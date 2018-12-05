#include <ctime>
#include <iostream>
#include <list>
#include <string>

int run(std::string input) {
  bool modified(false);
  std::list<unsigned int> to_delete{};
  do {
    modified = false;
    to_delete = {};
    // Search for elements to delete
    unsigned int index(0);
    while (index < input.size() - 1) {
      int here = (int)input[index];
      int next = (int)input[index + 1];
      if (here - next == 32 || next - here == 32) {
        to_delete.push_back(index);
        modified = true;
        ++index;
      }
      ++index;
    }
    // Delete marked elements
    if (modified) {
      int nb_deleted(0);
      for (unsigned int it : to_delete) {
        input.erase(it - nb_deleted,2);
        nb_deleted += 2;
      }
    }
  } while (modified);
  return input.size();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }

  clock_t start = clock();
  int answer = run(argv[1]);

  std::cout << "_duration:" << float(clock() - start) * 1000.0 / CLOCKS_PER_SEC
            << '\n';
  std::cout << answer << '\n';
  return 0;
}
