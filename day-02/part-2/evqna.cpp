#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> parse_input(const string& in) {
    istringstream iss(in);
    vector<string> vec;
    for (string line; getline(iss, line); ) {
        vec.push_back(line);
    }
    return vec;
}

string run(const string& in) {
    auto boxes = parse_input(in);
    int box_size = boxes[0].length();

    for (int i = 0; i < box_size; i++) {
        set<string> names;
        // Remove letter i from all names, check if 2 are equal
        for (const auto& id : boxes) {
            string tmp = string(id).erase(i, 1);
            if (names.find(tmp) != names.end())
                return tmp;
            names.insert(tmp);
        }
    }

    return "";
}

int main(int argc, char **argv) {
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
