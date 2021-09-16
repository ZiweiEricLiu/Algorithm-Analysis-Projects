#include "project1.h"
#include "merge.h"

void merge_sort(std::vector<int>& nums) {
	if (nums.size() > 1) {
		int mid = nums.size() / 2;
		std::vector<int> L(nums.begin(), nums.begin() + mid);
		std::vector<int> R(nums.begin() + mid, nums.end());
		merge_sort(L);
		merge_sort(R);
		merge(nums, L, R);
	}
}