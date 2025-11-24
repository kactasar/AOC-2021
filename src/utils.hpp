#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <array>

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

// Day 04 specific utility functions.

// Bingo board structure, size and related methods.
constexpr int BOARDSIZE {5};
struct Bingo_Board{
	std::array< std::array<int, BOARDSIZE>, BOARDSIZE> contents {0};
	int horizontal_lines[BOARDSIZE] {0};
	int vertical_lines[BOARDSIZE] {0};
	
	void mark_number(int called_number);
	bool any_line_marked();
	int calculate_score(int called_number);
};
std::vector<int> load_bingo_sequence(std::istream& input_file);
std::vector<Bingo_Board> load_bingo_boards(std::istream& input_file);
int calculate_bingo_first_winner_score(const std::vector<int>& bingo_sequence, std::vector<Bingo_Board>& boards);
int calculate_bingo_last_winner_score(const std::vector<int>& bingo_sequence, std::vector<Bingo_Board>& boards);

// Day 05 specific utility functions.
constexpr int ARRSIZE = 1000;

struct Vent_Line{
	std::pair< int, int> start_point;
	std::pair< int, int> end_point;
	bool vertical{false};
	bool horizontal{false};
	bool diagonal_down{false};
	bool diagonal_up{false};
	
	Vent_Line(const std::pair< int, int>& first_point, const std::pair< int, int>& second_point);
	void draw_line_on_diagram(std::array<std::array<int, ARRSIZE>, ARRSIZE>& diagram) const;
};
std::vector<Vent_Line> load_vent_lines(const std::vector<std::string>& data);
void draw_straight_lines(const std::vector<Vent_Line>& vent_lines, std::array<std::array<int, ARRSIZE>, ARRSIZE>& diagram);
void draw_diagonal_lines(const std::vector<Vent_Line>& vent_lines, std::array<std::array<int, ARRSIZE>, ARRSIZE>& diagram);
int count_overlaps(const std::array<std::array<int, ARRSIZE>, ARRSIZE>& diagram);