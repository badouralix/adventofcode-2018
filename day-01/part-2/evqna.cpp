#include <cstdio>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parse_input(const std::string& in) {
    std::istringstream iss(in);
    std::vector<int> vec;
    for (std::string line; std::getline(iss, line); ) {
        vec.push_back(std::stoi(line));
    }
    return vec;
}

int part_2(const std::vector<int>& commands) {
    int freq = 0;
    std::set<int> cache;

    size_t i = 0;
    do {
        cache.insert(freq);
        freq += commands[i++];
        if (i == commands.size())
            i = 0;
    } while (cache.find(freq) == cache.end());

    return freq;
}

int main(int argc, char *argv[]) {
    auto commands = parse_input(argv[1]);

    printf("%d\n", part_2(commands));

    return 0;
}
