#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> read_input(std::string input_str) {
  std::vector<std::string> ids;
  std::string line;
  std::stringstream input(input_str, std::ios_base::in);
  while (input >> line) {
    ids.push_back(line);
  }
  return ids;
}

inline uint_fast8_t compare(std::string &a, std::string &b) {
  uint_fast8_t dist(0);
  for (unsigned int i = 0; i < a.length(); ++i) {
    if (a[i] != b[i])
      ++dist;
  }
  return dist;
}

inline std::string compare_str(std::string &a, std::string &b) {
  std::string result{};
  for (unsigned int i = 0; i < a.length(); ++i) {
    if (a[i] == b[i])
      result+=a[i];
  }
  return result;
}

std::string run(std::string input_str) {
  std::vector<std::string> ids(read_input(input_str));
  std::vector<std::pair<int, int>> result;
  for (unsigned int i = 0; i < ids.size(); ++i) {
    for (unsigned int j = i + 1; j < ids.size(); ++j) {
      uint_fast8_t res = compare(ids[i], ids[j]);
      if (res == 1) {
        result.push_back({i,j});
      }
    }
  }
  return compare_str(ids[result[0].first], ids[result[0].second]);
}

int main(int argc, char **argv) {
  /*
   * Usage: <executable> <input>
   */
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }
  std::cout << run(argv[1]) << std::endl;
  return 0;
}
