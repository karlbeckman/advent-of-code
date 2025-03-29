#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

bool is_level_ok(const std::vector<int>& numbers) {
  if (numbers.size() < 2) return false;

  bool increasing = true;
  bool decreasing = true;

  for (size_t i = 1; i < numbers.size(); ++i) {
    int diff = numbers[i -1] - numbers[i];
    if (std::abs(diff) < 1 || std::abs(diff) > 3) {
      return false;
    }
    if (diff < 0) {
      increasing = false;
    }
    if (diff > 0) {
      decreasing = false;
    }
  }

  return increasing || decreasing;
}

bool is_level_ok_with_removal(const std::vector<int>& numbers) {
  for (size_t i = 0; i < numbers.size(); ++i) {
    std::vector<int> modified_numbers = numbers;
    modified_numbers.erase(modified_numbers.begin() + i);
    if (is_level_ok(modified_numbers)) {
      return true;
    }
  }

  return false;
}

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return 1;
  }

  int ok_count_part1 = 0;
  int ok_with_removal = 0;
  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream iss(line);
    std::vector<int> numbers;
    int number;

    // Read numbers from the line
    while (iss >> number) {
      numbers.push_back(number);
    }

    // Check if the level is ok
    if (is_level_ok(numbers)) {
      ok_count_part1++;
    } else {
      if (is_level_ok_with_removal(numbers)) {
        ok_with_removal++;
      }
    }
  }
  int ok_count_part2 = ok_count_part1 + ok_with_removal;

  input_file.close();
  std::cout << "Part 1: " << ok_count_part1 << std::endl;
  std::cout << "Part 2: " << ok_count_part2 << std::endl;
  return 0;
}