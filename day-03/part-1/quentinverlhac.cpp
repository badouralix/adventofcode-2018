#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string run(string s) {
    istringstream iss(s);
    string line;
    int const size(1000);
    int fabric[size][size];
    for(int i(0); i<size; ++i) {
        for(int j(0); j<size; ++j) {
            fabric[i][j] = 0;
        }
    }
    while(getline(iss, line)) {
        // left
        size_t beginning = line.find("@") + 2;
        size_t length = line.find(",") - beginning;
        int left = stoi(line.substr(beginning,  length));
        // right
        beginning = line.find(",") + 1;
        length = line.find(":") - beginning;
        int top = stoi(line.substr(beginning,  length));
        // width
        beginning = line.find(":") + 2;
        length = line.find("x") - beginning;
        int width = stoi(line.substr(beginning,  length));
        // top
        beginning = line.find("x") + 1;
        length = line.find("\\") - beginning;
        int height = stoi(line.substr(beginning,  length));
        // increment
        for(int i(0); i<width; ++i) {
            for(int j(0); j<height; ++j) {
                fabric[left + i][top + j] += 1;
            }
        }
    }
    int surfaceOverClaimed(0);
    for(int i(0); i<size; ++i) {
        for(int j(0); j<size; ++j) {
            if(fabric[i][j] > 1) {
                surfaceOverClaimed += 1;
            }
        }
    }
    return to_string(surfaceOverClaimed);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
