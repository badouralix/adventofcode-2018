#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

string run(string s) {
    string   line;
    stringstream ss(s);
    int output = 0;

    while(getline(ss, line, '\n'))
    {
        int value;
        value = atoi(line.c_str());
        output += value;
    }
    return to_string(output);
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}