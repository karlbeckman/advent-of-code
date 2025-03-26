#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>

class Solution {
private:
  std::vector<int> left_list;
  std::vector<int> right_list;
public:
  Solution(std::ifstream& input_file);
  int findTotalDistance();
  int computeSimilarityScore();
};

int main() {
  std::ifstream input_file("input.txt");

  if (!input_file) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }

  Solution solution(input_file);
  auto total_distance = solution.findTotalDistance();
  std::cout << "Part 1: " << total_distance << std::endl;
  auto similarity_score = solution.computeSimilarityScore();
  std::cout << "Part 2: " << similarity_score << std::endl;

  return 0;
}

Solution::Solution(std::ifstream& input_file) {
  std::string line;
  int left, right;
  while (std::getline(input_file, line)) {
    std::stringstream ss(line);
    ss >> left >> right;
    left_list.push_back(left);
    right_list.push_back(right);
  }
  std::sort(left_list.begin(), left_list.end());
  std::sort(right_list.begin(), right_list.end());
}

int Solution::findTotalDistance() {
  int totalDistance = 0;
  for (size_t i = 0; i < left_list.size(); ++i) {
    totalDistance += std::abs(left_list[i] - right_list[i]);
  }
  return totalDistance;
}

int Solution::computeSimilarityScore() {
  int similarity_score = 0;
  for (const auto& element : left_list) {
    const int occurrences = std::count(right_list.begin(), right_list.end(), element);
    similarity_score += element * occurrences;
  }
  return similarity_score;
}