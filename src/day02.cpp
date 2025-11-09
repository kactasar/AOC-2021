#include "utils.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(){
	// Load data from the input file into a vector for processing.
	// If the file is not found, cannot be opened, or contains no data an error message is printed
	// and the program returns with a non-zero exit code.
	std::vector<std::string> data {load_input<std::string>("data/day02_input.txt")};
	if(data.empty()){
		std::cout << "No data loaded." << std::endl;
		return 1;
	}
	
	std::cout << "Part 1: " << calculate_final_position(data) << std::endl;
	std::cout << "Part 2: " << calculate_final_position_with_aim(data) << std::endl;
	
	return 0;
}
