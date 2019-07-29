#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const int N_SIMULATIONS = 10;
const int GRID_SIZE = 50;

using Grid = array<array<char, GRID_SIZE>, GRID_SIZE>;

void parse(const string& in, Grid& grid) {
    istringstream iss(in);
    int y = 0;
    for (string line; getline(iss, line); y++) {
        for (int x = 0; x < line.length(); x++) {
            grid[y][x] = line[x];
        }
    }
}

void print(const Grid& grid) {
    for (const auto& row : grid) {
        for (const auto c : row)
            putchar(c);
        putchar('\n');
    }
}

int count_neighbors(const Grid& grid, int x, int y, char type) {
    int xmin = max(0, x-1), xmax = min(x+1, GRID_SIZE-1);
    int ymin = max(0, y-1), ymax = min(y+1, GRID_SIZE-1);
    int count = 0;
    for (int j = ymin; j <= ymax; j++)
        for (int i = xmin; i <= xmax; i++)
            if (grid[j][i] == type && !(i == x && j == y))
                count++;
    return count;
}

Grid update(const Grid& state) {
    Grid nextState;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int trees = count_neighbors(state, x, y, '|');
            int lumber = count_neighbors(state, x, y, '#');
            nextState[y][x] = state[y][x];
            switch (state[y][x]) {
                case '|':
                    if (lumber >= 3)
                        nextState[y][x] = '#';
                    break;
                case '.':
                    if (trees >= 3)
                        nextState[y][x] = '|';
                    break;
                case '#':
                    if (trees == 0 || lumber == 0)
                        nextState[y][x] = '.';
            }
        }
    }
    return nextState;
}

int resource_value(const Grid& grid) {
    int wooded = 0, lumber = 0;
    for (const auto& row : grid) {
        for (const auto c : row) {
            if (c == '|')   wooded++;
            if (c == '#')   lumber++;
        }
    }
    return wooded * lumber;
}

int run(const string& s) {
    Grid state;
    parse(s, state);

    for (int n = 0; n < N_SIMULATIONS; n++) {
        state = update(state);
    }

    return resource_value(state);
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
