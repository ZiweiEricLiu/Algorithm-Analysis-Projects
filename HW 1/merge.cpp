#include "merge.h"

void merge(std::vector<int>& nums, std::vector<int>& L, std::vector<int>& R) {
	int i, j;
	for (i = 0, j = 0; i < L.size() && j < R.size();) {
		if (L[i] <= R[j]) {
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
