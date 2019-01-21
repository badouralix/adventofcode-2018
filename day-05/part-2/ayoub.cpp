#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Stack {
    struct Stack *prev;
    char val;
};

typedef struct Stack Stack;

bool react(char a, char b) {
    if (a >= 'a' && b < 'a') return a - ('a'-'A') == b;
    if (a < 'a' && b >= 'a') return b - ('a'-'A') == a;
    return false;
}

bool case_i_compare(char a, char b) {
    if (a >= 'a' && b < 'a') return a - ('a'-'A') == b;
    if (a < 'a' && b >= 'a') return b - ('a'-'A') == a;
    return a == b;
}

int shorten(const string &s, char ignore) {
    Stack *curr = NULL, *prev = NULL;
    int count = 0;
    for (char c: s) {
        if (case_i_compare(c, ignore)) continue;
        count++;
        curr = new Stack;
        curr->prev = prev;
        curr->val = c;
        if (curr->prev && react(curr->prev->val, curr->val)) {
            count -= 2;
            curr = curr->prev->prev;
        }
        prev = curr;
    }
    return count;
}

int run(string s) {
    int min = s.size(), count = 0;

    for (char c = 'a'; c <= 'z'; c++) {
        count = shorten(s, c);
        min = (count<min)?count:min;
    }

    return min;
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
