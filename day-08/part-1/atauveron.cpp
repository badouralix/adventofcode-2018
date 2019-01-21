#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

int recurse(std::stringstream &input) {
  int nb_children(0);
  int nb_metadata(0);
  int sum_metadata(0);
  input >> nb_children >> nb_metadata;
  if (nb_children > 0) {
    for (int i = 0; i < nb_children; ++i) {
      sum_metadata += recurse(input);
    }
  }
  if (nb_metadata > 0) {
    int metadata(0);
    for (int i = 0; i < nb_metadata; ++i) {
      input >> metadata;
      sum_metadata += metadata;
    }
  }
  return sum_metadata;
}

inline int run(std::string input_str) {
  std::stringstream input(input_str, std::ios_base::in);
  return recurse(input);
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
