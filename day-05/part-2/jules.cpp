#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int reduce(string input) {
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
    return polymer.size();
}

string run(string s) {
    string   input;
    stringstream ss(s);
    getline(ss, input, '\n');
    int min = input.length();
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < chars.length(); i++){
        string modifiedInput = input;
        modifiedInput.erase(remove(modifiedInput.begin(), modifiedInput.end(), chars[i]), modifiedInput.end());
        modifiedInput.erase(remove(modifiedInput.begin(), modifiedInput.end(), char(tolower(chars[i]))), modifiedInput.end());
        int result = reduce(modifiedInput);
        if (result < min) {
            min = result;
        }
    }
    return to_string(min);
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}