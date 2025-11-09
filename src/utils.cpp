#include "utils.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>

// Day 01
// Function for solving first part of the puzzle:
// Count how many times a measurement increases from the previous one.
int count_increases_simple(const std::vector<int>& data){
    int count {0};
	// Procede only if there are at least two elements to compare.
	if (data.size() >= 2) {
		for (size_t i = 1; i < data.size(); ++i) {
			// Compare current element with the previous one and increment count if there is an increase.
            if (data[i-1] < data[i])
                count++;
		}
	}
    return count;
}
// Function for solving second part of the puzzle:
// Count how many times a measurement increases from the previous one, but for three-measurement-wide sliding window.
int count_increases_sliding_window(const std::vector<int>& data){
	int count {0};
	// As before, procede only if there are at least two elements to compare, but this time we need 
    // at least four elements to form two sliding windows.
	if (data.size() >= 4) {
		for (size_t i = 0; i + 3 < data.size(); ++i) {
            // Elements in the middle of the slididing windows cancel out, so we only need to compare
            // the first and the last elements of the windows (data[i+1] and data[i+2] are present in 
            // both windows and thus do not affect the comparison).
			if (data[i] < data[i+3]) ++count;
		}
	}
    return count;
}

// Day 02
int calculate_final_position(const std::vector<std::string>& data){
	int x{0}, y{0};	

	// Iterate through each line of input data to separate commands and their values.
	for(const std::string& line : data){
		std::string command;
		int value;
		std::istringstream line_stream(line);
		
		line_stream >> command >> value;
		// In case of input error the failbit is set so we check the stream state and throw an exception if needed.
		if (line_stream.fail()) {
			throw std::runtime_error("Error: invalid input line: " + line);
		}
		
		// Process each command accordingly and throw an exception if an unknown command is encountered.
		if (command == "forward"){
			x += value;
		} else if (command == "down"){
			y += value;
		} else if (command == "up"){
			y -= value;
		} else {
			throw std::runtime_error("Error: unknown command: " + command);
		}
	}

	// Return the product of the final horizontal position and depth.
	return x * y;
}

int calculate_final_position_with_aim(const std::vector<std::string>& data){
	int x{0}, y{0}, aim{0};	

	// Iterate through each line of input data to separate commands and their values.
	for(const std::string& line : data){
		std::string command;
		int value;
		std::istringstream line_stream(line);

		line_stream >> command >> value;
		// In case of input error the failbit is set so we check the stream state and throw an exception if needed.
		if (line_stream.fail()) {
			throw std::runtime_error("Error: invalid input line: " + line);
		}

		// Process each command accordingly and throw an exception if an unknown command is encountered.
		if (command == "forward"){
			x += value;
			y += aim * value;
		} else if (command == "down"){
			aim += value;
		} else if (command == "up"){
			aim -= value;
		} else {
			throw std::runtime_error("Error: unknown command: " + command);
		}
	}

	// Return the product of the final horizontal position and depth.
	return x * y;
}
