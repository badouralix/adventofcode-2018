#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

typedef struct Linked {
    int val;
    struct Linked *prev, *next;
} Linked;

Linked* newNode(int val, Linked* prev = NULL, Linked* next = NULL) {
    Linked* node = new Linked;
    node->val = val;
    node->prev = prev; node->next = next;
    return node;
}

int run(string s) {
    replace(s.begin(), s.end(), ' ', '-');
    int P = 9, N = 25;
    sscanf(s.c_str(), "%d-players;-last-marble-is-worth-%d-points", &P, &N);

    int high_score = 0, p = 0, scores[P];
    for (int i = 0; i < P; i++) scores[i] = 0;

    Linked *curr = newNode(0), *node(0), *one_away(0), *two_away(0), *seven_away(0);
    curr->next = curr;
    curr->prev = curr;

    for (int marble = 1; marble <= N; marble++) {
        if (marble % 23 == 0) {
            scores[p] += marble;
            seven_away = curr->prev->prev->prev->prev->prev->prev->prev;
            scores[p] += seven_away->val;
            seven_away->prev->next = seven_away->next;
            curr = seven_away->next;
            high_score = (high_score<scores[p])?scores[p]:high_score;
        } else {
            node = newNode(marble);
            one_away = curr->next;
            two_away = curr->next->next;
            one_away->next = node;
            two_away->prev = node;
            node->next = two_away;
            node->prev = one_away;
            curr = node;
        }
        p = (p+1)%P; 
    }

    return high_score;
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
