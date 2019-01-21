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

/**
 * return the sum of all metadata entries for the tree
 * rooted at data[i] and move i to the beginning of the next node
 */
int sumMetadata(const vector<int>& data, int& i) {
    int sum = 0;
    int nChildren = data[i++];
    int nMeta = data[i++];

    for (int k = 0; k < nChildren; k++)
        sum += sumMetadata(data, i);
    for (int k = 0; k < nMeta; k++)
        sum += data[i++];
    
    return sum;
}

int run(const string& s) {
    auto input = parse(s);

    int i = 0;
    return sumMetadata(input, i);
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
