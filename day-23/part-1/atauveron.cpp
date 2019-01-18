#include <array>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline int abs_diff(int a, int b) { return a > b ? a - b : b - a; }

inline std::vector<std::array<int, 4>> parse_input(const std::string &s) {
  std::vector<std::array<int, 4>> res{};
  std::stringstream input(s, std::ios_base::in);
  std::string line;
  while (std::getline(input, line)) {
    unsigned int index1 = line.find('<');
    unsigned int index2 = line.find(',', index1 + 1);
    unsigned int index3 = line.find(',', index2 + 1);
    unsigned int index4 = line.find('=', index3 + 1);
    // Values
    int x = std::stoi(line.substr(index1 + 1, index2 - index1 - 1));
    int y = std::stoi(line.substr(index2 + 1, index3 - index2 - 1));
    int z = std::stoi(line.substr(index3 + 1, index3 - index3 - 1));
    int r = std::stoi(line.substr(index4 + 1, line.size() - index4));
    res.push_back({x, y, z, r});
  }
  return res;
}

unsigned int run(std::string s) {
  std::vector<std::array<int, 4>> input = parse_input(s);
  // Find the element with the largest range
  int range(0);
  size_t index(0);
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i][3] > range) {
      range = input[i][3];
      index = i;
    }
  }
  // Count the number of bots in range
  std::array<int, 3> origin{input[index][0], input[index][1], input[index][2]};
  unsigned int count(0);
  for (size_t i = 0; i < input.size(); ++i) {
    int dist = abs_diff(origin[0], input[i][0]) +
               abs_diff(origin[1], input[i][1]) +
               abs_diff(origin[2], input[i][2]);
    if (dist <= range) {
      count += 1;
    }
  }
  return count;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }

  clock_t start = clock();
  auto answer = run(std::string(argv[1]));

  std::cout << "_duration:" << float(clock() - start) * 1000.0 / CLOCKS_PER_SEC
            << "\n";
  std::cout << answer << '\n';
  return 0;
}
