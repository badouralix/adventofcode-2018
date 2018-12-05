#include <algorithm>
#include <iterator>
#include <cstdio>
#include <string>
#include <vector>

int abs(int x) {
    return x >= 0 ? x : -x;
}

int react_polymer(std::string polymer) {
    bool hasChanged;

    do {
        hasChanged = false;
        size_t i = 0;
        while (i < polymer.length() - 1) {
            if (abs(polymer[i] - polymer[i+1]) == 32) {     // Hack for lower/upper case check
                polymer.erase(i, 2);
                hasChanged = true;
                // Opti: backtrack one character
                if (i > 0)  i--;
            }
            else {
                i++;
            }
        }
    } while(hasChanged);

    return polymer.length();
}

int transform_react(std::string polymer, char atom) {
    polymer.erase(std::remove_if(polymer.begin(), polymer.end(),
                  [=](char c) { return c == atom || c == atom - 32; }),
                  polymer.end()
    );
    return react_polymer(polymer);
}

int solve(const std::string& input) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    std::vector<int> collapsed_lengths;
    std::transform(alphabet.begin(), alphabet.end(), std::back_inserter(collapsed_lengths),
                   [&](char atom) { return transform_react(input, atom); });

    return *std::min_element(collapsed_lengths.begin(), collapsed_lengths.end());
}

int main(int argc, char *argv[]) {
    auto input = std::string(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
