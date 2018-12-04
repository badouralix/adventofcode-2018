#include <stdio.h>

unsigned int n_dbl = 0;
unsigned int n_tpl = 0;
unsigned int c_dbl = 0;
unsigned int c_tpl = 0;
unsigned int ctr = 0;
char p = 0;

int main(int argc, char** argv) {
	if (argc != 2) return 1;
	
	char* input = argv[1];
	while (*input != 0) {
		if (*input == '\n') {
			if (c_dbl > 0 || ctr == 1) {++n_dbl; c_dbl = 0;}
			if (c_tpl > 0 || ctr == 2) {++n_tpl; c_tpl = 0;}
			p   = 0;
			ctr = 0;
		}
		if (*input == p) {
			switch (++ctr) {
				case 1 : ++c_dbl; break;
				case 2 : --c_dbl; ++c_tpl; break;
				case 3 : --c_tpl; break;
				default: break;
			}
		}
		else { ctr = 0; }
		p = *input;
		++input;
	}
	if (c_dbl > 0 || ctr == 1) ++n_dbl; 
	if (c_tpl > 0 || ctr == 2) ++n_tpl;

	printf("%d\n", n_dbl * n_tpl);
	return 0;
}
