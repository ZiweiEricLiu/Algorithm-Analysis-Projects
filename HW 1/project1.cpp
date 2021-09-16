#include <iostream>
#include "project1.h"
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> generateUniform(int size) {
	std::vector<int> nums;
	for (int i = 0; i < size; ++i) {
		nums.push_back(i);
	}
	std::random_shuffle(nums.begin(), nums.end());
	return nums;
}

std::vector<int> generateAlmostSorted(int size) {
	std::vector<int> nums;
	for (int i = 0; i < size; ++i) {
		nums.push_back(i);
	}
	for (int i = 0; i < 2 * std::log(size); i++) {
		int index1 = rand() % size;
		int index2 = rand() % size;
		while (index2 == index1) {
			index2 = rand() % size;
		}
		std::swap(nums[index1], nums[index2]);
	}
	return nums;
}

std::vector<int> generateReverse(int size) {
	std::vector<int> nums;
	for (int i = size - 1; i >= 0; --i) {
		nums.push_back(i);
	}
	return nums;
}


int main(int argc, char* argv[]) {
	int input_size = atoi(argv[2]);
	std::string fn_name = std::string(argv[1]);
	std::string arrange = std::string(argv[3]);
	std::vector<int> nums;
	if (arrange == "uniform") {
		nums = generateUniform(input_size);
	}
	else if (arrange == "almost") {
		nums = generateAlmostSorted(input_size);
	}
	if (arrange == "reverse") {
		nums = generateReverse(input_size);
	}
	if (fn_name == "insertion") { insertion_sort(nums); }
	else if (fn_name == "merge") { merge_sort(nums); }
	else if (fn_name == "shell1") { shell_sort1(nums); }
	else if (fn_name == "shell2") { shell_sort2(nums); }
	else if (fn_name == "shell3") { shell_sort3(nums); }
	else if (fn_name == "shell4") { shell_sort4(nums); }
	else if (fn_name == "hybrid1") { hybrid_sort1(nums); }
	else if (fn_name == "hybrid2") { hybrid_sort2(nums); }
	else if (fn_name == "hybrid3") { hybrid_sort3(nums); }
}
