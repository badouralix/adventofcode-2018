#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

unsigned int scores[1024];
unsigned int players = 0;
unsigned int player = 0;
unsigned int last = 0;
unsigned int maxscore = 0;

typedef struct vec {
	unsigned int val;
	struct vec* next;
	struct vec* prev;
} vec;

vec* root;
vec* circled;

void insert_after(unsigned int m, vec* position) {
  vec* new_node = (vec*)malloc(sizeof(vec));
  vec* right = position->next;
  new_node->val = m; new_node->prev=position;new_node->next=right;
  position->next = new_node;
  right->prev=new_node;
  circled = new_node;
}

void remove_at(vec* position) {
  vec* left = position->prev;
  vec* right = position->next;
  left->next = right;
  right->prev = left;
}

int main(int argc, char** argv) {

  if (argc < 2) return 1;
  char* input = argv[1];

  sscanf(input, "%d players; last marble is worth %d points\n", &players, &last);

  clock_t start = clock();
  last *= 100;

  root = (vec*)malloc(sizeof(vec));
  root->val = 0;  root->prev = root;  root->next = root;
  circled = root;

  memset(scores, 0, sizeof(unsigned int) * players);

  for(unsigned int round = 1; round <= last; ++round) {
    player = (player == players)?1:player + 1;
    if (round % 23 == 0) {
      scores[player] += round;
      vec* to_remove = circled->prev->prev->prev->prev->prev->prev->prev;
      circled = to_remove->next;
      scores[player] += to_remove->val;
      remove_at(to_remove);

      maxscore = scores[player] > maxscore?scores[player]:maxscore;

    }
    else insert_after(round, circled->next );
  }

  printf("_duration:%f\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  printf("%d\n",maxscore);

  return 0;
}
