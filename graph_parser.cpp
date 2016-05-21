#include <omp.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Graph.hpp"


void printArray(unsigned long long array[], unsigned long long size)
{
	for (unsigned long long i = 0; i < size; i++ ) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[]) 
{



	if(argc != 2)
	{
		std::cout << "Command usage: " << argv[0] << " ./GRAPH_PATH" << std::endl;
		return 0;
	}


	Graph *graph = new Graph(argv[1]);

	std::cout << graph->getNumVertex(); << std::endl;  


	return 1;
}
