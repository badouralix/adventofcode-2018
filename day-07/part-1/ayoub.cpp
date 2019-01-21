#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

#define SIZE 26

using namespace std;

bool ready(int i, bool seen[SIZE], bool rel[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        if (rel[j][i] && !seen[j]) return false;
    }
    return true;
}

bool any(bool q[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (q[i]) return true;
    }
    return false;
}

int pop(bool q[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (q[i]) {
            q[i] = false;
            return i;
        }
    }
    return -1;
}

string run(string s) {
    istringstream ss(s);
    string line;
    char p, c, path[SIZE+1];

    bool rel[SIZE][SIZE];
    bool has_parents[SIZE], seen[SIZE], queue[SIZE];

    for (int i = 0; i < SIZE; i++) {
        has_parents[i] = false; seen[i] = false; queue[i] = false;
        for (int j = 0; j < SIZE; j++) {
            rel[i][j] = false;
        }
    }

    while (getline(ss, line)) {
        replace(line.begin(), line.end(), ' ', '-');
        sscanf(line.c_str(), "Step-%c-must-be-finished-before-step-%c-can-begin.", &p, &c);
        rel[p - 'A'][c - 'A'] = true;
        has_parents[c - 'A'] = true;
    }

    int start = -1;
    for (int i = 0; i < SIZE; i++) {
        if (!has_parents[i]) {
            start = i;
            break;
        }
    }

    int k = -1, current;

    queue[start] = true;
    while (any(queue)) {
        current = pop(queue);
        seen[current] = true;
        path[++k] = 'A'+current;
        for (int i = 0; i < SIZE; i++) {
            if (ready(i, seen, rel) && !seen[i]) queue[i] = true;
        }
    }
    path[++k] = '\0';

    return string(path);
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
