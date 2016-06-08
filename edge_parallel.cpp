#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <limits.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Graph.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <set>

#include <sys/time.h>

int main(int argc, char *argv[])
{
	struct timeval start, end;

	if(argc != 2)
	{
		std::cout << "Command usage: " << argv[0] << " ./GRAPH_PATH" << std::endl;
		return 0;
	}



	// Data structure declararion
	Graph *graph = new Graph();
	Graph g = *graph;
	g.parse_edgelist(argv[1]);
	//g.print_CSR();

	//take initial time
	gettimeofday(&start, NULL);

	std::vector<float> bc(g.num_vertex,0);

	std::vector<unsigned> S(g.num_vertex,0);
	unsigned S_len = 0;
	std::vector<unsigned> ends(g.num_vertex,0);
	unsigned ends_len = 0;

	
	std::vector<unsigned> d(g.num_vertex, UINT_MAX);
	std::vector<unsigned> sigma(g.num_vertex,0);
	std::vector<float> delta(g.num_vertex,0);
	unsigned long current_depth = 0;
	unsigned long depth = 0;
	bool done = false;
	
	
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
		S[0] = source;
		S_len = 1;
		ends[0] = 1;
		ends[1] = 1;
		ends_len = 2;
		current_depth = 0;
		done = false;
		

		while(!done)
		{
			done = true;
			#pragma omp parallel for shared(done) shared(S) shared(d) shared(sigma)
			for(unsigned long edge = 0; edge < g.R[g.num_vertex]; edge+=1)
			{
				unsigned long v = g.F[edge];
				if(d[v] == current_depth)
				{
					unsigned long w = g.C[edge];
					if(d[w] == UINT_MAX)
					{
						done = false;
						d[w] = d[v] + 1;
						#pragma omp critical(seenUpdate)
						{
							S[S_len] = w;
							S_len++;
						}
					}
					if(d[w] == (d[v] + 1))
					{
						#pragma omp atomic
						sigma[w] += sigma[v];
					}
				}
			}
			#pragma omp barrier
			current_depth++;
			ends[ends_len] = S_len;
			ends_len++;
		}		

		depth = current_depth;

		//std::cout << "-------------> Breadth first completed for source " << source <<  "<----------" << std::endl;
		/*for(unsigned i = 0; i < g.num_vertex; i++)
		{
				std::cout << "sigma[" << i << "] = "  << sigma[i]  << " || d[" << i << "] = "  << d[i]  << std::endl;
		}*/	
		/*for(unsigned long i = 0; i < S_len; i++)
		{
			if(i==0)
				std::cout << "S = [";
			std::cout << S[i] << ",";
		}*/
		/*std::cout << "]" << std::endl;
		for(unsigned long i = 0; i < ends_len; i++)
		{
			if(i==0)
				std::cout << "ends = [";
			std::cout << ends[i] << ",";
		}
		std::cout << "]" << std::endl;
		*/
		//Dependency accumulation
		while(depth > 0)
		{	
			#pragma omp parallel for shared(d) shared(delta)
			for(unsigned tid = ends[depth]; tid < ends[depth+1]; tid++)
			{
				unsigned w = S[tid];
				float dsw = 0.0f;
				unsigned sw = sigma.at(w);
				for(unsigned j=g.R[w]; j<g.R[w+1]; j++) //for each neighbor of v
				{	
					unsigned v = g.C[j];
					if(d[v] == (d[w]+1))
					{
						dsw += (sw/(float)sigma[v])*(1+delta[v]);
						//std::cout << "[thread " << omp_get_thread_num() << "] dsw = " << dsw << " \tv = " << v << " \tw = " << w << std::endl;
						////std::cout << "d[v] = " << d[v] << " || d[w] = " << d[w] << " || sigma[v] = " << sigma[v] << std::endl; 
					}
				}
				delta[w] = dsw;
			}
			#pragma omp barrier
			//std::cout << "---------- new depth ----------" << std::endl;
			depth--;
		}
		/*
		for(unsigned i = 0; i < g.num_vertex; i++)
		{
			//std::cout << "delta[" << i << "] = "  << delta[i]  << std::endl;
		}	
	*/
		for (unsigned i = 0; i < g.num_vertex; i++)
		{
			//std::cout << "sigma[" << i << "] = " << sigma[i] << std::endl; 
			bc[i] += i == source ? 0 : delta[i];
		}
	}
	#pragma omp barrier
	for(unsigned i=0; i<g.num_vertex; i++)
	{
		bc[i] /= 2.0f; //Undirected edges are modeled as two directed edges, but the scores shouldn't be double counted.
	}

	g.print_BC_scores(bc,NULL);

	gettimeofday(&end, NULL);

	double elapsed = ((double)((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000;
	//printf("time %lf\n", elapsed);
	std::cerr << "time " << elapsed << std::endl;
	
	return 1;
}



