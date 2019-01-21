#include <string>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

string run(string s) {
    string   line;
    int map[1000][1000] = {{0}};
    stringstream ss(s);
    int count = 0;
    while(getline(ss, line, '\n')){
        size_t at = line.find("@");
        size_t comma = line.find(",");
        size_t semi_colon = line.find(":");
        size_t multiplier = line.find("x");
        int x = stoi(line.substr(at + 1, comma - at - 1));
        int y = stoi(line.substr(comma + 1, semi_colon - comma - 1));
        int width = stoi(line.substr(semi_colon + 1, multiplier - semi_colon - 1));
        int height = stoi(line.substr(multiplier + 1, line.length() - multiplier - 1));
        for(int i = x; i < x + width; i++){
            for(int j = y; j < y + height; j++){
                if(++map[i][j] == 2){
                    count++;
                }
            }
        }
    }
    return to_string(count);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
