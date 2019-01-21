#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int recurse(const std::vector<int> &input, int &index) {
  int node_value(0);
  int nb_children(input[index]);
  int nb_metadata(input[index + 1]);
  index += 2;
  if (nb_children == 0) {
    for (int i = 0; i < nb_metadata; ++i) {
      node_value += input[index];
      ++index;
    }
  } else {
    std::vector<int> children_values{};
    for (int i = 0; i < nb_children; ++i) {
      children_values.push_back(recurse(input, index));
    }
    for (int i = 0; i < nb_metadata; ++i) {
      int child = input[index];
      if (0 < child && child <= nb_children) {
        node_value += children_values[child-1];
      }
      ++index;
    }
  }
  return node_value;
}

inline std::vector<int> read_input(std::string &input_str) {
  std::stringstream input(input_str, std::ios_base::in);
  int value;
  std::vector<int> result{};
  while (input >> value) {
    result.push_back(value);
  }
  return result;
}

inline int run(std::string input_str) {
  std::vector<int> input(read_input(input_str));
  int i(0);
  return recurse(input, i);
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
