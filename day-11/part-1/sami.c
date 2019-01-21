#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRIDSIZE 300

int fuel(int x, int y, int serial) {
    return (((((x + 10) * y + serial) * (x + 10)) / 100) % 10) - 5;
}

void run(char* s, int* x, int* y) {
    int serial, i, j, di, dj, max, temp;
    max = 0;
    sscanf(s, "%d", &serial);

    for (i = 1; i < GRIDSIZE - 1; ++i) {
        for (j = 1; j < GRIDSIZE - 1; ++j) {
            temp = 0;
            for (di = 0; di < 3; ++di) {
                for (dj = 0; dj < 3; ++dj) {
                    temp += fuel(i + di, j + dj, serial);
                }
            }
            if (temp > max) {
                max = temp;
                *x = i;
                *y = j;
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    int x, y;
    clock_t start = clock();
    run(argv[1], &x, &y);

    printf("_duration:%f\n%d,%d\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, x, y);
    return 0;
}
