#include <stdio.h>
#include <string.h>

unsigned int n_dbl = 0;
unsigned int n_tpl = 0;
unsigned int c_dbl = 0;
unsigned int c_tpl = 0;
char p = 0;

static unsigned int ctr[26] =
  { 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0
  };

int main(int argc, char** argv) {
	if (argc != 2) return 1;
	
	char* input = argv[1];
	while (*input != 0) {
		if (*input == '\n') {
			if (c_dbl > 0) {++n_dbl; c_dbl = 0;}
			if (c_tpl > 0) {++n_tpl; c_tpl = 0;}
			memset(ctr, 0x0, 26 * sizeof( unsigned int ));
		}
		else {
			switch (++ctr[*input - 'a']) {
				case 2: ++c_dbl; break;
				case 3: ++c_tpl; --c_dbl; break;
				case 4: --c_tpl; break;
			}
		}
		p = *input;
		++input;
	}
	if (c_dbl > 0) ++n_dbl; 
	if (c_tpl > 0) ++n_tpl;

	printf("%d\n", n_dbl * n_tpl);
	return 0;
}
