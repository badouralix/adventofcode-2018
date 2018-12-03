#include <fstream>
#include <iostream>
#include <string>

int process(std::string filename) {
  int frq (0);
  int line;
  std::ifstream input;
  input.open(filename);
  if (input.is_open()){
    while (input >> line){
      frq += line;
    }
  }
  return frq;
}

int main(int argc, char **argv) {
  /*
   * Usage: <executable> <input file>
   */
  if (argc<2){
    std::cout << "No file was provided." << std::endl;
    return 0;
  }
  std::string filename (argv[1]);
  std::cout << process(filename) << std::endl;
  return 0;
}
