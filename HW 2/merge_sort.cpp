#include "merge_sort.h"

void merge(std::vector<double>& nums, std::vector<double>& L, std::vector<double>& R) {
	int i, j;
	for (i = 0, j = 0; i < L.size() && j < R.size();) {
		if (L[i] >= R[j]) {
			nums[i + j] = L[i];
			i++;
		}
		else {
			nums[i + j] = R[j];
			j++;
		}
	}
	while (i < L.size()) {
		nums[i + j] = L[i];
		i++;
	}
	while (j < R.size()) {
		nums[i + j] = R[j];
		j++;
	}
}

void merge_sort(std::vector<double>& nums) {
	if (nums.size() > 1) {
		int mid = nums.size() / 2;
		std::vector<double> L(nums.begin(), nums.begin() + mid);
		std::vector<double> R(nums.begin() + mid, nums.end());
		merge_sort(L);
		merge_sort(R);
		merge(nums, L, R);
	}
}