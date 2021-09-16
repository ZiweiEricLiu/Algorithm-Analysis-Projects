#include "project1.h"
#include <cmath>


std::vector<int> pratt_generator(int max) {
	std::vector<int> pratt;
	pratt.push_back(0);
	for (int q = 0;; q++) {
		int candidate;
		candidate = std::pow(3, q);
		if (candidate >= max) {
			break;
		}
		for (int p = 0;; p++) {
			candidate = std::pow(2, p)*std::pow(3, q);
			if (candidate < max) {
				pratt.push_back(candidate);
			}
			else {
				break;
			}
		}
	}
	merge_sort(pratt);
	return pratt;
}


void shell_sort3(std::vector<int>& nums) {
	std::vector<int> pratt = pratt_generator(nums.size());
	int k = pratt.size() - 1;
	for (int gap = pratt[k]; gap > 0; --k, gap=pratt[k]) {
		for (int i = gap; i < nums.size(); i++) {
			int temp = nums[i];
			int j;
			for (j = i; j >= gap && temp < nums[j - gap]; j -= gap) {
				nums[j] = nums[j - gap];
			}
			nums[j] = temp;
		}
	}
}