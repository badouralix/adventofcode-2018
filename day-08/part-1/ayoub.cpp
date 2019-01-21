#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#define MAX_DEPTH 1000

using namespace std;

typedef struct Node {
    int n, m;
} Node;


typedef struct Stack {
    int top;
    Node *el;

    Node pop(void) {
        return el[top--];
    }

    Node peek(void) {
        return el[top];
    }

    void push(int n, int m) {
        top++;
        update_top(n, m);
    }

    void update_top(int n, int m) {
        el[top].n = n; el[top].m = m;
    }

    bool empty(void) {
        return top < 0;
    }
} Stack;

int run(string s) {
    istringstream sstream(s);
    int a, sum = 0;
    Node el[MAX_DEPTH], top;
    Stack *stack = new Stack;
    stack->top = -1;
    stack->el = el;

    while (sstream >> a) {
        if (!stack->empty() && stack->peek().n == 0 && stack->peek().m == 0) {
            stack->pop();
        }
        if (stack->empty()) {
            stack->push(a, -1);
            continue;
        }
        top = stack->peek();
        if (top.m == -1) {
            stack->update_top(top.n, a);
            continue;
        }
        if (top.n == 0) {
            sum += a;
            stack->update_top(top.n, top.m-1);
            continue;
        }
        stack->update_top(top.n-1, top.m);
        stack->push(a, -1);
    }

    return sum;
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
