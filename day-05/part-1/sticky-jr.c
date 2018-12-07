#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    char stack[65536];
    unsigned int sp = 0;
    char* input = argv[1];

    while(*input != 0) {
        if (sp == 0) 
	    stack[++sp] = *input;
	else if ((*input - stack[sp]) == 32) 
	    --sp;
	else if ((stack[sp] - *input) == 32) 
	    --sp;
	else
	    stack[++sp] = *input;

	++input;
    }
    printf("%d\n",sp);
    return 0;
}
