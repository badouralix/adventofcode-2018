#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <climits>

#define SIZE 26
#define WORKERS 5
#define OFFSET 61

using namespace std;


typedef struct Worker {
    int task, done_at;
} Worker;

bool ready(int i, bool done[SIZE], bool rel[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        if (rel[j][i] && !done[j]) return false;
    }
    return true;
}

bool any(bool q[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (q[i]) return true;
    }
    return false;
}

bool all(bool q[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (!q[i]) return false;
    }
    return true;
}


bool all_busy(Worker worker[WORKERS]) {
    for (int w = 0; w < WORKERS; w++) {
        if (worker[w].task == -1) return false;
    }
    return true;
}

int run(string s) {
    istringstream ss(s);
    string line;
    char p, c;

    bool rel[SIZE][SIZE];
    bool has_parents[SIZE], done[SIZE], available[SIZE], assigned[SIZE];
    Worker worker[WORKERS];

    for (int i = 0; i < SIZE; i++) {
        has_parents[i] = false; done[i] = false; available[i] = false; assigned[i] = false;
        worker[i%WORKERS].task = -1;
        worker[i%WORKERS].done_at = 0;
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


    int task, t = 0, next_time;
    available[start] = true;

    while (!all(done)) {
        next_time = INT_MAX;

        for (int w = 0; w < WORKERS; w++) {
            if (worker[w].task == -1) continue;
            if (worker[w].done_at == t) {
                done[worker[w].task] = true;
                worker[w].task = -1;
            } else if (worker[w].done_at > t) {
                next_time = (next_time>worker[w].done_at)?worker[w].done_at:next_time;
            }
        }

        if (all(done)) break;

        for (int i = 0; i < SIZE; i++) {
            available[i] = (!done[i] && !assigned[i] && ready(i, done, rel));
        }
    
        for (task = 0; task < SIZE; task++) {
            if (!available[task]) continue;
            for (int w = 0; w < WORKERS; w++) {
                if (worker[w].task == -1) {
                    worker[w].task = task;
                    worker[w].done_at = t + task + OFFSET;
                    available[task] = false;
                    assigned[task] = true;
                    next_time = (next_time>worker[w].done_at)?worker[w].done_at:next_time;
                    break;
                }
            }
        }
        t = next_time;
    }
    
    return t;
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
