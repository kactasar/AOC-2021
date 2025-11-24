#include "utils.hpp"
#include <iostream>

int main()
{
    std::vector<std::string> data {load_input<std::string>("data/day05_input.txt")};
	if(data.empty()){
		std::cout << "No data loaded." << std::endl;
		return 1;
	}
    std::vector<Vent_Line> vent_lines = load_vent_lines(data);

    std::array<std::array<int, ARRSIZE>, ARRSIZE> diagram{};
	draw_straight_lines(vent_lines, diagram);
	std::cout << "Part 1: " << count_overlaps(diagram) << std::endl;
	draw_diagonal_lines(vent_lines, diagram);
	std::cout << "Part 2: " << count_overlaps(diagram) << std::endl;

    return 0;
}