#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

const long long ITER = 50000000000LL;
// Bunch of heuristics to reduce problem space
const int STATE_SIZE = 2200;    // Should be large enough to hold all simulated vectors
const int OFFSET = 1050;
const int TAU = 3;              // How many equal deltas do we need to see before we assume problem is stationary

struct State {
    string buf;
    int min, max;
    set<string> generators;

    void setInitialState(const string& IV) {
        buf.replace(OFFSET, IV.length(), IV);
        min = OFFSET;
        max = OFFSET + IV.length();
    }

    int value() const {
        int total = 0;
        for (int i = min; i < max; i++) {
            if (buf[i] == '#')
                total += i - OFFSET;
        }
        return total;
    }

    void update() {
        // Assume the region grows by at most one in both directions
        string window = buf.substr(min-3, 5);
        for (int i = min-1; i <= max+1; i++) {
            if (generators.find(window) != generators.end()) {
                buf[i] = '#';
            } else {
                buf[i] = '.';
            }
            window = window.substr(1) + buf[i + 3];
        }

        min--;
        max++;
    }
};

State parse(const string& in) {
    State state;
    state.buf = string(STATE_SIZE, '.');

    istringstream iss(in);
    string line;
    getline(iss, line);
    state.setInitialState(line.substr(15));

    while (getline(iss, line)) {
        if (!line.empty() && line[9] == '#')
            state.generators.insert(line.substr(0, 5));
    }
    return state;
}

long long run(const string& s) {
    auto state = parse(s);
    
    int prevValue = state.value();
    int prevDelta = prevValue;
    // Break early as soon as we see n identical delta in a row (heuristic)
    int counter = TAU;

    for (int iter = 1; iter <= ITER; iter++) {
        state.update();
        int delta = state.value() - prevValue;
        
        if (delta == prevDelta) {
            counter--;
            // Assume all next deltas will be identical
            if (counter == 0)
                return state.value() + (ITER - iter) * delta;
        } else {
            counter = TAU;
        }

        prevValue = state.value();
        prevDelta = delta;
    }

    return 0;
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
