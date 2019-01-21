#include <iostream>
#include <stack>
#include <string>

using namespace std;

int abs(int x) {
    return x >= 0 ? x : -x;
}

int run(const string& input) {
    stack<char> stack;

    for (char c : input) {
        if (!stack.empty() && abs(c - stack.top()) == 32)   // Hack for lower/upper case check
            stack.pop();
        else
            stack.push(c);
    }

    return stack.size();
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
