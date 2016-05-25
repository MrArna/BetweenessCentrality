#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/bimap.hpp>

class Graph
{

public:
	unsigned num_vertex;
	unsigned num_edge;

	unsigned *R;
	unsigned *C;
	unsigned *F;

	boost::bimap<unsigned,std::string> IDs;

	Graph()
	{

	}

	void parse_edgelist(char *file);

	void print_R();

	void print_number_of_isolated_vertices();

	void print_CSR();
		
	void print_high_degree_vertices();

	void print_adjacency_list();

	void print_numerical_edge_file(char *outfile);

	void print_BC_scores(const std::vector<float> bc, char *outfile);



};

#endif // __GRAPH_H__