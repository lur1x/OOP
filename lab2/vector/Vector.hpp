#pragma once

#include <vector>
#include <fstream>

std::vector<double> ReadNumbers(std::istream& input);
std::vector<double> ProcessNumbers(const std::vector<double>& numbers);
void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& output);