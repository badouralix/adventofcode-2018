#include <algorithm>
#include <iterator>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>

int abs(int x) {
    return x >= 0 ? x : -x;
}

int react_polymer(const std::string& polymer) {
    std::stack<char> stack;

    for (char c : polymer) {
        if (!stack.empty() && abs(c - stack.top()) == 32)   // Hack for lower/upper case check
            stack.pop();
        else
            stack.push(c);
    }

    return stack.size();
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
