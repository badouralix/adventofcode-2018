#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int run(char* s)
{
    char *ptr_two = NULL,
         *ptr_three = NULL,
         *c = s;
    int ctr_two = 0,
        ctr_three = 0;
    int letter_count[ALPHABET_SIZE] = {},
        empty_array[ALPHABET_SIZE] = {};

    do {
        switch (*c) {

        case '\n':
        case '\0':
            if (ptr_two && letter_count[*ptr_two - 'a'] == 2) {
                ctr_two++;
            }
            if (ptr_three && letter_count[*ptr_three - 'a'] == 3) {
                ctr_three++;
            }
            if (ptr_two && ptr_three && *ptr_two == *ptr_three) {
                for (int i = 0; i < 26; i++) {
                    if (letter_count[i] == 2) {
                        ctr_two++;
                        break;
                    }
                }
            }
            memcpy(letter_count, empty_array, ALPHABET_SIZE * sizeof(int));
            ptr_two = NULL;
            ptr_three = NULL;
            break;

        default:
            letter_count[*c - 'a']++;
            switch (letter_count[*c - 'a']) {
            case 2:
                ptr_two = c;
                break;
            case 3:
                ptr_three = c;
                break;
            default:
                break;
            }
            break;
        }

        c++;
    } while (*(c-1) != '\0');

    return ctr_two * ctr_three;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }
    printf("%d\n", run(argv[1]));
    return 0;
}
