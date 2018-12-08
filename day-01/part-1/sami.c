#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ZERO = (int)'0';

int run(char *s) {
  int res = 0;
  int buffer = 0;
  char op = '\0';

  for (int i = *s; i != EOF && i != '\0'; i = *(s++)) {
    switch (i) {
    case '+':
    case '-':
      op = i;
      break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      buffer = buffer * 10 + i - ZERO;
      break;

    default:
      res = op == '+' ? res + buffer : res - buffer;
      buffer = 0;
    }
  }

  res = op == '+' ? res + buffer : res - buffer;

  return res;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Missing one argument\n");
    exit(1);
  }
    clock_t start = clock();
    int answer = run(argv[1]);
    
    printf("_duration:%f\n%d\n", (float)( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC, answer);
  return 0;
}
