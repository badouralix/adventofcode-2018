#include <stdio.h>
#include <time.h>
#include <string.h>

unsigned int scores[1024];
unsigned int status[65536];
unsigned int veclen = 1;
unsigned int players = 0;
unsigned int player = 0;
unsigned int last = 0;
unsigned int maxscore = 0;
unsigned int circled = 0;

void print_status() {
	for (unsigned int i = 0; i < veclen; ++i) {
		if (circled == i) {
			printf("(%d) ", status[i]);
		}
		else {
			printf("%d ", status[i]);
		}
	}
	printf("\n");
}

void insert_after(unsigned int m, unsigned int p) {
  ++veclen; ++p;
  for (unsigned int i = veclen-1; i >=p ; --i) status[i] = status[i-1];
  status[p] = m;
  circled = p;
}

void remove_at(unsigned int p) {
  for(unsigned int i=p; i<veclen-1;++i) status[i] = status[i+1];
  --veclen;  
}

int main(int argc, char** argv) {

  if (argc < 2) return 1;
  char* input = argv[1];

  clock_t start = clock();

  sscanf(input, "%d players; last marble is worth %d points\n", &players, &last);

  status[0] = 0;
  memset(scores, 0, sizeof(unsigned int) * players);

  print_status();

  for(unsigned int round = 1; round <= last; ++round) {
    player = (player == players)?1:player + 1;
    if (round % 23 == 0) {
      scores[player] += round;
      circled = (circled + veclen - 7)%veclen;
      scores[player] += status[circled];
      remove_at(circled);

      maxscore = scores[player] > maxscore?scores[player]:maxscore;

    }
    else insert_after(round, (circled+1)%veclen );
  }

  printf("_duration:%f\n", (float)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  printf("%d\n",maxscore);

  return 0;
}
