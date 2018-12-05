#include <cstdio>
#include <stack>
#include <string>

int abs(int x) {
    return x >= 0 ? x : -x;
}

int solve(const std::string& input) {
    std::stack<char> stack;

    for (char c : input) {
        if (!stack.empty() && abs(c - stack.top()) == 32)   // Hack for lower/upper case check
            stack.pop();
        else
            stack.push(c);
    }

    return stack.size();
}

int main(int argc, char *argv[]) {
    auto input = std::string(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
