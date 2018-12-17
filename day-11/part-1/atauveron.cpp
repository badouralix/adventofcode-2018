#include <array>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>

inline std::string run(std::string input) {
  int serial = std::stoi(input);
  // Power level for each cell
  std::array<std::array<long int, 300>, 300> cells;
  for (auto i = 0; i < 300; ++i) {
    for (auto j = 0; j < 300; ++j) {
      // Caution: the grid is 1-indexed
      int pwr = (i + 11) * (j + 1) + serial;
      pwr *= (i + 11);
      pwr = (pwr / 100) % 10;
      cells[i][j] = pwr - 5;
    }
  }
  // Find the maximum
  int max_loc(-32767);
  int i_max(0);
  int j_max(0);
  for (auto i = 0; i < 298; ++i) {
    for (auto j = 0; j < 298; ++j) {
      int tmp(0);
      for (auto i1 = 0; i1 < 3; ++i1) {
        for (auto j1 = 0; j1 < 3; ++j1) {
          tmp += cells[i+i1][j+j1];
        }
      }
      if (tmp > max_loc) {
        max_loc = tmp;
        i_max = i;
        j_max = j;
      }
    }
  }
  // Caution: the grid is 1-indexed
  return std::to_string(i_max + 1) + ',' + std::to_string(j_max + 1);
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
