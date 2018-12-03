#include <iostream>
#include <sstream>
#include <string>

int process(std::string input_str) {
  int frq(0);
  int line;
  std::stringstream input(input_str, std::ios_base::in);
  while (input >> line) {
    frq += line;
  }
  return frq;
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
