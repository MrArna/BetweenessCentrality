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



int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		std::cout << "Command usage: " << argv[0] << " ./GRAPH_PATH" << std::endl;
		return 0;
	}

	srand(time(NULL))
	
	//Data structure declaration

	// Initialization
	Graph *graph = new Graph(argv[1]);
	unsigned long long source = rand() % graph->getNumVertex();
	unsigned long long d[graph->getNumVertex()];
	unsigned long long sigma[graph->getNumVertex()];


	unsigned long long currentDepth = 0;
	bool done = false;
	std::queue<unsigned long long> frontier;

	#pragma omp parallel for
	for(unsigned long long i = 0; i < graph->getNumVertex(); i++)
	{
		if(i == source)
		{
			d[i] = 0;
			sigma[i] = 1;
		}
		else
		{
			d[i] = ULLONG_MAX;
			sigma[i] = 0;
		}
	}


	//edge parallel core
	while(!done)
	{
		done = true;

		#pragma omp parallel for
		for(unsigned long long i = 0; i < graph->getNumEdge(); i++)
		{	
			unsigned long long v = graph->getC().at(i);

			if(d[v] == current_depth) 
		    {
		      unsigned long long w = C[i];
		      if(d[w] == INT_MAX)
		      {
		        d[w] = d[v] + 1;
		        done = false;

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
	}

	return 1;
}