#include <stdio.h>

char* run(char* s)
{
    // Your code goes here
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }
    printf("%s\n", run(argv[1]));
    return 0;
}
