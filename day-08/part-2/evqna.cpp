#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parse(const string& in) {
    vector<int> data;
    int n;
    istringstream iss(in);
    
    while (iss >> n)
        data.push_back(n);
    
    return data;
}

int nodeValue(const vector<int>& data, int& i) {
    int value = 0;
    vector<int> childrenValues;
    int nChildren = data[i++];
    int nMeta = data[i++];

    if (nChildren == 0) {
        for (int k = 0; k < nMeta; k++)
            value += data[i++];
    }
    else {
        for (int k = 0; k < nChildren; k++)
            childrenValues.push_back(nodeValue(data, i));

        for (int k = 0; k < nMeta; k++) {
            int meta = data[i++];
            if (meta >= 1 && meta <= nChildren)
                value += childrenValues[meta - 1];
        }
    }
    
    return value;
}

int run(const string& s) {
    auto input = parse(s);

    int i = 0;
    return nodeValue(input, i);
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
