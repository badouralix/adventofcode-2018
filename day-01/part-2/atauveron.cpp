#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

std::vector<int> read_input(std::string filename){
  std::vector<int> res;
  int line;
  std::ifstream input;
  input.open(filename);
  if (input.is_open()){
    while (input >> line){
      res.push_back(line);
    }
  }
  return res;
}

int process(std::string filename) {
  std::vector<int> input (read_input(filename));
  std::unordered_set<int> frqs ({0});
  int frq (0);
  while(1){
    for (int& i:input){
      frq += i;
      if (frqs.find(frq)!=frqs.end()){
        return frq;
      }else{
        frqs.emplace(frq);
      }
    }
  }
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
  std::cout << "The first repeated frequency is: " << process(filename) << std::endl;
  return 0;
}