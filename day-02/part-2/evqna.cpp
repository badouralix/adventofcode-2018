#include <cstdio>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> parse_input(const std::string& in) {
    std::istringstream istream(in);
    std::vector<std::string> vec;
    for (std::string line; std::getline(istream, line); ) {
        vec.push_back(line);
    }
    return vec;
}

std::string part_2(const std::vector<std::string>& boxes) {
    int box_size = boxes[0].length();

    for (int i = 0; i < box_size; i++) {
        std::set<std::string> names;
        // Remove letter i from all names, check if 2 are equal
        for (auto& id : boxes) {
            std::string tmp = std::string(id).erase(i, 1);
            if (names.find(tmp) != names.end())
                return tmp;
            names.insert(tmp);
        }
    }

    return "";
}

int main(int argc, char *argv[]) {
    auto boxes = parse_input(argv[1]);

    printf("%s\n", part_2(boxes).c_str());

    return 0;
}
