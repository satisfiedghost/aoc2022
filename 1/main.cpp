#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
  std::ifstream file;
  file.open("input.txt");
  std::string line;

  std::vector<std::vector<int>> items;

  int a;
  size_t idx = 0;
  items.push_back(std::vector<int>());

  while (std::getline(file, line)) {
    if (!line.size()) {
      idx++;
      items.push_back(std::vector<int>());
      continue;
    }
    a = std::stoi(line);
    items[idx].push_back(a);
  }

  std::vector<int> calories_per_elf;

  for (auto item : items) {
    int sum = 0;
    for (auto c : item) {
      sum += c;
    }
    calories_per_elf.push_back(sum);
  }

  std::sort(calories_per_elf.begin(), calories_per_elf.end());

  // just added this in `bc` because I'm too lazy to lookup how to reverse sort or iterate
  for (auto i : calories_per_elf) {
    std::cout << i << std::endl;
  }

  return 0;
}