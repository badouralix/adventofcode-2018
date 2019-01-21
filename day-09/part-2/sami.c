#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct marble {
    long int val;
    struct marble* next;
    struct marble* prev;
};

struct marble* new_marble(int v) {
    struct marble* m;
    m = (struct marble*)malloc(sizeof(struct marble));
    m->next = NULL;
    m->prev = NULL;
    m->val = v;
    return m;
}

long int run(char* s) {
    int players, points;
    sscanf(s, "%d players; last marble is worth %d points\n", &players, &points);

    // players points
    long int pp[players];
    for (int i = 0; i < players; ++i) {
        pp[i] = 0;
    }

    struct marble* m = new_marble(0);
    m->next = m;
    m->prev = m;

    struct marble* temp;

    long int highscore = 0;
    int player = 0;

    for (long int turn = 1; turn <= 100 * points; ++turn) {

        player = (turn - 1) % players;
        if (turn % 23 == 0) {
            // Remove the 7th marble left
            for (int i = 0; i < 7; ++i) {
                m = m->prev;
            }
            // Set the points for the current player
            pp[player] += turn + m->val;
            highscore = pp[player] > highscore ? pp[player] : highscore;

            // Remove this marble
            m->prev->next = m->next;
            m->next->prev = m->prev;
            temp = m->next;
            free(m);
            m = temp;
        } else {
            // Skip the current one
            m = m->next;
            temp = new_marble(turn);
            temp->next = m->next;
            temp->prev = m;
            m->next->prev = temp;
            m->next = temp;
            m = m->next;
        }
    }

    return highscore;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    clock_t start = clock();
    long int answer = run(argv[1]);

    printf("_duration:%f\n%ld\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
    return 0;
}
