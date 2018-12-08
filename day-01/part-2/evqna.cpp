#include <iostream>
#include <set>
#include <sstream>
#include <string>
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

int run(const string in) {
    auto commands = parse_input(in);
    
    int freq = 0;
    set<int> cache;

    size_t i = 0;
    do {
        cache.insert(freq);
        freq += commands[i++];
        if (i == commands.size())
            i = 0;
    } while (cache.find(freq) == cache.end());

    return freq;
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
