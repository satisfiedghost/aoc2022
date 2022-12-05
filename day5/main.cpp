#include <iostream>
#include <stack>
#include <array>
#include <string>
#include <fstream>
#include <deque>

// initial state of stacks
//[N]         [C]     [Z]
//[Q] [G]     [V]     [S]         [V]
//[L] [C]     [M]     [T]     [W] [L]
//[S] [H]     [L]     [C] [D] [H] [S]
//[C] [V] [F] [D]     [D] [B] [Q] [F]
//[Z] [T] [Z] [T] [C] [J] [G] [S] [Q]
//[P] [P] [C] [W] [W] [F] [W] [J] [C]
//[T] [L] [D] [G] [P] [P] [V] [N] [R]
// 1   2   3   4   5   6   7   8   9

// input modified from
// move x from y to z
// to
// x y z
// for ease of parsing

void init_stacks(std::array<std::stack<char>, 9>& stacks) {
  std::array<std::string, 9> strs = {
    "TPZCSLQN",
    "LPTVHCG",
    "DCZF",
    "GWTDLMVC",
    "PWC",
    "PFJDCTSZ",
    "VWGBD",
    "NJSQHW",
    "RCQFSLV"
  };

  size_t stack_idx = 0;
  for (auto str : strs) {
    for (std::string::size_type i = 0; i < str.size(); i++) {
      stacks[stack_idx].push(str[i]);
    }
    stack_idx++;
  }
}

int main() {
  std::deque<char> moved_crates;
  std::array<std::stack<char>, 9> stacks;
  init_stacks(stacks);

  int num, from, to;
  std::ifstream infile("input.txt");

  while (infile >> num >> from >> to) {
    std::cout << num << " " << from << " " << to << std::endl;
    from--;
    to--;

    // uncomment for part 1 solution
    //for (size_t i = 0; i < num; i++) {
    //  auto& c = stacks[from].top();
    //  stacks[to].push(c);
    //  stacks[from].pop();
    //}

    // part 2
    for (size_t i = 0; i < num; i++) {
      auto& c = stacks[from].top();
      moved_crates.push_back(c);
      stacks[from].pop();

    }

    while (!moved_crates.empty()) {
      stacks[to].push(moved_crates.back());
      moved_crates.pop_back();
    }
  }

  for (auto& stack : stacks) {
    std::cout << stack.top();
  }
  std::cout << std::endl;


  return 0;
}