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

	std::vector<unsigned> Q_curr;
	std::vector<unsigned> Q_next;
	std::vector<unsigned> S;
	std::vector<unsigned> ends;

	unsigned depth =0;
	
	std::vector<unsigned> d(g.num_vertex, UINT_MAX);
	std::vector<unsigned> sigma(g.num_vertex,0);
	std::vector<unsigned> delta;


	for( unsigned source = 4; source < 5; source++)
	{
		
		//Initialization
		#pragma omp parallel for
		for (unsigned v = 0; v < g.num_vertex; v++)
		{
			if(v == source)
			{
				d.at(v) = 0;
				sigma.at(v) = 1;
			}
			else
			{
				d.at(v) = UINT_MAX;
				sigma.at(v) = 0;
			}
		}
		Q_curr.push_back(source);
		S.push_back(source);
		ends.push_back(0);
		ends.push_back(1);
		#pragma omp barrier

		//Work efficilen shortest path calculation
		while (true)
		{
			#pragma omp parallel for shared(Q_next) shared(Q_curr) shared(d) shared(sigma)
			for(unsigned tid = 0; tid < Q_curr.size(); tid++)
			{
				unsigned v = Q_curr.at(tid);
				for(unsigned j=g.R[v]; j<g.R[v+1]; j++) //for each neighbor of v
				{	
					#pragma omp critical(compareAndSwap)
					{
						unsigned w = g.C[j];
						std::cout << "Node analyzed is " << v << " , its neighbor is: " << w << " analyzed by " << omp_get_thread_num() << std::endl;
						if(d[w] == UINT_MAX)
						{
							Q_next.push_back(w);
							d[w] = d[v]+1;
						}
						if(d[w] == (d[v]+1))
						{
							sigma[w] += sigma[v];
						}
						std::cout << "Node analyzed is " << v << " , its d is: " << d[w] << " analyzed by " << omp_get_thread_num() << std::endl;

					}	
				}
			}
			#pragma omp barrier
			if(Q_next.size() == 0)
			{
				depth = d[S.at(S.size()-1)]-1;
				break;
			}
			Q_curr.clear();
			#pragma omp parallel for
			for(unsigned tid = 0; tid < Q_next.size(); tid++)
			{
				Q_curr.push_back(Q_next.at(tid));
				S.push_back(Q_next.at(tid));
			}
			#pragma omp barrier
			Q_next.clear();
			ends.push_back(S.size());
			#pragma omp barrier
		}
		#pragma omp barrier

		std::cout << "------> Breadth first completed. ends.size = " << ends.size() << " depth = " << depth << std::endl;	
		for(unsigned i=0; i<g.num_vertex; i++)
		{
			std::cout << "d[" << i << "] = " << d[i] << std::endl;
		}	
		//Dependency accumulation
		while(depth > 0)
		{	
			#pragma omp parallel for shared(d) shared(delta)
			for(unsigned tid = ends[depth]; tid < ends[depth+1]; tid++)
			{
				unsigned w = S[tid];
				unsigned dsw = 0;
				unsigned sw = sigma.at(w);
				for(unsigned j=g.R[w]; j<g.R[w+1]; j++) //for each neighbor of v
				{	
					unsigned v = g.C[j];
					if(d[v] == (d[w]+1))
						dsw += (sw/(float)sigma[v])*(1+delta[v]);
				}
				delta[w] = dsw;

			}
			#pragma omp barrier
			depth--;
		}

		for (unsigned i = 0; i < g.num_vertex; i++)
		{
			bc[source] += delta[i];
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