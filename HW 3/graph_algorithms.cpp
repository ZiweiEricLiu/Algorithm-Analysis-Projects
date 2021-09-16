#include "graph.h"
#include <chrono>
#include <random>

int get_diameter(Graph graph)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng = std::mt19937(seed);
	std::uniform_int_distribution<int> distribution(1, graph.get_num_nodes());

	int Dmax = 0;
	Path_param path = graph.get_longest_path(distribution(rng));

	while (path.dist > Dmax) {
		Dmax = path.dist;
		path = graph.get_longest_path(path.to);
	}
	return Dmax;
}

float get_clustering_coefficient(Graph graph) 
{
	return (3.0 * graph.get_triangles()) / graph.two_edge_paths();;
}

std::map<int, int> get_degree_distribution(Graph graph) 
{
	return graph.degree_distribution(); // remove this line if you implement the function
}