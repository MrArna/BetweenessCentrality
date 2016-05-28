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



    int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		std::cout << "Command usage: " << argv[0] << " ./GRAPH_PATH" << std::endl;
		return 0;
	}

	srand(time(NULL));
	

	/*
	//edge parallel core
	while(!done)
	{
		done = true;

		#pragma omp parallel for
		for(unsigned long long i = 0; i < graph->num_edge; i++)
		{	
			unsigned long long v = graph->F[i];

			if(d[v] == current_depth) 
		    {
		      unsigned long long w = C[i];
		      #pragma omp critical(compareAndSwap)
			  {
			      if(d[w] == INT_MAX)
			      {
			        d[w] = d[v] + 1;
			        done = false;
			        S.push_back(w);

			      }
			  }
		      if(d[w] == (d[v] + 1))
		      {
		      	#pragma omp atomic
		      	sigma[w]+= sigma[v];
		        //atomicAdd(&sigma[w],sigma[v]);
		      }
		    }
		}
		current_depth++;
		ends.push_back(S.size()-1);
	}

	*/



		std::set<unsigned long long> source_vertices;
		//source_vertices.insert(3);
		Graph *graph = new Graph();
		Graph g = *graph;
		g.parse_edgelist(argv[1]);
		g.print_CSR();
		std::vector<float> bc(g.num_vertex,0);
		int end = source_vertices.empty() ? g.num_vertex : source_vertices.size();
		std::set<unsigned long long>::iterator it = source_vertices.begin();



		//#pragma omp parallel for
		for(int k=0; k<end; k++)
		{
			int i = source_vertices.empty() ? k : *it++;
			std::queue<int> Q;
			std::stack<int> S;
			std::vector<int> d(g.num_vertex,INT_MAX);
			d[i] = 0;
			std::vector<unsigned long long> sigma(g.num_vertex,0);
			sigma[i] = 1;
			std::vector<float> delta(g.num_vertex,0);
			Q.push(i);
			unsigned long long current_depth = 0;




			while(!Q.empty())
			{
				int v = Q.front();
				Q.pop();
				S.push(v);

				//#pragma omp parallel for
				for(unsigned int j=g.R[v]; j<g.R[v+1]; j++)
				{
					int w = g.C[j];
					if(d[w] == INT_MAX)
					{
						Q.push(w);
						d[w] = d[v]+1;
					}
					if(d[w] == (d[v]+1))
					{
						sigma[w] += sigma[v];
					}
				}
				//#pragma omp barrier
			}
			std::cout << "-------------> Breadth first completed for source " << k <<  "<----------" << std::endl;
			for(unsigned i = 0; i < g.num_vertex; i++)
			{
				std::cout << "sigma[" << i << "] = "  << sigma[i]  << " || d[" << i << "] = "  << d[i]  << std::endl;
			}	

			while(!S.empty())
			{
				int w = S.top();
				S.pop();
				//#pragma omp parallel for
				for(unsigned int j=g.R[w]; j<g.R[w+1]; j++)
				{
					//#pragma omp critical(compareAndSwap)
					//{
						int v = g.C[j];
						if(d[v] == (d[w] - 1))
						{
							delta[v] += (sigma[v]/(float)sigma[w])*(1+delta[w]);
							std::cout << "delta[v] = " << delta[v] << " \tv = " << v << " \tw = " << w << std::endl;

						}
					//}
				}
				//#pragma omp barrier	
				
				std::cout << "---------- new w ----------" << std::endl;

				if(w != i)
				{
					bc[w] += delta[w];
				}
			}
		}
		//#pragma omp barrier
		//#pragma omp parallel for
		for(int i=0; i<g.num_vertex; i++)
		{
			bc[i] /= 2.0f; //Undirected edges are modeled as two directed edges, but the scores shouldn't be double counted.
		}

		g.print_BC_scores(bc,NULL);

	return 1;
}
