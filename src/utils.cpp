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
// Function to calculate the first part of the puzzle:
// Calculate the final horizontal position and depth based on movement commands.
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

// Function to calculate the second part of the puzzle:
// Calculate the final horizontal position and depth based on movement commands with aim adjustment.
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

// Day 03
// Function to convert a binary string to its integer representation.
int binary_str_to_int(const std::string& str) {
	// Use std::stoi with base 2 to convert binary string to integer.
	// This will throw an exception if the string is not a valid binary representation.
	return std::stoi(str, nullptr, 2);
}

// Function to calculate the first part of the puzzle:
// Calculate the product of gamma rate and epsilon rate from vector of binary data strings.
unsigned long long calculate_gamma_epsilon_product(const std::vector<std::string>& data) {
	// n = number of lines in dataset
	// m = number of bits per line
	size_t n = data.size();
	size_t m = data.front().size();

	// Vector 'ones' to count number of '1's in each bit position (size 'm', initialized to 0).
	std::vector<int> ones(m, 0);
	for (const auto &s : data)
		for (size_t i = 0; i < m; ++i)
			ones[i] += (s[i] == '1');

	// gamma: most common bit in each position across all input lines.
	// epsilon: bitwise inverse of gamma (least common bit in each position).
	unsigned long long gamma = 0, epsilon = 0;
	// For each position: if ones > n/2, the most common bit is '1'.
	for (size_t i = 0; i < m; ++i) {
		bool most_common_is_one = (ones[i] > n / 2);
		// Build gamma and epsilon by shifting left and adding the new bit (the '<< 1' operation),
		// then setting the least significant bit according to the most common bit ( '| ...' operation).
		gamma = (gamma << 1) | (most_common_is_one ? 1ULL : 0ULL);
		// epsilon is the opposite bit of gamma at each position so the logic is inverted here.
		epsilon = (epsilon << 1) | (most_common_is_one ? 0ULL : 1ULL);
	}

	return gamma * epsilon;
}

unsigned long long calculate_life_support_rating(const std::vector<std::string>& data) {
	// Helper lambda function 'find rate' to find either oxygen generator rating or CO2 scrubber rating based on mode.
	// mode == '1' for oxygen generator rating (most common bit criteria)
	// mode == '0' for CO2 scrubber rating (least common bit criteria)
	auto find_rate = [&](char mode) -> unsigned long long {
		// Maintain a list of indices into `data` to avoid copying strings
		std::vector<int> idx(data.size());
		// Initialize indices to all entries in data.
		for (size_t i = 0; i < idx.size(); ++i) 
			// static_cast to convert size_t to int safely
			idx[i] = static_cast<int>(i);
		// 'm' is the number of bits in each binary string.
		size_t m = data.front().size(); 

		// For each bit position, compute counts among remaining candidates and filter.
		for (size_t pos = 0; pos < m && idx.size() > 1; ++pos) {
			// Count how many remaining candidates have '1' at this position.
			int ones = 0;
			for (int id : idx) if (data[id][pos] == '1') ++ones;
			int zeros = static_cast<int>(idx.size()) - ones;

			// Decide which bit to keep based on mode:
			// - mode == '1': keep the most common bit; if tied, keep '1'.
			// - mode == '0': keep the least common bit; if tied, keep '0'.
			char keep;
			if (mode == '1') keep = (ones >= zeros) ? '1' : '0';
			else             keep = (zeros <= ones) ? '0' : '1';

			// Build the next list of candidate indices that have the desired bit.
			std::vector<int> next;
			next.reserve(idx.size());
			for (int id : idx)
				if (data[id][pos] == keep)
					next.push_back(id);

			// Replace current candidate list with the filtered one.
			idx.swap(next);
		}

		// When only one candidate remains, convert its binary string to integer.
		return binary_str_to_int(data[idx.front()]);
	};

	// Multiply oxygen generator rating (most-common filter) by CO2 scrubber rating (least-common filter).
	return find_rate('1') * find_rate('0');
}

// Day 04

