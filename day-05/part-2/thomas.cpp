#include <iostream>
#include <string>
#include <ctime>
#include <stack>

using namespace std;

stack<char> reduce(const string& s) {
    stack<char> stack;
    for (char c: s) {
        if (!stack.empty() && abs(c - stack.top()) == 32) {
            stack.pop();
        } else {
            stack.push(c);
        }
    }
    return stack;
}

int run(string s) {
    stack<char> stack = reduce(s);
    int mini = s.length();
    for (int ignore_char = 65; ignore_char<92; ignore_char++) { // iterate over alphabet
        std::stack<char> substack;
        for (char& c: s) {
            if (!substack.empty() && abs(c - substack.top()) == 32) {
                substack.pop();
            } else if (c != ignore_char && c != ignore_char + 32) {
                substack.push(c);
            }
        }
        if (substack.size() < mini) {
            mini = substack.size();
        }
    }
    return mini;
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
