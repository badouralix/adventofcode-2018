#include <array>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

inline std::vector<std::array<int, 5>> read_input(std::string input_str) {
  std::vector<std::array<int, 5>> result{};
  std::stringstream input(input_str, std::ios_base::in);
  std::string line;
  while (std::getline(input, line)) {
    unsigned int index1 = line.find("@");
    unsigned int index2 = line.find(',');
    unsigned int index3 = line.find(':');
    unsigned int index4 = line.find('x');
    // Values
    int id = std::stoi(line.substr(1, index1 - 2));
    int left = std::stoi(line.substr(index1 + 1, index2 - index1 - 1));
    int top = std::stoi(line.substr(index2 + 1, index3 - index2 - 1));
    int width = std::stoi(line.substr(index3 + 1, index4 - index3 - 1));
    int height = std::stoi(
        line.substr(index4 + 1, line.size() - index4)); // +1 -1 cancels out
    result.push_back({left, top, width, height, id});
  }
  return result;
}

int run(std::string input_str) {
  std::vector<std::array<int, 5>> input(read_input(input_str));
  std::array<std::array<int, 1000>, 1000> fabric{};
  std::set<int> non_overlap{};
  for (auto &it : input){
    bool overlap (false);
    for (int i = it[0]; i < it[0] + it[2]; ++i) {
      for (int j = it[1]; j < it[1] + it[3]; ++j) {
        if (fabric[i][j] != 0){
          non_overlap.erase(fabric[i][j]);
          overlap = true;
        }
        fabric[i][j] = it[4];
      }
    }
    if (!overlap){
      non_overlap.insert(it[4]);
    }
  }
  return *(non_overlap.begin());
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }
  std::cout << run(argv[1]) << std::endl;
  return 0;
}