// Marks the called number on the bingo board if present by replacing it with -1
// and updating the horizontal and vertical line counters keeping track of marked numbers.
// Function exits after marking the first occurrence of the called number as there are no 
// duplicate numbers on a bingo board.
void Bingo_Board::mark_number(int called_number){
	for (auto& row : contents){
		for (auto& cell : row){
			if (cell == called_number){
				cell = -1;
				// Update the counters for the corresponding row and column.
				// '&row - &contents[0]' and '&cell - &row[0]' calculate the indices
				// using pointer arithmetic.			
				horizontal_lines[&row - &contents[0]] += 1;
				vertical_lines[&cell - &row[0]] += 1;
				return;
			}
		}
	}
}

// Checks if any horizontal or vertical line on the bingo board is fully marked.
bool Bingo_Board::any_line_marked(){
	for (int i = 0 ; i < BOARDSIZE ; i++){
		if ((horizontal_lines[i] == BOARDSIZE) || (vertical_lines[i] == BOARDSIZE))
			return true;
	}
	return false;
}

// Calculates the score of the bingo board by summing all unmarked numbers
// and multiplying the sum by the last called number as per puzzle rules.
int Bingo_Board::calculate_score(int called_number){
	int unmarked_sum {0};
	for (auto& row : contents){
		for (auto& cell : row){
			if (cell != -1)
				unmarked_sum += cell;
		}
	}
	return unmarked_sum * called_number;
}

// Load sequence of comma separated numbers for bingo from input file into a vector.
std::vector<int> load_bingo_sequence(std::istream& input_file) {
	int tmp;
	std::vector<int> bingo_sequence;
	while (input_file >> tmp){
		bingo_sequence.push_back(tmp);
        // Check for comma separator and ignore it
		if (input_file.peek() == ',')
			input_file.ignore(1);
		// Break if the next character is not a comma (end of sequence)
		else 
			break;
	}
    return bingo_sequence;
}

// Load bingo boards from input file into a vector of Bingo_Board structures.
std::vector<Bingo_Board> load_bingo_boards(std::istream& input_file) {
	std::vector<Bingo_Board> boards;
	while (true) {
    Bingo_Board tmp_board;
    for (auto& row : tmp_board.contents) {
        for (auto& cell : row) {
            if (!(input_file >> cell)) {
                // Stop if we run out of numbers mid-board to avoid adding incomplete boards
                return boards;
            }
        }
    }
    boards.push_back(tmp_board);
	}
	return boards;
}

// Function to calculate the score of the first winning bingo board.
int calculate_bingo_first_winner_score(const std::vector<int>& bingo_sequence, std::vector<Bingo_Board>& boards) {
	for (auto& called_number : bingo_sequence) {
		for (auto& board : boards) {
			board.mark_number(called_number);
			if (board.any_line_marked()) {
				// Exit the function by returning the score when the first winning board is found.
				return board.calculate_score(called_number);
			}
		}
	}
	// In case there is no winning board (which should not happen in a valid input), throw a runtime error.
	throw std::runtime_error("No winning board found in the provided sequence.");
}

// Function to calculate the score of the last winning bingo board.
int calculate_bingo_last_winner_score(const std::vector<int>& bingo_sequence, std::vector<Bingo_Board>& boards) {
	int last_score = -1;
	for (auto& called_number : bingo_sequence) {
		auto board = boards.begin();
		while (board != boards.end()) {
			board->mark_number(called_number);
			if (board->any_line_marked()) {
				last_score = board->calculate_score(called_number);
				// Remove the board that just won from the vector. Vector function erase() not only removes the element,
				// but also returns the next iterator after the erased one or end() if the last element was erased so we
				// use it to assign back to the 'board' variable.
				board = boards.erase(board);
			} else {
				// Only increment the iterator if we did not erase the current board.
				++board;
			}
		}
	}
	if (last_score == -1) {
		// If last_score was never updated, it means no board won. Throw a runtime error.
		throw std::runtime_error("No winning board found in the provided sequence.");
	}
	return last_score;
}