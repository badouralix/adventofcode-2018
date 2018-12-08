#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int run(const string in) {
    istringstream istream(in);
    string line;

    int sum = 0;
    while (getline(istream, line))
        sum += stoi(line);

    return sum;
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
