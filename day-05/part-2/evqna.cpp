#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int abs(int x) {
    return x >= 0 ? x : -x;
}

int react_polymer(const string& polymer) {
    stack<char> stack;

    for (char c : polymer) {
        if (!stack.empty() && abs(c - stack.top()) == 32)   // Hack for lower/upper case check
            stack.pop();
        else
            stack.push(c);
    }

    return stack.size();
}

int transform_react(string polymer, char atom) {
    polymer.erase(remove_if(polymer.begin(), polymer.end(),
                  [=](char c) { return c == atom || c == atom - 32; }),
                  polymer.end()
    );
    return react_polymer(polymer);
}

int run(const string& input) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    vector<int> collapsed_lengths;
    transform(alphabet.begin(), alphabet.end(), back_inserter(collapsed_lengths),
                   [&](char atom) { return transform_react(input, atom); });

    return *min_element(collapsed_lengths.begin(), collapsed_lengths.end());
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
