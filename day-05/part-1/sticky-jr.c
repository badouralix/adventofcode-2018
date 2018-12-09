#include <stdio.h>
#include <time.h>

#define POP --sp
#define PUSH stack[++sp] = *input

char stack[65536];

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    unsigned int sp = 0;
    char* input = argv[1];

    clock_t start = clock();

    while(*input != 0) {
        if (sp == 0)                         PUSH;
	else if ((*input - stack[sp]) == 32) POP;
	else if ((stack[sp] - *input) == 32) POP;
	else                                 PUSH;

	++input;
    }

    printf("_duration:%f\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
    printf("%d\n",sp);

    return 0;
}
