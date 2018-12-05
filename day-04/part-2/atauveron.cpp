#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

std::map<std::string, std::string> read_input(std::string input_str) {
  std::map<std::string, std::string> result{};
  std::stringstream input(input_str, std::ios_base::in);
  std::string line;
  while (std::getline(input, line)) {
    std::string instant(line.substr(1, 16));
    std::string action(line.substr(19));
    result.insert({instant, action});
  }
  return result;
}

int run(std::string input_str) {
  // Ordered map, so ordered increasing by date
  std::map<std::string, std::string> input(read_input(input_str));
  std::unordered_map<int, unsigned int> time{};
  std::unordered_map<int, std::array<unsigned int, 60>> asleep{};
  // Guard id
  int guard(0);
  std::string date_previous{};
  bool is_asleep(false);
  unsigned int sleep(0);
  unsigned int wake(60);
  std::string date(input.begin()->first.substr(0, 10));
  // Loop over the data
  for (auto &it : input) {
    date_previous = date;
    date = it.first.substr(0, 10);
    // If we changed day, the guard slept until 1am the previous day
    if (date != date_previous && is_asleep) {
      is_asleep = false;
      time[guard] += (60 - sleep);
      for (unsigned int i = sleep; i < 60; ++i) {
        asleep[guard][i] += 1;
      }
    }
    // Read the log
    if (it.second[0] == 'G') {
      // New guard id
      guard = std::stoi(it.second.substr(7));
      is_asleep = false;
    } else if (it.second[0] == 'f') {
      // Guard falls asleep
      sleep = std::stoi(it.first.substr(14));
      is_asleep = true;
    } else if (it.second[0] == 'w') {
      // Guard wakes up
      wake = std::stoi(it.first.substr(14));
      is_asleep = false;
      time[guard] += (wake - sleep);
      for (unsigned int i = sleep; i < wake; ++i) {
        asleep[guard][i] += 1;
      }
    } else {
      std::cerr << "Unknown input\n";
    }
    if (guard == 0) {
      std::cerr << "guard cannot be 0\n";
    }
  }
  // Exploit the extracted data
  int id_max(0);
  unsigned int min_max(0);
  unsigned int max_loc(0);
  for (auto &it : asleep) {
    for (unsigned int i = 0; i < 60; ++i) {
      if (it.second[i] > max_loc) {
        id_max = it.first;
        min_max = i;
        max_loc = it.second[i];
      }
    }
  }
  return id_max * min_max; // FIXME
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing one argument" << std::endl;
    exit(1);
  }
  std::cout << run(argv[1]) << "\n";
  return 0;
}
