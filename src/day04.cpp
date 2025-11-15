#include "utils.hpp"
#include <iostream>

int main()
{	
	auto file_stream = std::ifstream("data/day04_input.txt");
	std::vector<int> bingo_sequence = load_bingo_sequence(file_stream);
	std::vector<Bingo_Board> boards = load_bingo_boards(file_stream);
	
	std::cout << "Part 1: " << calculate_bingo_first_winner_score(bingo_sequence, boards) << std::endl;
	std::cout << "Part 2: " << calculate_bingo_last_winner_score(bingo_sequence, boards) << std::endl;
	
	return 0;
}
