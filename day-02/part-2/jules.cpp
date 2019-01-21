#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string common(string s1, string s2) {
    // We consider those two strings to be of the same size
    string sameChars;
    for(int i = 0; i < s1.length(); i++){
        if(s1[i] == s2[i]) {
            sameChars += s1[i];
        }
    }
    return sameChars;
}

string run(string s) {
    string   line;
    stringstream ss(s);
    vector<string> words;
    while(getline(ss, line, '\n'))
    {
        words.push_back(line);
    }
    string minDist = "";
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        for (vector<string>::iterator it2 = it + 1; it2 != words.end(); ++it2){
            string dist = common(*it, *it2);
            if(dist.length() > minDist.length()){
                minDist = dist;
            }
        }
    }
    return minDist;
}

int main(int argc, char** argv) {
    cout << run(string(argv[1])) << "\n";
    return 0;
}