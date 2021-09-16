#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "node.h"

struct Path_param {
	int from;
	int to;
	int dist;
};

class Graph 
{
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE
        int get_num_nodes(); 						// get number of nodes
        int get_num_edges(); 						// get number of edges
        std::vector<Node> get_neighbors(Node u); 	// return neighbors of u 
        std::map<int, Node> get_id_to_node_map(); 	// allows lookup of nodes from ids
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE
		
		// declare any constructors, members, and member functions you may want to use
		Graph();
		Graph(int num_nodes, std::vector<int> u, std::vector<int> v);

		std::vector<std::vector<bool>> graph;
		int num_nodes;
		int num_edges;
		// implement any newly declared member functions in graph.cpp
		std::vector<int> get_neighbors(int u);
		Path_param get_longest_path(int from);
		int get_degree(int u);
		int two_edge_paths();
		int get_triangles();
		std::map<int, int> degree_distribution();
};

#endif
