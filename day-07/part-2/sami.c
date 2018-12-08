#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int LINESIZE = 48;
const int FIRST = 5;
const int SECOND = 36;
const char OFFSET = 'A';
const int TIME = 61;

const int DONE = -1;
const int PROGRESS = -2;

const int IDLE = -1;
const int WORKING = 1;

#define ALPHABET 26
#define WORKERS 5

// Will hold the number of dependencies left for the given step to be run
static int counts[ALPHABET];

// Will hold STEP -> Steps to do before
static int dependencies[ALPHABET][ALPHABET];

static int seen[ALPHABET];

// Will hold which task each worker is doing
static int workers[WORKERS];

// Will hold time left for each task
static int timeleft[WORKERS];

char *parseline(char *s, char *l1, char *l2) {
  *l1 = *(s + FIRST);
  *l2 = *(s + SECOND);
  return s + LINESIZE;
}

int run(char *s) {
  int i, j, k, nb;
  nb = i = j = k = 0;

  // Init arrays
  for (i = 0; j < ALPHABET; i++)
    for (j = 0; j < ALPHABET; j++)
      dependencies[i][j] = DONE;

  for (i = 0; i < WORKERS; ++i)
    workers[i] = IDLE;

  char first, second;
  for (;; s++) {
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

  int pos = 0;
  int smallest, w;
  int timestamp = 0;

  while (pos != nb) {
    for (i = 0; i < nb && pos != nb;) {
      // i should be done
      if (counts[i] == 0) {
        // Find a worker for this task
        for (k = 0; k < WORKERS; k++) {
          if (workers[k] == IDLE) {
            counts[i] = PROGRESS;
            workers[k] = i;
            timeleft[k] = TIME + i;
            break;
          }
          // No workers were found just skip this task for the moment
        }
      }
      i++;
    }
    w = -1;
    smallest = TIME + ALPHABET + 1;
    // Advance time by taking the smallest working time
    for (k = 0; k < WORKERS; k++) {
      if (workers[k] != IDLE && timeleft[k] < smallest) {
        smallest = timeleft[k];
        w = k;
      }
    }

    for (j = 0; j < nb; j++) {
      if (dependencies[workers[w]][j] > 0) {
        dependencies[workers[k]][j] = DONE;
        counts[j]--;
      }
    }

    for (k = 0; k < WORKERS; k++) {
      timeleft[k] -= smallest;
      if (k == w) {
        timestamp += smallest;
        pos++;
        i = 0;
        workers[k] = IDLE;
      }
    }
  }

  return timestamp;
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
