#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int LINESIZE = 48;
const int FIRST = 5;
const int SECOND = 36;

#define ALPHABET 26
const char OFFSET = 'A';

const int DONE = -1;

// Will hold the number of dependencies left for the given step to be run
static int counts[ALPHABET];

// Will hold STEP -> Steps to do before
static int dependencies[ALPHABET][ALPHABET];

static int seen[ALPHABET];

char *parseline(char *s, char *l1, char *l2) {
  *l1 = *(s + FIRST);
  *l2 = *(s + SECOND);
  return s + LINESIZE;
}

char *run(char *s) {
  int i, j, nb;
  nb = i = j = 0;

  // Init array
  for (i = 0; j < ALPHABET; i++) 
   for (j = 0;  j < ALPHABET; j++)
    dependencies[i][j] = DONE;
     
  char first, second;
  for (;;s++) {
    s = parseline(s, &first, &second);
    nb += seen[first - OFFSET] == 0 ? 1 : 0;
    nb += seen[second - OFFSET] == 0 ? 1 : 0;
    seen[first - OFFSET] = 1;
    seen[second - OFFSET] = 1;
    counts[second - OFFSET]++;
    dependencies[first - OFFSET][second - OFFSET] = 1;

    if (*s == '\0')
      break;
  }

  char *order = (char *) malloc(nb);
  int pos = 0;

  for (i = 0; i < nb && pos != nb;) {
    // We can do i
    if (counts[i] == 0) {
      counts[i] = DONE; 
      for (j = 0; j < nb; j++) {
       if (dependencies[i][j] > 0) {
          dependencies[i][j] = DONE;
          counts[j]--;
       }
      }
      order[pos++] = i + OFFSET;
      i = 0;
    }
    else {
      i++; 
    }
  }
  order[pos] = '\0';
  
  return order;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Missing one argument\n");
    exit(1);
  }

  clock_t start = clock();
  char *answer = run(argv[1]);

  printf("_duration:%f\n%s\n",
         (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC, answer);
  return 0;
}
