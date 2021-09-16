#include "project1.h"

void shell_sort1(std::vector<int>& nums) {
	for (int gap = nums.size() / 2; gap > 0; gap /= 2) {
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