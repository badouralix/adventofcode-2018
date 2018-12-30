#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <climits>

#define GEN 20
#define MAPPING_SIZE 32
#define MAX_SIZE 400
#define INPUT_SIZE 100

using namespace std;

bool mapping[MAPPING_SIZE];

bool get_state(bool pp, bool p, bool c, bool n, bool nn) {
    int a = 0;
    if (pp) a += 1;
    if (p)  a += 2;
    if (c)  a += 4;
    if (n)  a += 8;
    if (nn) a += 16;
    return mapping[a];
}

int seqtoi(const char *seq) {
    int a = 0, p = 1;
    for (int i = 0; i < 5; i++) {
        a += ((seq[i] == '#')?1:0)*p;
        p *= 2;
    }
    return a;
}

void evolve(bool *pots, bool *output) {
    for (int i = 2; i < MAX_SIZE-2; i++) {
        output[i] = get_state(pots[i-2], pots[i-1], pots[i], pots[i+1], pots[i+2]);
    }
    output[0] = get_state(false, false, pots[0], pots[1], pots[2]);
    output[1] = get_state(false, pots[0], pots[1], pots[2], pots[3]);

    output[MAX_SIZE-2] = get_state(pots[MAX_SIZE-4], pots[MAX_SIZE-3], pots[MAX_SIZE-2], pots[MAX_SIZE-1], false);
    output[MAX_SIZE-1] = get_state(pots[MAX_SIZE-3], pots[MAX_SIZE-2], pots[MAX_SIZE-1], false, false);
}

void copy(bool *dst, bool *src) {
    for (int i = 0; i < MAX_SIZE; i++) {
        dst[i] = src[i];
    }
}

int run(string s) {
    istringstream stream(s);
    string line;
    bool initialized = false;
    bool pots[MAX_SIZE] = {false}, future[MAX_SIZE] = {false};
    int id = MAX_SIZE / 2 - INPUT_SIZE / 2;
    int offset = id;

    while (getline(stream, line)) {
        if (!initialized) {
            for (int i = 15; i < line.size(); i++) {
                pots[id++] = line.at(i) == '#';
            }
            initialized = true;
            getline(stream, line);
            continue;
        }
        mapping[seqtoi(line.c_str())] = line.at(9) == '#';
    }

    for (int g = 0; g < GEN; g++) {
        evolve(pots, future);
        copy(pots, future);
    }

    int total = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        total += (pots[i])?(i-offset):0;
    }

    return total;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
