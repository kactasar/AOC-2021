#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(){
	// Load data from the input file into a vector for processing.
	// If the file is not found, cannot be opened, or contains no data an error message is printed
	// and the program returns with a non-zero exit code.
	std::vector<std::string> data {load_input<std::string>("data/day03_input.txt")};
	if(data.empty()){
		std::cout << "No data loaded." << std::endl;
		return 1;
	}

	std::cout << "Part 1: " << calculate_gamma_epsilon_product(data) << std::endl;
	std::cout << "Part 2: " << calculate_life_support_rating(data) << std::endl;

	return 0;
}
