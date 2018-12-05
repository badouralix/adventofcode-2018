#include <ctime>
#include <deque>
#include <iostream>
#include <string>

int run(std::string input) {
  std::deque<char> list{};
  for (char c : input) {
    if (list.empty()) {
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
