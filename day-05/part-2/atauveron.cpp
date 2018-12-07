#include <array>
#include <ctime>
#include <deque>
#include <iostream>
#include <string>

int react(std::string &input, char del) {
  std::deque<char> list{};
  char del_capital(del - 32);
  for (char c : input) {
    if (c == del || c == del_capital) {
      // Ignore
      continue;
    } else if (list.empty()) {
      list.push_front(c);
    } else {
      int front = (int)list.front();
      int next = (int)c;
      if (front - next == 32 || next - front == 32) {
        list.pop_front();
      } else {
        list.push_front(c);
      }
    }
  }
  return list.size();
}

int run(std::string input) {
  // Alphabet used in the polymer
  std::array<char, 26> alphabet({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
  int min_loc(input.size());
  for (auto c : alphabet) {
    int tmp = react(input, c);
    if (tmp < min_loc) {
      min_loc = tmp;
    }
  }
  std::cerr << '\n';
  return min_loc;
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
