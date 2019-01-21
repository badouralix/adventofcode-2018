#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRIDSIZE 1000

static unsigned int grid[GRIDSIZE][GRIDSIZE];

// parse a number and stops at the first non digit char
char* parse_number(char* s, int* x) {
    *x = 0;
    for (; isdigit(*s); s++)
        *x = 10 * (*x) + *s - '0';

    return s;
}

// jumps to next_number
char* next_number(char* s) {
    for (; !isdigit(*s); s++)
        ;
    return s;
}

char* parsenext(char* s, int* x) { return parse_number(next_number(s), x); }

char* parse_rect(char* l, int* c) {
    int id, x, y, w, h;
    id = x = y = w = h = 0;
    l++;
    l = parsenext(l, &id);
    l = parsenext(l, &x);
    l = parsenext(l, &y);
    l = parsenext(l, &w);
    l = parsenext(l, &h);

    /* printf("#%d @ %d,%d: %dx%d\n", id, x, y, w, h); */
    for (int i = x; i < x + w; ++i)
        for (int j = y; j < y + h; ++j) {
            switch (grid[i][j]) {
            case 0:
                grid[i][j] = 1;
                break;
            case 1:
                grid[i][j] = 2;
                (*c)++;
                break;
            }
        }

    return l;
}

int run(char* s) {
    int count = 0;

    for (;; s++) {
        s = parse_rect(s, &count);
        if (*s == '\0')
            return count;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }
    clock_t start = clock();
    int answer = run(argv[1]);

    printf("_duration:%f\n%d\n",
        (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
    return 0;
}
