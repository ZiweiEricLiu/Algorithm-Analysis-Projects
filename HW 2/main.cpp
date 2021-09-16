#include <iostream>
#include "project2.h"
#include <vector>
#include <random>
#include <cmath>
#include <ctime>

std::vector<double> generateItems(int size) {
	std::vector<double> nums;
	static	std::default_random_engine generator(std::time(0));
	std::uniform_real_distribution<double> distribution(0.0, 0.7);
	for (int i = 0; i < size; i++) {
		double rng = distribution(generator);
		nums.push_back(std::round(rng * 10.0) / 10.0);
	}
	return nums;
}

int main(int argc, char* argv[]) {
	int input_size = atoi(argv[2]);
	std::string fn_name = std::string(argv[1]);
	double waste = 0.0;
	int trials;
	if (input_size < 100000) {
		trials = 10;
	}
	else {
		trials = 5;
	}
	for (int i = 0; i < trials; i++) {
		std::vector<double> nums = generateItems(input_size);
		std::vector<int> assignment(nums.size(), 0);
		std::vector<double> free_space;
		if (fn_name == "NF") { next_fit(nums, assignment, free_space); }
		else if (fn_name == "FF") { first_fit(nums, assignment, free_space); }
		else if (fn_name == "BF") { best_fit(nums, assignment, free_space); }
		else if (fn_name == "FFD") { first_fit_decreasing(nums, assignment, free_space); }
		else if (fn_name == "BFD") { best_fit_decreasing(nums, assignment, free_space); }

		for (double d : free_space) {
			waste += d;
		}
	}
	
	std::cout << input_size << "," << waste / (1.0 * trials) << std::endl;

	return 0;
}