#include "project2.h"

// implement in next_fit.cpp
void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	if (items.size() == 0) {
		return;
	}
	int current_bin = 1;
	int current_item = 0;
	free_space.push_back(1.0);
	for (auto i : items) {
		if (i <= free_space[current_bin-1]) {
			assignment[current_item] = current_bin;
			free_space[current_bin-1] -= i;
		}
		else {
			current_bin++;
			assignment[current_item] = current_bin;
			free_space.push_back(1.0 - i);
		}
		current_item++;
	}
}