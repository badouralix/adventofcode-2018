#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

const long long ITER = 50000000000LL;
const int STATE_SIZE = 2200;
const int OFFSET = 1050;

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
        // for (int i = min; i < max; i++) {
        for (int i = 0; i < buf.length(); i++) {
            if (buf[i] == '#')
                total += i - OFFSET;
        }
        return total;
    }

    void update() {
        // Assume the region grows by one in both directions
        string window = buf.substr(0, 5);
        for (int i = 2; i < buf.length() - 2; i++) {
            // string window = buf.substr(i - 2, 5);
            if (generators.find(window) != generators.end()) {
                buf[i] = '#';
            } else {
                buf[i] = '.';
            }
            window = window.substr(1) + buf[i + 3];
        }
        min -= 1;
        max += 1;
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
    
    // Compute 1000 iterations and assume all subsequent ones differ by a constant delta
    for (int iter = 1; iter <= 1000; iter++) {
        state.update();
    }

    int prevValue = state.value();
    state.update();
    int delta = state.value() - prevValue;

    return prevValue + (ITER - 1000) * delta;
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
