#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

const int STATE_SIZE = 200;
const int OFFSET = 50;

set<string> parseRules(const string& in, string& IV) {
    istringstream iss(in);
    string line;
    getline(iss, line);
    IV = line.substr(15);

    set<string> rules;
    while (getline(iss, line)) {
        if (!line.empty() && line[9] == '#')
            rules.insert(line.substr(0, 5));
    }
    return rules;
}

int totalValue(const string& state) {
    int total = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == '#')
            total += i - OFFSET;
    }
    return total;
}

void update(string& state, const set<string>& generators) {
    string window = state.substr(0, 5);
    for (int i = 2; i < state.size() - 2; i++) {
        if (generators.find(window) != generators.end())
            state[i] = '#';
        else
            state[i] = '.';
        window = window.substr(1) + state[i + 3];
    }
}

int run(const string& s) {
    string initialState;
    auto generators = parseRules(s, initialState);

    // All the state should fit in this array
    // Flower pot n is at state[n+offset]
    string state(STATE_SIZE, '.');
    state.replace(OFFSET, initialState.length(), initialState);    // Embed IV into state
    
    for (int iter = 1; iter <= 20; iter++) {
        update(state, generators);
    }

    return totalValue(state);
}

int main(int argc, char** argv) {
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
