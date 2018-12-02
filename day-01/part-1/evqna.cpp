#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
    std::string in = argv[1];
    std::istringstream istream{in};
    std::string line;

    int sum = 0;
    while (std::getline(istream, line)) {
        sum += std::stoi(line);
    }
    std::cout << sum << "\n";

    return 0;
}
