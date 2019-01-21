#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

string run(string s) {
    string   line;
    stringstream ss(s);
    int count2 = 0;
    int count3 = 0;

    while(getline(ss, line, '\n'))
    {
        map<char, int> lineMap;
        int has2 = 0, has3 = 0;
        for(int i = 0; i < line.length(); i++){
            lineMap[line[i]] += 1;
        }
        for(map<char, int>::const_iterator it = lineMap.begin(); it != lineMap.end(); ++it)
        {
            if(it->second == 2) {
                has2 = 1;
            }
            if(it->second == 3) {
                has3 = 1;
            }
        }
        count2 += has2;
        count3 += has3;
    }
    return to_string(count2*count3);
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}