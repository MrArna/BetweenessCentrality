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

	void parse_edgelist(char *file)
		{
			std::set<std::string> vertices;

			//Scan the file
			std::ifstream edgelist(file,std::ifstream::in);
			std::string line;
			
			if(!edgelist.good())
			{
				std::cerr << "Error opening graph file." << std::endl;
				exit(-1);
			}

			std::vector<std::string> from;
			std::vector<std::string> to;
			while(std::getline(edgelist,line))
			{
				if((line[0] == '%') || (line[0] == '#')) //Allow comments
				{
					continue;
				}

				std::vector<std::string> splitvec;
				boost::split(splitvec,line,boost::is_any_of(" \t"),boost::token_compress_on);
			
				if(splitvec.size() != 2)
				{
					std::cerr << "Warning: Found a row that does not represent an edge or comment." << std::endl;
					std::cerr << "Row in question: " << std::endl;	
					for(unsigned i=0; i<splitvec.size(); i++)
					{
						std::cout << splitvec[i] << std::endl;
					}
					exit(-1);
				}

				for(unsigned i=0; i<splitvec.size(); i++)
				{
					vertices.insert(splitvec[i]);
				}

				from.push_back(splitvec[0]);
				to.push_back(splitvec[1]);
			}

			edgelist.close();

			this->num_vertex = vertices.size();
			this->num_edge = from.size();

			unsigned id = 0;
			for(std::set<std::string>::iterator i = vertices.begin(), e = vertices.end(); i!=e; ++i)
			{
				this->IDs.insert(boost::bimap<unsigned,std::string>::value_type(id++,*i));
			}

			this->R = new unsigned int[this->num_vertex+1];
			this->F = new unsigned int[2*this->num_edge];
			this->C = new unsigned int[2*this->num_edge];

			for(unsigned i=0; i<this->num_edge; i++)
			{
				boost::bimap<unsigned,std::string>::right_map::iterator itf = this->IDs.right.find(from[i]);
				boost::bimap<unsigned,std::string>::right_map::iterator itc = this->IDs.right.find(to[i]);

				if((itf == this->IDs.right.end()) || (itc == this->IDs.right.end()))
				{
					std::cerr << "Error parsing graph file." << std::endl;
					exit(-1);
				}
				else
				{
					if(itf->second == itc->second)
					{
						std::cerr << "Error: self edge! " << itf->second << " -> " << itc->second << std::endl;
						std::cerr << "Aborting. Graphs with self-edges aren't supported." << std::endl;
						exit(-1);
					}
					this->F[2*i] = itf->second;
					this->C[2*i] = itc->second;
					//Treat undirected edges as two directed edges
					this->F[(2*i)+1] = itc->second;
					this->C[(2*i)+1] = itf->second;
				}
			}

			//Sort edges by F
			std::vector< std::pair<int,int> >edges;
			for(unsigned i=0; i<2*this->num_edge; i++)
			{
				edges.push_back(std::make_pair(this->F[i],this->C[i]));
			}
			std::sort(edges.begin(),edges.end()); //By default, pair sorts with precedence to it's first member, which is precisely what we want.
			this->R[0] = 0;
			unsigned last_node = 0;
			for(unsigned i=0; i<2*this->num_edge; i++)
			{
				this->F[i] = edges[i].first;
				this->C[i] = edges[i].second;
				while(edges[i].first > last_node)
				{
					this->R[++last_node] = i;
				}
			}
			this->R[this->num_vertex] = 2*this->num_edge;
			edges.clear();
		}

		void print_R()
		{
			if(R == NULL)
			{
				std::cerr << "Error: Attempt to prunsignedCSR of a graph that has not been parsed." << std::endl;
			}

			std::cout << "R = [";
			for(unsigned i=0; i<(num_vertex+1); i++)
			{
				if(i == this->num_vertex)
				{
					std::cout << R[i] << "]" << std::endl;
				}
				else
				{
					std::cout << R[i] << ",";
				}
			}
		}

		void print_number_of_isolated_vertices()
		{
			if(R == NULL)
			{
				std::cerr << "Error: Attempt to prunsignedCSR of a graph that has not been parsed." << std::endl;
			}

			unsigned isolated = 0;
			for(unsigned i=0; i<num_vertex; i++)
			{
				unsigned degree = R[i+1]-R[i];
				if(degree == 0)
				{
					isolated++;
				}
			}

			std::cout << "Number of isolated vertices: " << isolated << std::endl;
		}

		void print_CSR()
		{
			if((R == NULL) || (C == NULL) || (F == NULL))
			{
				std::cerr << "Error: Attempt to prunsignedCSR of a graph that has not been parsed." << std::endl;
				exit(-1);
			}

			std::cout << "R = [";
			for(unsigned i=0; i<(num_vertex+1); i++)
			{
				if(i == num_vertex)
				{
					std::cout << R[i] << "]" << std::endl;
				}
				else
				{
					std::cout << R[i] << ",";
				}
			}

			std::cout << "C = [";
			for(unsigned i=0; i<(2*num_edge); i++)
			{
				if(i == ((2*num_edge)-1))
				{
					std::cout << C[i] << "]" << std::endl;
				}
				else
				{
					std::cout << C[i] << ",";
				}
			}	
			
			std::cout << "F = [";
			for(unsigned i=0; i<(2*num_edge); i++)
			{
				if(i == ((2*num_edge)-1))
				{
					std::cout << F[i] << "]" << std::endl;
				}
				else
				{
					std::cout << F[i] << ",";
				}
			}	
		}

		void print_high_degree_vertices()
		{
			if(R == NULL)
			{
				std::cerr << "Error: Attempt to search adjacency list of graph that has not been parsed." << std::endl;
				exit(-1);
			}

			unsigned max_degree = 0;
			for(unsigned i=0; i<num_vertex; i++)
			{
				unsigned degree = R[i+1]-R[i];
				if(degree > max_degree)
				{
					max_degree = degree;
					std::cout << "Max degree: " << degree << std::endl;
				}
			}
		}

		void print_adjacency_list()
		{
			if(R == NULL)
			{
				std::cerr << "Error: Attempt to prunsignedadjacency list of graph that has not been parsed." << std::endl;
				exit(-1);
			}

			std::cout << "Edge lists for each vertex: " << std::endl;

			for(unsigned i=0; i<num_vertex; i++)
			{
				unsigned begin = R[i];
				unsigned end = R[i+1];
				boost::bimap<unsigned,std::string>::left_map::iterator itr = IDs.left.find(i);
				for(unsigned j=begin; j<end; j++)
				{
					boost::bimap<unsigned,std::string>::left_map::iterator itc = IDs.left.find(C[j]);
					if(j==begin)
					{
						std::cout << itr->second << " | " << itc->second;
					}
					else
					{
						std::cout << ", " << itc->second;
					}
				}
				if(begin == end) //Single, unconnected node
				{
					std::cout << itr->second << " | ";
				}
				std::cout << std::endl;
			}
		}

		void print_numerical_edge_file(char *outfile)
		{
			std::ofstream ofs(outfile, std::ios::out);
			if(!ofs.good())
			{
				std::cerr << "Error opening output file." << std::endl;
				exit(-1);
			}	
			for(unsigned i=0; i<2*num_edge; i++)
			{
				if(F[i] < C[i])
				{
					ofs << F[i] << " " << C[i] << std::endl;
				}
			}
		}

		void print_BC_scores(const std::vector<float> bc, char *outfile)
		{
			std::ofstream ofs;
			if(outfile != NULL)
			{
				ofs.open(outfile, std::ios::out);
			}
			std::ostream &os = (outfile ? ofs : std::cout);
			for(unsigned i=0; i<num_vertex; i++)
			{
				boost::bimap<unsigned,std::string>::left_map::iterator it = IDs.left.find(i);
				if(it != IDs.left.end())
				{
					os << it->second << " " << bc[i] << std::endl;
				}
				else
				{
					//Just prunsignedthe numeric id
					os << i << " " << bc[i] << std::endl;
				}
			}
		}



};

#endif // __GRAPH_H__