#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASHSIZE 100000

typedef struct nlist* dict[HASHSIZE];
struct nlist {
    struct nlist* next;
    int key;
};

int lookup(dict* h, int key);
void set(dict* h, int key);
dict* new_dict(void);

dict* new_dict(void) {
    dict* h = NULL;
    h = (dict*)malloc(sizeof(dict));
    for (int i = 0; i < HASHSIZE; ++i) {
        (*h)[i] = NULL;
    }
    return h;
}

unsigned hash(int v) { return (v % HASHSIZE + HASHSIZE) % HASHSIZE; }

void set(dict* h, int key) {
    struct nlist* np;
    unsigned hashval;

    if (lookup(h, key) == 0) {
        // TODO check for malloc error
        np = (struct nlist*)malloc(sizeof(struct nlist));
        np->key = key;

        hashval = hash(key);
        np->next = (*h)[hashval];
        (*h)[hashval] = np;
    }
}

int lookup(dict* h, int key) {
    struct nlist* np;
    for (np = (*h)[hash(key)]; np != NULL; np = np->next) {
        if (key == np->key) {
            return 1;
        }
    }
    return 0;
}

int run(char* s) {
    int res = 0;
    int buffer = 0;
    char op = '\0';
    char* init = s;

    dict* h = new_dict();

    for (;;) {
        for (; *s != EOF && *s != '\0'; s++) {
            if (isdigit(*s))
                buffer = buffer * 10 + *s - '0';
            else {
                switch (*s) {
                case '+':
                case '-':
                    op = *s;
                    break;

                case '\n':
                    res = op == '+' ? res + buffer : res - buffer;

                    if (lookup(h, res) == 1)
                        return res;

                    set(h, res);
                    buffer = 0;
                }
            }
        }
        s = init;
        res = op == '+' ? res + buffer : res - buffer;
        buffer = 0;
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
