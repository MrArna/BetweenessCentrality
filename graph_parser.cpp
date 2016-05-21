#include <omp.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <iostream>


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



	// Open the file:
	std::ifstream fin(argv[1]);

	// Declare variables:
	unsigned long long columns, rows, entries;

	// Ignore headers and comments:
	while (fin.peek() == '%') fin.ignore(2048, '\n');

	// Read defining parameters:
	fin >> columns >> rows >> entries;

	
	unsigned long long R[columns];
	unsigned long long C[entries];

	R[0] = 0;

	unsigned long long prev_node = 1, cur_node = 0;

	for(unsigned long long i = 0; i <= entries; i++)
	{
		fin >> cur_node;
		fin >> C[i];
		C[i]--;
		if(prev_node != cur_node)
		{
			R[cur_node-1] = i;
			prev_node = cur_node;
		}
	}

	fin.close();

	std::cout << "C = ";
	printArray(C, entries);
	std::cout << "R = ";
	printArray(R, columns);

	return 1;
}
