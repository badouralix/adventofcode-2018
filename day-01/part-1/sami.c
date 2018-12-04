#include <stdio.h>
#include <stdlib.h>

int run(char *s) {
  int res = 0;
  int buffer = 0;
  char op = '\0';

  for (int i = 0; s[i] != EOF && s[i] != '\0'; ++i) {
    if (s[i] == '+' || s[i] == '-') {
      op = s[i];
    } else if (s[i] >= '0' && s[i] <= '9') {
      buffer = buffer * 10 + s[i] - '0';
    } else {
      if (op == '+') {
        res += buffer;
      } else {
        res -= buffer;
      }
      buffer = 0;
    }
  }

  return res;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Missing one argument\n");
    exit(1);
  }
  printf("%d\n", run(argv[1]));
  return 0;
}
