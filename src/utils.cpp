#include "utils.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// Function to load integers from a file into a vector.
std::vector<int> load_input(const std::string& filename)
{
	std::ifstream input_file_stream(filename);
    // Throw an exception if the file cannot be opened.
    if (!input_file_stream)
		throw std::runtime_error("Failed to open input file: " + filename);

    std::vector<int> input_vector;
	for (int n; input_file_stream >> n; )
        input_vector.push_back(n);
	
    return input_vector;
}

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