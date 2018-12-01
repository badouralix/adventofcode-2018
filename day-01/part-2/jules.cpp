#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

string run(string s) {
    string   line;
    int output = 0;
    set<int> freqs;
    freqs.insert(0);

    while (true) {
        stringstream ss(s);
        while(getline(ss, line, '\n'))
        {
            int value;
            value = atoi(line.c_str());
            output += value;
            if(freqs.count(output) == 1) {
                return to_string(output);
            }
            freqs.insert(output);
        }
    }
    return to_string(0);
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}