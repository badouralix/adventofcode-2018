#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRIDSIZE 300

int grid[GRIDSIZE + 1][GRIDSIZE + 1];

int fuel(int x, int y, int serial) {
    return (((((x + 10) * y + serial) * (x + 10)) / 100) % 10) - 5;
}

void run(char* s, int* x, int* y, int* size) {
    int serial, i, j, di, dj, max, temp;
    max = 0;
    sscanf(s, "%d", &serial);

    for (i = 1; i <= GRIDSIZE; ++i) {
        for (j = 1; j <= GRIDSIZE; ++j) {
            grid[i][j] = fuel(i, j, serial) + grid[i][j - 1] + grid[i - 1][j] - grid[i - 1][j - 1];
        }
    }

    for (int s = 1; s <= GRIDSIZE; s++) {
        for (i = s; i <= GRIDSIZE; ++i) {
            for (j = s; j <= GRIDSIZE; ++j) {
                temp = grid[i][j] - grid[i][j - s] - grid[i - s][j] + grid[i - s][j - s];
                if (temp > max) {
                    max = temp;
                    *x = i - s + 1;
                    *y = j - s;
                    *size = s;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    int x, y, size;
    clock_t start = clock();
    run(argv[1], &x, &y, &size);

    printf("_duration:%f\n%d,%d,%d\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, x, y, size);
    return 0;
}
