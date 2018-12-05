#include <iostream>
#include <string>

using namespace std;

string run(string s) {
    // Your code goes here
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
