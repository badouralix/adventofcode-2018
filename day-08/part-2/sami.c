#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// parse a number and stops at the first non digit char
char *parse_number(char *s, int *x) {
  *x = 0;
  for (; isdigit(*s); s++)
    *x = 10 * (*x) + *s - '0';

  return s;
}

// jumps to next_number
char *next_number(char *s) {
  for (; !isdigit(*s); s++)
    ;
  return s;
}

char *next(char *s, int *x) { return next_number(parse_number(s, x)); }

// Calls count for each child
char *count(int childs, int metadatas, int *c, char *s) {
  int ch, me, tmp, i;

  if (childs != 0) {
    int refs[childs];
    for (i = 0; i < childs; ++i) 
      refs[i] = 0; 

    for (i = 0; i < childs; i++) {
      s = next(s, &ch);
      s = next(s, &me);
      s = count(ch, me, &refs[i], s);
    }

  for (i = 0; i < metadatas; ++i) {
    s = next(s, &tmp);
    *c += tmp - 1 < childs ? refs[tmp - 1] : 0;
  }
  return s;
  }

  for (i = 0; i < metadatas; ++i) {
    s = next(s, &tmp);
    *c += tmp;
  }
  return s;
}

int run(char *s) {
  int childs, meta, counter;
  childs = meta = counter = 0;
  s = next(s, &childs);
  s = next(s, &meta);
  s = count(childs, meta, &counter, s);

  return counter;
}

int main(int argc, char **argv) {
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
