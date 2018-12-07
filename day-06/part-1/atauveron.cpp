#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

inline int_fast16_t abs_diff(unsigned int a, unsigned int b) {
  return (int_fast16_t)((a > b) ? a - b : b - a);
}

inline std::vector<std::pair<unsigned int, unsigned int>>
parse_input(std::string &input_str) {
  std::stringstream input(input_str, std::ios_base::in);
  std::vector<std::pair<unsigned int, unsigned int>> result{};
  std::string line;
  while (std::getline(input, line)) {
    unsigned int x;
    unsigned int y;
    sscanf(line.c_str(), "%u %*c %u", &x, &y);
    result.push_back({x, y});
  }
  return result;
}

int run(std::string input_str) {
  // Parse the input
  const std::vector<std::pair<unsigned int, unsigned int>> input(
      parse_input(input_str));
  // Extrema
  unsigned int x_max(input.at(0).first), x_min(input.at(0).first),
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
  // Array
  const unsigned int size_x(x_max), size_y(y_max);
  int_fast16_t closest[size_x][size_y];
  for (unsigned int i = 0; i < size_x; ++i) {
    for (unsigned int j = 0; j < size_y; ++j) {
      std::vector<int_fast16_t> dist(input.size(), 5000);
      for (unsigned int id = 0; id < dist.size(); ++id) {
        dist.at(id) =
            abs_diff(i, input.at(id).first) + abs_diff(j, input.at(id).second);
      }
      // Find the closest node
      int_fast16_t node(0);
      int counter(1);
      for (unsigned int id = 1; id < dist.size(); ++id) {
        if (dist.at(id) < dist.at(node)) {
          node = id;
          counter = 1;
        } else if (dist.at(id) == dist.at(node)) {
          counter += 1;
        }
      }
      if (counter == 1) {
        closest[i][j] = node;
      } else if (counter > 1) {
        closest[i][j] = -1;
      } else {
        std::cerr << "Error for " << i << '-' << j << '\n';
      }
    }
  }
  std::vector<int_fast16_t> area(input.size(), 0);
  for (unsigned int i = 0; i < size_x; ++i) {
    for (unsigned int j = 0; j < size_y; ++j) {
      if (closest[i][j] != -1) {
        area.at(closest[i][j]) += 1;
      }
    }
  }
  // If any area involves a border cell, it is infinite
  for (unsigned int i = 0; i < size_x; ++i) {
    int_fast16_t node1(closest[i][0]);
    int_fast16_t node2(closest[i][size_y - 1]);
    if (node1 >= 0) {
      area.at(node1) = -1;
    }
    if (node2 >= 0) {
      area.at(node2) = -1;
    }
  }
  for (unsigned int i = 0; i < size_y; ++i) {
    int_fast16_t node1(closest[0][i]);
    int_fast16_t node2(closest[size_x - 1][i]);
    if (node1 >= 0) {
      area.at(node1) = -1;
    }
    if (node2 >= 0) {
      area.at(node2) = -1;
    }
  }
  // Find the maximum
  uint_fast16_t max_id(0);
  for (unsigned int id = 0; id < area.size(); ++id) {
    // if (input.at(id).first == x_max || input.at(id).first == x_min ||
    //     input.at(id).second == y_max || input.at(id).second == y_min) {
    //   // Exclude points with infinite domains
    //   continue;
    // } else {
    // }
    // Compute the area
    if (area.at(id) > area.at(max_id)) {
      max_id = id;
    }
  }
  return area.at(max_id);
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
