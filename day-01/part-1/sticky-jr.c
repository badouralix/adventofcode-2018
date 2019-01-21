#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    char* input = argv[1];
    int answer = 0, buf = 0, op = 0;

    clock_t start = clock();

    while (*input != 0) {
	    if (*input == '\n') {
		    answer += op?buf:-buf;
		    op = buf = 0;
	    }
	    else if (*input == '-') op = 1;
	    else if (*input == '+') ;
	    else buf = 10*buf + (int)(*input - '0');
	    
	    ++input;
    }
    answer += op?buf:-buf;

    printf("_duration:%f\n%d\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, -answer);
    return 0;
}
