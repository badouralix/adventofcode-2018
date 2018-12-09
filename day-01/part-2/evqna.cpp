#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> parse_input(const string& in) {
    istringstream iss(in);
    vector<int> vec;
    for (string line; getline(iss, line); ) {
        vec.push_back(stoi(line));
    }
    return vec;
}

struct Val {
    int value;
    int index;      // The index of this value in the accumulation table

    bool operator<(const Val& b) const {
        return this->value < b.value;
    }
};

int mod(int n, int d) {
    int r = n % d;
    if (r < 0)  r += d;
    return r;
}

int run(const string& in) {
    auto commands = parse_input(in);
    
    // Iterate once over input and build frequency table
    set<int> seen = {0};
    vector<int> accumulator = {0};
    for (int i = 0; i < commands.size(); i++) {
        int freq = accumulator[i] + commands[i];
        // Check if freq is repeated during first iteration
        if (seen.find(freq) != seen.end())
            return freq;
        accumulator.push_back(freq);
        seen.insert(freq);
    }
    
    // On every following iteration, the frequency table is translated by this delta
    int runDelta = accumulator.back();
    if (runDelta == 0)
        return 0;

    accumulator.pop_back();
    
    unordered_map<int, vector<Val>> freqByModulus;
    for (int i = 0; i < accumulator.size(); i++)
        freqByModulus[mod(accumulator[i], runDelta)].push_back({accumulator[i], i});

    // Find frequencies in the same group with minimal difference
    int minDelta = -1, minIndex = -1, minFreq = -1;
    for (auto& pair : freqByModulus) {
        auto& values = pair.second;
        if (values.size() > 1) {
            // Sort the frequencies by value to find minimal delta in linear time
            sort(values.begin(), values.end());
            for (int i = 1; i < values.size(); i++) {
                int delta = values[i].value - values[i-1].value;
                // If mod is positive v[i-1] -> v[i]
                // If mod is negative v[i-1] <- v[i]
                int index = runDelta > 0 ? values[i-1].index : values[i].index;
                int freq = runDelta > 0 ? values[i].value : values[i-1].value;
                if (minDelta < 0 || delta < minDelta || (delta == minDelta && (minIndex < 0 || index < minIndex))) {
                    minDelta = delta;
                    minIndex = index;
                    minFreq = freq;
                }
            }
        }
    }

    return minFreq;
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
