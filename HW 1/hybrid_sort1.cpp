#include "project1.h"
#include <cmath>
#include "merge.h"

void hybrid_sort1(std::vector<int>& nums) {
	int H = pow(nums.size(), 1.0 / 2.0);
	if (nums.size() > H) {
		int mid = nums.size() / 2;
		std::vector<int> L(nums.begin(), nums.begin() + mid);
		std::vector<int> R(nums.begin() + mid, nums.end());
		merge_sort(L);
		merge_sort(R);
		merge(nums, L, R);
	}
	else {
		insertion_sort(nums);
	}
}