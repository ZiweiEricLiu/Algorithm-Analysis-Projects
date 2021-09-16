#include "project1.h"
#include <cmath>

std::vector<int> sq_generator(int max) {
	std::vector<int> sq;
	sq.push_back(0);
	sq.push_back(1);
	for (int k = 0;; k++) {
		int candidate = pow(4, k + 1) + 3 * pow(2, k) + 1;
		if (candidate >= max) {
			break;
		}else{
			sq.push_back(candidate);
		}
	}
	return sq;
}

void shell_sort4(std::vector<int>& nums) {
	std::vector<int> sq = sq_generator(nums.size());
	int k = sq.size() - 1;
	for (int gap = sq[k]; gap > 0; --k, gap = sq[k]) {
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