#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#define MAX_DEPTH 1000

using namespace std;

typedef struct Node {
    int n, m, i, j, v, o_m, o_n;
    struct Node **children;
    int *ref;

    void update_m(int a) {
        m = a; o_m = a; j = 0;
        ref = new int[m];
    }

    void add_child(struct Node *child) {
        children[i++] = child;
    }

    void add_ref(int r) {
        ref[j++] = r;
    }
} Node;

typedef struct Stack {
    int top;
    Node **el;

    Node* pop(void) {
        return el[top--];
    }

    Node* peek(void) {
        return el[top];
    }

    void push(Node *n) {
        el[++top] = n;
    }

    bool empty(void) {
        return top < 0;
    }
} Stack;

Node* newNode(int n) {
    Node* node = new Node;
    node->v = 0;
    node->n = n; node->o_n = n; node->i = 0;
    node->m = -1; node->o_m = -1; node->j = 0;
    node->children = new Node*[n];
    node->ref = NULL;
    return node;
}

int calc_val(Node *node) {
    if (node->o_n == 0) {
        int sum = 0;
        for (int i = 0; i < node->o_m; i++) sum += node->ref[i];
        return sum;
    }
    int sum = 0, m;
    for (int i = 0; i < node->o_m; i++) {
        m = node->ref[i]-1;
        if (m >= 0 && m < node->o_n) {
            sum += calc_val(node->children[m]);
        }
    }

    return sum;
}

int run(string s) {
    istringstream sstream(s);
    int a;
    Node *el[MAX_DEPTH], *top, *parent;
    Stack stack = {-1, el};

    while (sstream >> a) {
        if (!stack.empty() && stack.peek()->n == 0 && stack.peek()->m == 0) {
            stack.pop();
        }
        if (stack.empty()) {
            top = newNode(a);
            stack.push(top);
            continue;
        }
        top = stack.peek();
        if (top->m == -1) {
            top->update_m(a);
            continue;
        }
        if (top->n == 0) {
            top->add_ref(a);
            top->m--;
            continue;
        }
        top->n--;
        parent = top;
        top = newNode(a);
        parent->add_child(top);
        stack.push(top);
    }

    return calc_val(top);
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
