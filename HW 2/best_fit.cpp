#include "project2.h"
#include "WAVLTree.h"
#include "merge_sort.h"

#include <iostream>
using namespace std;

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	if (items.size() == 0) {
		return;
	}
	int current_bin = 1;
	int current_item = 0;
	WAVLTree<double, int> tree;
	free_space.push_back(1.0);
	tree.insert(1.0, current_bin);
	for (auto i : items) {
		int assigned_bin = tree.findByMaxKey(i);
		if (assigned_bin == -1) {
			current_bin++;
			assignment[current_item] = current_bin;
			free_space.push_back(1.0 - i);
			tree.insert(free_space[current_bin-1], current_bin);
		}
		else {
			assignment[current_item] = assigned_bin;
			double key = free_space[assigned_bin - 1];
			free_space[assigned_bin - 1] -= i;
			tree.removeWithDup(key, assigned_bin);
			tree.insert(free_space[assigned_bin - 1], assigned_bin);
		}
		current_item++;
	}
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	if (items.size() == 0) {
		return;
	}
	std::vector<double> sort_items = items;
	merge_sort(sort_items);
	int current_bin = 1;
	int current_item = 0;
	WAVLTree<double, int> tree;
	free_space.push_back(1.0);
	tree.insert(1.0, current_bin);

	for (auto i : sort_items) {
		int assigned_bin = tree.findByMaxKey(i);
		if (assigned_bin == -1) {
			current_bin++;
			assignment[current_item] = current_bin;
			free_space.push_back(1.0 - i);
			tree.insert(free_space[current_bin - 1], current_bin);
		}
		else {
			assignment[current_item] = assigned_bin;
			double key = free_space[assigned_bin - 1];
			free_space[assigned_bin - 1] -= i;
			tree.removeWithDup(key, assigned_bin);
			tree.insert(free_space[assigned_bin - 1], assigned_bin);
		}
		current_item++;
	}
}