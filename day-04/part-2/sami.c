#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXGUARDS 5000
#define MAXLINES 2000

enum {
  UNDEFINED = -2,
  ASLEEP = -1,
  WAKEUP = 0,
};

// Will hold the number of time guard $i slept during minute $m
static int guards[MAXGUARDS][60];

typedef struct {
  short int month;
  short int day;
  short int minute;
  short int id;
  short int guard; // -1 if falls asleep, 0 if wake up otherwise guard id
} entry_t;

// parse a number and stops at the first non digit char
char *parse_number(char *s, short int *x) {
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

char *parseandnext(char *s, short int *x) {
  return next_number(parse_number(s, x));
}

char *readentry(char *s, entry_t *e) {
  short int hour;

  s = parseandnext(s + 1, &e->day); // we don't care abouth year
  s = parseandnext(s, &e->month);
  s = parseandnext(s, &e->day);
  s = parseandnext(s, &hour);
  s = parse_number(s, &e->minute);
  if (hour == 23){
    e->minute = 0;
    e->day++; 
  }

  // We are at the ], so we need to read two chars
  switch (*(s + 2)) {
  case 'G':
    s = parse_number(next_number(s), &e->guard);
    break;
  case 'f': // Falls asleep
    e->guard = ASLEEP;
    break;
  case 'w': // wakes up
    e->guard = WAKEUP;
    break;
  default:
    // This should not happen
    printf("Unknown line: %c: %s\n", *s, s);
    exit(1);
  }
  // Then we should just walk until end of line
  for (; *s != '\n' && *s != '\0'; s++)
    ;

  return s;
}

entry_t *newentry() {
  entry_t *e = (entry_t *)malloc(sizeof(entry_t *));
  return e;
}

// compare entries
int comp_entries(const void *e1, const void *e2) {
  entry_t *x = *(entry_t **)e1;
  entry_t *y = *(entry_t **)e2;

  if (y->guard == UNDEFINED)
    return -1;
  if (x->guard == UNDEFINED)
    return 1;

  if (x->month < y->month)
    return -1;
  else if (x->month > y->month)
    return 1;

  if (x->day < y->day)
    return -1;
  else if (x->day > y->day)
    return 1;

  if (x->minute < y->minute)
    return -1;
  else if (x->minute > y->minute)
    return 1;

  return 0;
}

int run(char *s) {
  entry_t *es[MAXLINES];
  int i;

  for (i = 0; i < MAXLINES; ++i) {
    es[i] = newentry();
    es[i]->guard = UNDEFINED;
  }

  // Parse the entries
  for (i = 0;; s++, i++) {
    s = readentry(s, es[i]);
    if (*s == '\0')
      break;
  }

  // Sort the entries
  qsort(es, MAXLINES, sizeof(entry_t *), comp_entries);

  int curr = es[0]->guard; // Current guard
  int maxg, maxm, mcount; // Max guard and max minute
  maxm = maxg = mcount = 0;
  short int m;

  // Restart at the beginning of the array
  for (i = 0; i < MAXLINES; i++) {
    switch (es[i]->guard) {
    case UNDEFINED:
      return maxg * maxm;
    case ASLEEP:
      break;
    case WAKEUP:
      // Increase all the minute for this guard
      for (m = es[i-1]->minute; m < es[i]->minute; m++){
        guards[curr][m]++;
        if (guards[curr][m] > mcount) {
          maxg = curr;
          maxm = m;
          mcount = guards[curr][m];
        }
      }
      break;
    default:
      // Guard changed
      curr = es[i]->guard;
    }
  }
  printf("end\n");
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Missing one argument\n");
    exit(1);
  }
  printf("%d\n", run(argv[1]));
  return 0;
}
