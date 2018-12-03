#include <array>
#include <iostream>
#include <sstream>
#include <string>

int run(std::string input_str) {
  unsigned int two(0);
  unsigned int three(0);
  std::string line;
  std::stringstream input(input_str, std::ios_base::in);
  while (input >> line) {
    // Array of frequencies (initialized)
    std::array<uint_fast8_t, 26> occurences{};
    for (char &c : line) {
      uint_fast8_t index = (uint_fast8_t)c - 97; // Offset in ASCII table
      occurences[index] += 1;
    }
    bool flag_two(true);
    bool flag_three(true);
    for (auto &it : occurences) {
      if (flag_two && it == 2) {
        two += 1;
        flag_two = false;
      } else if (flag_three && it == 3) {
        three += 1;
        flag_three = false;
      }
    }
  }
  return two * three;
}

int main(int argc, char **argv) {
  /*
   * Usage: <executable> <input string>
   */
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }
  std::string input(argv[1]);
  std::cout << run(input) << std::endl;
  return 0;
}
