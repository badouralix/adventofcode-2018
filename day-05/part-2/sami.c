#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int DELTA = 'A' - 'a';

int eq(char a, char b) {
    return ((a - b) == DELTA) || ((a - b) == -DELTA);
}

int collapse(char* s, char* buf, char f, int len, int min) {
    int j = 0;
    buf[0] = '\0';

    for (int i = 0; s[i] != '\0';) {
        if (s[i] == f || s[i] - f == DELTA) {
            i++;
            continue;
        }

        if (j >= min)
            return min;

        if (eq(buf[j], s[i])) {
            buf[j--] = '\0';
            i++;
        } else
            buf[++j] = s[i++];
    }

    return j;
}

int run(char* s) {
    int len = strlen(s);
    char* buf = (char*)malloc(sizeof(char) * (1 + len));

    int min = strlen(s);
    int c;

    for (int i = 'a'; i <= 'z'; ++i) {
        c = collapse(s, buf, i, len, min);
        min = c < min ? c : min;
    }

    return min;
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
