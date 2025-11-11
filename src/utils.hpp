#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

// Function to load data from a file into a vector.
template <typename T>
std::vector<T> load_input(const std::string& filename) {
	std::ifstream input_file_stream(filename);
    // Throw an exception if the file cannot be opened.
    if (!input_file_stream)
		  throw std::runtime_error("Failed to open input file: " + filename);

    std::vector<T> input_vector;
	for (T n; input_file_stream >> n; )
      input_vector.push_back(n);
	
    return input_vector;
}
// Specialization for string: read file line by line.
template <>
inline std::vector<std::string> load_input<std::string>(const std::string& filename) {
    std::ifstream input_file_stream(filename);
    // Throw an exception if the file cannot be opened.
    if (!input_file_stream)
        throw std::runtime_error("Failed to open input file: " + filename);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file_stream, line))
        lines.push_back(line);

    return lines;
}

// Day 01 specific utility functions.
int count_increases_simple(const std::vector<int>& data);
int count_increases_sliding_window(const std::vector<int>& data);

// Day 02 specific utility functions.
int calculate_final_position(const std::vector<std::string>& data);
int calculate_final_position_with_aim(const std::vector<std::string>& data);

// Day 03 specific utility functions.
int binary_str_to_int(const std::string& str);
unsigned long long calculate_gamma_epsilon_product(const std::vector<std::string>& data);
unsigned long long calculate_life_support_rating(const std::vector<std::string>& data);