#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

// Apply rules (split, multiply or add 1).
std::vector<long long> applyRules(long long key) {
  std::vector<long long> stones;
  std::string key_str = std::to_string(key);
  int len = key_str.length();
  if ((len % 2) == 0) {
    std::string left_half_str = key_str.substr(0, len / 2);
    std::string right_half_str = key_str.substr(len / 2, len);
    
    int left_half = std::stoll(left_half_str);
    int right_half = std::stoll(right_half_str);
    
    stones.push_back(left_half);
    stones.push_back(right_half);
  } else {
    if (key == 0) {
      stones.push_back(1);
    } else {
      stones.push_back(key * 2024);
    }
  }
  return stones;
}

// Blink with your eyes.
std::map<long long, long long> blink(std::map<long long, long long>& numbers) {
  std::map<long long, long long> new_numbers;
  for (const auto& [key, value] : numbers) {
    std::vector<long long> stones = applyRules(key);
    for (auto& stone : stones) {
      if (new_numbers.find(stone) == new_numbers.end()) {
        new_numbers[stone] = value;
      } else {
        new_numbers[stone] += value;
      }
    }
  }
  return new_numbers;
}

// Solver function for part 1 and part 2.
void solve(std::map<long long, long long>& start_numbers) {
  std::map<long long, long long> numbers = start_numbers;
  for (int i = 1; i <= 75; ++i) {
    numbers = blink(numbers);
    if (i == 25) {
      long long stones = 0;
      for (const auto& [key, value] : numbers)
        stones += value;
      std::cout << "Part 1: " << stones << std::endl;
    } else if (i == 75) {
      long long stones = 0;
      for (const auto& [key, value] : numbers)
        stones += value;
      std::cout << "Part 2: " << stones << std::endl;
    }
  }
}

// Parse input and solve problem.
void parseInputAndSolve(std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Could not open the file: " << file_name << std::endl;
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    int number; 
    std::map<long long, long long> start_numbers;
    while (iss >> number) {
      if (start_numbers.find(number) == start_numbers.end()) {
        start_numbers[number] = 1;
      } else {
        start_numbers[number]++;
      }
    }
    solve(start_numbers);
  }
}

int main() {  
  parseInputAndSolve("input.txt");
  return 0;
}