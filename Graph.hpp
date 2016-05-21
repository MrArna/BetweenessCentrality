#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>

class Graph
{

private:
	unsigned long long num_vertex;
	unsigned long long num_edge;

	std::vector<unsigned long long> R;
	std::vector<unsigned long long> C;

public:
	Graph(char graph_path[])
	{
		// Open the file:
		std::ifstream fin(graph_path);

		// Declare variables:
		unsigned long long columns, rows, entries;

		// Ignore headers and comments:
		while (fin.peek() == '%') fin.ignore(2048, '\n');

		// Read defining parameters:
		fin >> columns >> rows >> entries;

		this->num_vertex = columns;
		this->num_edge = entries;

		unsigned long long edge;

		this->R.push_back(0);

		unsigned long long prev_node = 1, cur_node = 0;

		for(unsigned long long i = 0; i <= entries; i++)
		{
			fin >> cur_node;
			fin >> edge;
			edge--;
			this->C.push_back(edge);
			if(prev_node != cur_node)
			{
				this->R.push_back(i);
				prev_node = cur_node;
			}
		}

		fin.close();
	}

	unsigned long long getNumVertex()
	{
		return this->num_vertex;
	}

	unsigned long long getNumEdge()
	{
		return this->num_edge;
	}
};

#endif // __GRAPH_H__