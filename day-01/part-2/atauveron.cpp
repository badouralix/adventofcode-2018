#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<int> read_input(std::string input_str) {
  std::vector<int> res;
  int line;
  std::stringstream input(input_str, std::ios_base::in);
  while (input >> line) {
    res.push_back(line);
  }
  return res;
}

int process(std::string input_str) {
  std::vector<int> input(read_input(input_str));
  std::unordered_set<int> frqs({0});
  int frq(0);
  while (1) {
    for (int &i : input) {
      frq += i;
      if (frqs.find(frq) != frqs.end()) {
        return frq;
      } else {
        frqs.emplace(frq);
      }
    }
  }
}

int main(int argc, char **argv) {
  /*
   * Usage: <executable> <input>
   */
  if (argc < 2) {
    std::cout << "No file was provided." << std::endl;
    return 0;
  }
  std::string input(argv[1]);
  std::cout << process(input) << std::endl;
  return 0;
}