#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

string run(string s) {
    string   input;
    stringstream ss(s);
    getline(ss, input, '\n');
    vector<char> polymer;
    for(int i=0; i < input.length(); i++){
        if (polymer.size() == 0) {
            polymer.push_back(input[i]);
        }
        else {
            if (polymer.back() != input[i] && tolower(polymer.back()) == tolower(input[i])){
                polymer.pop_back();
            } else {
                polymer.push_back(input[i]);
            }
        }
    }
    return to_string(polymer.size());
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}