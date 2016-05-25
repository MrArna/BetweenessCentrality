#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <limits.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "graph.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <set>



int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		std::cout << "Command usage: " << argv[0] << " ./GRAPH_PATH" << std::endl;
		return 0;
	}

	srand(time(NULL));
	
	// Data structure declararion
	Graph *graph = new Graph();
	Graph g = *graph;
	g.parse_edgelist(argv[1]);
	g.print_CSR();
	std::vector<float> bc(g.num_vertex,0);

	std::vector<unsigned> Q_curr(g.num_vertex,0);
	unsigned Q_curr_len = 0;
	std::vector<unsigned> Q_next(g.num_vertex,0);
	unsigned Q_next_len = 0;
	std::vector<unsigned> S(g.num_vertex,0);
	unsigned S_len = 0;
	std::vector<unsigned> ends(g.num_vertex,0);
	unsigned ends_len = 0;

	unsigned depth =0;
	
	std::vector<unsigned> d(g.num_vertex, UINT_MAX);
	std::vector<unsigned> sigma(g.num_vertex,0);
	std::vector<float> delta(g.num_vertex,0);


	for(unsigned source = 0; source < g.num_vertex; source++)
	{
		
		//Initialization
		#pragma omp parallel for
		for (unsigned v = 0; v < g.num_vertex; v++)
		{
			if(v == source)
			{
				d[v] = 0;
				sigma[v] = 1;
			}
			else
			{
				d[v] = UINT_MAX;
				sigma[v] = 0;
			}
			delta[v] = 0;
		}
		Q_curr[0] = source;
		Q_curr_len = 1;
		Q_next_len = 0;
		S[0] = source;
		S_len = 1;
		ends[0] = 1;
		ends[1] = 1;
		ends_len = 2;
		depth = 0;
		

		//Work efficient shortest path calculation
		while (true)
		{
			#pragma omp parallel for shared(Q_next) shared(Q_curr) shared(d) shared(sigma)
			for(unsigned tid = 0; tid < Q_curr_len; tid++)
			{
				unsigned v = Q_curr[tid];
				for(unsigned j=g.R[v]; j<g.R[v+1]; j++) //for each neighbor of v
				{	
					unsigned w = g.C[j];
					//std::cout << "Node analyzed is " << v << " , its neighbor is: " << w << " analyzed by " << omp_get_thread_num() << std::endl;
					#pragma omp critical(compareAndSwap)
					{
						if(d[w] == UINT_MAX)
						{
							Q_next[Q_next_len] = w;
							Q_next_len++;
							d[w] = d[v]+1;
						}
					}
					if(d[w] == (d[v]+1))
					{
						#pragma omp atomic
						sigma[w] += sigma[v];
					}
					//std::cout << "Node analyzed is " << v << " , its d is: " << d[w] << " analyzed by " << omp_get_thread_num() << std::endl;
				}
			}
			#pragma omp barrier
			if(Q_next_len == 0)
			{
				depth = d[S[S_len-1]]-1;
				break;
			}
			else
			{
				#pragma omp parallel for
				for(unsigned tid = 0; tid < Q_next_len; tid++)
				{
					Q_curr[tid] = Q_next[tid];
					S[tid + S_len] = Q_next[tid];
				}
				#pragma omp barrier
				ends[ends_len] = ends[ends_len-1] + Q_next_len;
				ends_len++;
				Q_curr_len = Q_next_len;
				S_len = S_len + Q_next_len;
				Q_next_len = 0;
				#pragma omp barrier
			}	
		}

		std::cout << "-------------> Breadth first completed for source " << source <<  "<----------" << std::endl;
		for(unsigned i = 0; i < g.num_vertex; i++)
		{
				std::cout << "sigma[" << i << "] = "  << sigma[i]  << " || delta[" << i << "] = "  << delta[i]  << std::endl;
		}	
		//Dependency accumulation
		while(depth > 0)
		{	
			#pragma omp parallel for shared(d) shared(delta)
			for(unsigned tid = ends[depth]; tid < ends[depth+1]; tid++)
			{
				unsigned w = S[tid];
				float dsw = 0.0f;
				unsigned sw = sigma[w];
				for(unsigned j=g.R[w]; j<g.R[w+1]; j++) //for each neighbor of v
				{	
					unsigned v = g.C[j];
					if(d[v] == (d[w]+1))
					{
						dsw += (sw/(float)sigma[v])*(1+delta[v]);
						//std::cout << "d[v] = " << d[v] << " || d[w] = " << d[w] << " || sigma[v] = " << sigma[v] << std::endl; 
					}
				}
				delta[w] = dsw;

			}
			#pragma omp barrier
			depth--;
		}

		for(unsigned i = 0; i < g.num_vertex; i++)
		{
			//std::cout << "delta[" << i << "] = "  << delta[i]  << std::endl;
		}	

		for (unsigned i = 0; i < g.num_vertex; i++)
		{
			//std::cout << "sigma[" << i << "] = " << sigma[i] << std::endl; 
			bc[source] += i == source ? 0 : delta[i];
		}
	}
	#pragma omp barrier
	for(unsigned i=0; i<g.num_vertex; i++)
	{
		bc[i] /= 2.0f; //Undirected edges are modeled as two directed edges, but the scores shouldn't be double counted.
	}

	g.print_BC_scores(bc,NULL);

	return 1;
}