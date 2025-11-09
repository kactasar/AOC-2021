#pragma once
#include <string>
#include <vector>

std::vector<int> load_input(const std::string& filename);
int count_increases_simple(const std::vector<int>& data);
int count_increases_sliding_window(const std::vector<int>& data);