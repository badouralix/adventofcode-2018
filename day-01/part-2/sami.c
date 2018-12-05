#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// The poor's hashmap
struct node {
  int value;
  struct node *left;
  struct node *right;
};

struct node *new_node(void) {
  return (struct node *)malloc(sizeof(struct node));
}

// prints the result and exit if the element is already in the tree, otherwise returns the tree
struct node *push(struct node *t, int el) {
  if (t == NULL) {
    t = new_node();
    t->value = el;
    t->left = t->right = NULL;
  } 
  else if (el < t->value) {
    t->left = push(t->left, el);
  } 
  else if (el > t->value) {
    t->right = push(t->right, el);
  } 
  else {
    printf("%d\n", el);
    exit(0);
  }

  return t;
}

void run(char *s) {
  int res = 0;
  int buffer = 0;
  char op = '\0';

  struct node *tree = NULL;

  for (;;) {
    for (int i = 0; s[i] != EOF && s[i] != '\0'; ++i) {
      if (s[i] == '+' || s[i] == '-') {
        op = s[i];
      } 
      else if (isdigit(s[i])) {
        buffer = buffer * 10 + s[i] - '0';
      } 
      else if (s[i] == '\n') {
        res = op == '+' ? res + buffer : res - buffer;

        tree = push(tree, res);
        buffer = 0;
      }
    }
    res = op == '+' ? res + buffer : res - buffer;
    buffer = 0;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Missing one argument\n");
    exit(1);
  }

  run(argv[1]);
  return 0;
}
