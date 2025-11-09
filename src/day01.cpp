#include "utils.hpp"
#include <iostream>
#include <vector>

int main(){
	// Load data from the input.txt file into a vector for processing.
	// If the file is not found, cannot be opened, or contains no data an error message is printed
	// and the program returns with a non-zero exit code.
	std::vector<int> data {load_input("data/day01_input.txt")};
	if(data.empty()){
		std::cout << "No data loaded." << std::endl;
		return 1;
	}

	std::cout << "Part 1: " << count_increases_simple(data) << std::endl;
	std::cout << "Part 2: " << count_increases_sliding_window(data) << std::endl;
	
	return 0;
}
