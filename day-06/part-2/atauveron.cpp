#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

inline int_fast16_t abs_diff(uint_fast16_t a, uint_fast16_t b) {
  return (int_fast16_t)((a > b) ? a - b : b - a);
}

inline std::vector<std::pair<uint_fast16_t, uint_fast16_t>>
parse_input(std::string &input_str) {
  std::stringstream input(input_str, std::ios_base::in);
  std::vector<std::pair<uint_fast16_t, uint_fast16_t>> result{};
  std::string line;
  while (std::getline(input, line)) {
    unsigned int x, y;
    sscanf(line.c_str(), "%u %*c %u", &x, &y);
    result.push_back({x, y});
  }
  return result;
}

int run(std::string input_str) {
  // Parse the input
  const std::vector<std::pair<uint_fast16_t, uint_fast16_t>> input(
      parse_input(input_str));
  // Extrema
  uint_fast16_t x_max(input.at(0).first), x_min(input.at(0).first),
      y_max(input.at(0).second), y_min(input.at(0).second);
  for (auto &it : input) {
    if (it.first > x_max) {
      x_max = it.first;
    }
    if (it.first < x_min) {
      x_min = it.first;
    }
    if (it.second > y_max) {
      y_max = it.second;
    }
    if (it.second < y_min) {
      y_min = it.second;
    }
  }
  // Array of bboleans (+50 for good measure)
  // Is this cell close enough to otthe nodes?
  const uint_fast16_t size_x(x_max + 50), size_y(y_max + 50);
  bool grid[size_x][size_y];
  for (uint_fast16_t i = 0; i < size_x; ++i) {
    for (uint_fast16_t j = 0; j < size_y; ++j) {
      int_fast16_t distance(0);
      for (uint_fast8_t id = 0; id < input.size(); ++id) {
        distance +=
            abs_diff(i, input[id].first) + abs_diff(j, input[id].second);
      }
      grid[i][j] = (distance < 10000);
    }
  }
  uint_fast32_t counter (0);
  for (uint_fast16_t i = 0; i < size_x; ++i) {
    for (uint_fast16_t j = 0; j < size_y; ++j) {
      if (grid[i][j]) {
        ++counter;
      }
    }
  }
  return counter;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }

  clock_t start = clock();
  auto answer = run(argv[1]);

  std::cout << "_duration:" << float(clock() - start) * 1000.0 / CLOCKS_PER_SEC
            << '\n';
  std::cout << answer << '\n';
  return 0;
}
