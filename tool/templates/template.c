#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char* run(char* s) {
    // Your code goes here
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }

    clock_t start = clock();
    char* answer = run(argv[1]);
    
    printf("_duration:%f\n%s\n", (float)( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC, answer);
    return 0;
}
