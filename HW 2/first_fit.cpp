#include "project2.h"
#include "WAVLTree.h"
#include "merge_sort.h"

// implement in next_fit.cpp
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	if (items.size() == 0) {
		return;
	}
	int current_bin = 1;
	int current_item = 0;
	WAVLTree<int, double> tree(true);
	free_space.push_back(1.0);
	tree.insert(current_bin, 1.0);
	for (auto i : items) {
		int assigned_bin = tree.findByMaxVal(i);
		if (assigned_bin == -1) {
			current_bin++;
			assignment[current_item] = current_bin;
			free_space.push_back(1.0 - i);
			tree.insertWithoutDupl(current_bin, free_space[current_bin-1]);
		}
		else {
			assignment[current_item] = assigned_bin;
			free_space[assigned_bin-1] -= i;
			tree.insertWithoutDupl(assigned_bin, free_space[assigned_bin-1]);
		}
		current_item++;
	}
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	if (items.size() == 0) {
		return;
	}
	std::vector<double> sort_items = items;
	merge_sort(sort_items);
	int current_bin = 1;
	int current_item = 0;
	WAVLTree<int, double> tree(true);
	free_space.push_back(1.0);
	tree.insert(current_bin, 1.0);
	for (auto i : sort_items) {
		int assigned_bin = tree.findByMaxVal(i);
		if (assigned_bin == -1) {
			current_bin++;
			assignment[current_item] = current_bin;
			free_space.push_back(1.0 - i);
			tree.insertWithoutDupl(current_bin, free_space[current_bin - 1]);
		}
		else {
			assignment[current_item] = assigned_bin;
			free_space[assigned_bin - 1] -= i;
			tree.insertWithoutDupl(assigned_bin, free_space[assigned_bin - 1]);
		}
		current_item++;
	}
}