#include <string>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

string run(string s) {
    vector<int> points_x;
    vector<int> points_y;
    string   line;
    stringstream ss(s);
    while(getline(ss, line, '\n')){
        size_t pos = line.find(',');
        points_x.push_back(stoi(line.substr(0, pos)));
        points_y.push_back(stoi(line.substr(pos + 1)));
    }
    int minus = -10000;
    int plus = 10000;
    int total = 0;
    for(int i = minus; i < plus; i++){
        for(int j = minus; j < plus; j++){
            int distance = 0;
            for(int k = 0; k < points_x.size(); k++){
                distance += abs(points_x.at(k) - i) + abs(points_y.at(k) - j);
                if(distance > 10000){
                    break;
                }
            }
            if(distance < 10000){
                total++;
            }
        }
    }
    return to_string(total);
}

int main(int argc, char** argv) {
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
