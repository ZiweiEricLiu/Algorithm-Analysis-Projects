#include "project1.h"

void insertion_sort(std::vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i) {
		int temp = nums[i];
		int j;
		for (j = i; j > 0 && nums[j-1] > temp; j--) {
			nums[j] = nums[j - 1];
		}
		nums[j] = temp;
	}
}