#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POTS 500
#define TREESIZE 64
#define RULESNB 32

// Will contain 1 at pos n - POTS if pot number n has a plant
// For even generations
int pots[2 * POTS + 1];
// For odd generations
int pots2[2 * POTS + 1];

// Will hold the rules as a binary tree (1 means we should create a pot and 0 we should not)
// The tree starts by checking curr -2, then curr -1 then curr then curr + 1 then curr + 2
// If we are at index i , left child is at index 2*i + 1 and right child at 2*(i + 1)
// Left child means no pot while right child means there is a pot
int ruletree[TREESIZE];

#define printstate(p)                                \
    {                                                \
        for (int k = 0; k < 2 * POTS; ++k) {         \
            if (p[k] != 0) {                         \
                printf("pot: %d\n", k - POTS);       \
                for (int j = k; j < 2 * POTS; ++j) { \
                    if (p[j])                        \
                        printf("#");                 \
                    else                             \
                        printf(".");                 \
                }                                    \
                printf("\n\n");                      \
                break;                               \
            }                                        \
        }                                            \
    }

int cv(int x) {
    return x - POTS;
}

int build_idx(int l1, int l2, int curr, int r1, int r2) {
    int idx = 0;
    idx = 2 * idx + l1 + 1;
    idx = 2 * idx + l2 + 1;
    idx = 2 * idx + curr + 1;
    idx = 2 * idx + r1 + 1;
    idx = 2 * idx + r2 + 1;

    return idx;
}

char* parse_init(char* s) {
    // Skip header
    s += 15;
    for (int i = 0;; i++) {
        switch (*(s + i)) {
        case '#':
            pots[i + POTS] = 1;
            break;
        case '\n':
            return s + i;
        }
    }
}

void parse_rules(char* s) {
    int pot;
    for (int i = 0; i < RULESNB; ++i) {
        // Iterate over the rules
        pot = *(s + 9) == '#';

        // Write the rule in the tree
        ruletree[build_idx(*(s + 0) == '#', *(s + 1) == '#', *(s + 2) == '#', *(s + 3) == '#', *(s + 4) == '#')] = pot;
        if (*(s + 10) == '\0')
            return;

        s += 11;
    };
}

int next_state(int i, int p[2 * POTS]) {
    return ruletree[build_idx(p[i - 2], p[i - 1], p[i], p[i + 1], p[i + 2])];
}

int generate(int nb) {
    int count = 0;
    for (int i = 1; i <= nb; ++i) {
        if (i % 2 == 0) {
            for (int j = 2; j < 2 * POTS - 2; ++j) {
                pots[j] = next_state(j, pots2);
            }
        } else {
            for (int j = 2; j < 2 * POTS - 2; ++j) {
                pots2[j] = next_state(j, pots);
            }
        }
    }

    if (nb % 2) {
        for (int j = 2; j < 2 * POTS - 2; ++j) {
            if (pots[j])
                count += cv(j);
        }
    } else {
        for (int j = 2; j < 2 * POTS - 2; ++j) {
            if (pots2[j])
                count += cv(j);
        }
    }

    return count;
}

int run(char* s) {
    // Your code goes here
    s = parse_init(s);
    s += 2;
    parse_rules(s);
    return generate(21);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    clock_t start = clock();
    int answer = run(argv[1]);

    printf("_duration:%f\n%d\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
    return 0;
}
