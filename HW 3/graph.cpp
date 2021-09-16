#include "graph.h"
#include <unordered_set>
#include <queue>

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
	return Graph(num_nodes, u, v); 
}

Graph::Graph()
	:num_nodes{ 0 }, num_edges{ 0 }
{}

Graph::Graph(int num_nodes, std::vector<int> u, std::vector<int> v) 
	:num_nodes{ num_nodes }, num_edges{ 0 }
{
	graph = std::vector<std::vector<bool>>(num_nodes, std::vector<bool>(num_nodes, 0));

	for (int i = 0; i < u.size(); i++) {
		int m = u[i] - 1;
		int n = v[i] - 1;
		if (graph[m][n] == 0 || graph[n][m] == 0) {
			graph[m][n] = 1;
			graph[n][m] = 1;
			num_edges++;
		}
	}
}

int Graph::get_num_nodes() {
	return num_nodes; 
}

int Graph::get_num_edges() {
	return num_edges; 
}

std::vector<int> Graph::get_neighbors(int u) {
	std::vector<int> neighbors;
	for (int i = 0; i < num_nodes; i++) {
		if (graph[u - 1][i] == 1) {
			neighbors.push_back(i + 1);
		}
	}
	return neighbors;
}

std::vector<Node> Graph::get_neighbors(Node u) {
	std::vector<Node> neighbors;
	for (int i = 0; i < num_nodes; i++) {
		if (graph[u.id - 1][i] == 1) {
			neighbors.push_back(Node(i + 1));
		}
	}
	return neighbors; 
}

std::map<int, Node> Graph::get_id_to_node_map(){
	std::map<int, Node> map;
	for (int i = 0; i < num_nodes; i++) {
		map[i + 1] = Node(i + 1);
	}
	return map;
}

Path_param Graph::get_longest_path(int from) {
	if (get_neighbors(from).size() == 0) {
		return Path_param{ -1, -1, 0 };
	}
	int distance = -1;
	int to;
	std::queue<int> bfs;
	std::unordered_set<int> expanded;

	bfs.push(from);
	expanded.insert(from);

	while (!bfs.empty()) {
		std::vector<int> vertex_list;
		int v;
		while (!bfs.empty()) {
			vertex_list.push_back(bfs.front());
			bfs.pop();
		}
		for (auto to_expand_v : vertex_list) {
			for (auto neighbor : get_neighbors(to_expand_v)) {
				if (expanded.find(neighbor) == expanded.end()) {
					bfs.push(neighbor);
					expanded.insert(neighbor);
					v = neighbor;
				}
			}
		}
		distance++;
		to = v;
	}
	return Path_param{ from, to, distance };
}

int Graph::get_degree(int u) {
	return get_neighbors(u).size();
}

int Graph::two_edge_paths() {
	int paths = 0;
	for (int i = 1; i <= num_nodes; i++) {
		int deg = get_degree(i);
		paths += deg * (deg - 1) / 2;
	}
	return paths;
}

int Graph::get_triangles() {
	int count = 0;
	for (int i = 1; i <= num_nodes; ++i) {
		std::vector<int> neighbors = get_neighbors(i);
		for (int j = 0; j < neighbors.size(); ++j) {
			for (int k = j + 1; k < neighbors.size(); ++k) {
				int m = neighbors[j];
				int n = neighbors[k];
				if (m == n) {
					continue;
				}
				int deg_i = get_degree(i);
				int deg_m = get_degree(m);
				int deg_n = get_degree(n);
				if ((deg_m > deg_i && deg_n > deg_i) || (deg_m > deg_i && deg_n == deg_i && n > i) || (deg_n > deg_i && deg_m == deg_i && m > i)) {
					if (graph[m-1][n-1] && graph[n-1][m-1]) {
						count++;
					}
				}

			}
		}
	}
	return count;
}

std::map<int, int> Graph::degree_distribution() {
	std::map<int, int> distribution;
	for (int i = 1; i <= num_nodes; i++) {
		int deg = get_degree(i);
		distribution[deg]++;
	}
	return distribution;
}
