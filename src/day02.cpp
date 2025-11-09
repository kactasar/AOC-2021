#include "utils.hpp"
#include <iostream>
#include <vector>
#include <sstream>

int main(){
	std::vector<std::string> data {load_input_string("data/day02_input.txt")};
	
	int xpart1{0}, ypart1{0};
	int xpart2{0}, ypart2{0}, aim{0};
	
	std::string command;
	int value;

	for(std::string line : data){
		std::istringstream line_stream(line);
		line_stream >> command >> value;


	while (input_file >> command){
		input_file >> value;
		if (command == "forward"){
			//Part 1 calculations:
			xpart1 += value;
			//Part 2 calculations:
			xpart2 += value;
			ypart2 += aim*value;
			continue;
		}
		if (command == "down"){
			//Part 1 calculations:
			ypart1 += value;
			//Part 2 calculations:
			aim += value;
			continue;
		}
		if (command == "up"){
			//Part 1 calculations:
			ypart1 -= value;
			//Part 2 calculations:
			aim -= value;
			continue;
		}
		std::cout << "Error: unknown command: " << command << std::endl;
		return 1;
	}
	
	std::cout << "Part 1: " << xpart1*ypart1 << std::endl;
	std::cout << "Part 2: " << xpart2*ypart2 << std::endl;
	
	return 0;
}
