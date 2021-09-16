#include "project1.h"
#include <cmath>

void shell_sort2(std::vector<int>& nums) {
	int k = std::log(nums.size());
	for (int gap = std::pow(2, k)-1; gap > 0; --k, gap=std::pow(2, k) - 1) {
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