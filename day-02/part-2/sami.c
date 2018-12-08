#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASHSIZE 1000
const int MAXSIZE = 26;

typedef struct nlist* dict[HASHSIZE];

struct nlist {
    struct nlist* next;
    char* name;
    int v;
};

char* strsep(char** stringp, const char* delim) {
    char *begin, *end;
    begin = *stringp;
    if (begin == NULL)
        return NULL;
    /* Find the end of the token.  */
    end = begin + strcspn(begin, delim);
    if (*end) {
        /* Terminate the token and set *STRINGP past NUL character.  */
        *end++ = '\0';
        *stringp = end;
    } else
        /* No more delimiters; this is the last token.  */
        *stringp = NULL;
    return begin;
}

char* clonestr(char* s);
struct nlist* lookup(dict* h, char* s, int i);
struct nlist* set(dict* h, char* name, int i);
dict* new_dict(void);

dict* new_dict(void) {
    dict* h = NULL;
    h = (dict*)malloc(sizeof(dict));
    for (int i = 0; i < HASHSIZE; ++i) {
        *h[i] = NULL;
    }
    return h;
}

unsigned hash(char* s, int i) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return (hashval + i) % HASHSIZE;
}

struct nlist* set(dict* h, char* name, int i) {
    struct nlist* np;
    unsigned hashval;

    if ((np = lookup(h, name, i)) == NULL) {
        np = (struct nlist*)malloc(sizeof(struct nlist));
        // Check for malloc errors
        if (np == NULL || (np->name = clonestr(name)) == NULL)
            return NULL;
        hashval = hash(name, i);
        np->next = *h[hashval];
        np->v = i;
        *h[hashval] = np;
    }

    return np;
}

struct nlist* lookup(dict* h, char* s, int i) {
    struct nlist* np;
    for (np = *h[hash(s, i)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0 && i == np->v)
            return np;
    }
    return NULL;
}

char* clonestr(char* s) {
    char* p;
    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

char* run(char* s) {
    char* token = (char*)malloc(MAXSIZE);
    char* buffer = (char*)malloc(MAXSIZE);
    int len = 0;

    dict* d = new_dict();

    while ((token = strsep(&s, "\n")) != NULL) {
        len = len ? len : strlen(token);

        for (int i = 0; i < len; ++i) {
            // Slice at ith index
            strncpy(buffer, token, i);
            strncpy(buffer + i, token + i + 1, len - i);
            if (lookup(d, buffer, i) != NULL)
                return buffer;
            else
                set(d, buffer, i);
        }
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing one argument\n");
        exit(1);
    }
    clock_t start = clock();
    char* answer = run(argv[1]);

    printf("_duration:%f\n%s\n",
        (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
    return 0;
}
