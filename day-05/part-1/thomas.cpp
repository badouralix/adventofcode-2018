#include <iostream>
#include <string>
#include <ctime>
#include <stack>

using namespace std;

int run(string s) {
    stack<char> stack;
    for (char& c: s) {
        if (!stack.empty() && abs(c - stack.top()) == 32) {
            stack.pop();
        } else {
            stack.push(c);
        }
    }
    return stack.size();
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
