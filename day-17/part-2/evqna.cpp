#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int HEIGHT = 2500;
const int WIDTH = 1000;

const int SPRING_X = 500;
const int SPRING_Y = 0;

enum class GridEntry {
    SAND, CLAY, FLOWING, STILL, SPRING
};

char toString(const GridEntry entry) {
    switch (entry) {
        case GridEntry::SAND:       return '.';
        case GridEntry::CLAY:       return '#';
        case GridEntry::FLOWING:    return '|';
        case GridEntry::STILL:      return '~';
        case GridEntry::SPRING:     return '+';
        default:                    return '?';
    }
}

using Grid = vector<vector<GridEntry>>;
Grid grid(HEIGHT, vector<GridEntry>(WIDTH, GridEntry::SAND));
int waterCount = 0;
int stillCount = 0;

struct GroundSlice {
    int minX = INT32_MAX, maxX = INT32_MIN;
    int minY = INT32_MAX, maxY = INT32_MIN;

    GridEntry get(int x, int y) const {
        return grid[y][x];
    }

    void set(int x, int y, GridEntry c) { 
        grid[y][x] = c;
    }

    void set_resize(int x, int y, GridEntry c) {
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
        set(x, y, c);
    }

    void print() const {
        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++)
                putchar(toString(get(x, y)));
            putchar('\n');
        }
    }
};

struct GroundSlice parseInput(const string& in) {
    istringstream istream(in);
    struct GroundSlice slice;
    slice.set(SPRING_X, SPRING_Y, GridEntry::SPRING);

    for (string line; getline(istream, line); ) {
        char axis1, axis2;
        unsigned int coord1, coord2_min, coord2_max;
        sscanf(line.c_str(), "%c=%u, %c=%u..%u",
            &axis1, &coord1, &axis2, &coord2_min, &coord2_max);
        
        if (axis1 == 'x') {
            for (int y = coord2_min; y <= coord2_max; y++)
                slice.set_resize(coord1, y, GridEntry::CLAY);
        } else {
            for (int x = coord2_min; x <= coord2_max; x++)
                slice.set_resize(x, coord1, GridEntry::CLAY);
        }
    }

    // printf("Bounding box: (%d,%d) x (%d,%d)", slice.minX, slice.maxX, slice.minY, slice.maxY);

    return slice;
}

bool recursive_flow(GroundSlice& s, int x, int y);

bool flow_sideways(GroundSlice& s, int x, int y, int x_inc) {
    switch (s.get(x, y)) {
        case GridEntry::CLAY:
            return false;
        case GridEntry::FLOWING:
            return true;
        case GridEntry::SAND:
        default:
            waterCount++;
            s.set(x, y, GridEntry::FLOWING);
            return recursive_flow(s, x, y+1) || flow_sideways(s, x + x_inc, y, x_inc);
    }
}

// Returns true if the flow reached below the bounded region,
// false if it was blocked
bool recursive_flow(GroundSlice& s, int x, int y) {
    // Stop simulation if stream reaches out
    if (y > s.maxY)
        return true;

    switch (s.get(x, y)) {
        case GridEntry::FLOWING:
            // Merging with an already computed stream, NO-OP
            return true;
        case GridEntry::CLAY:
        case GridEntry::STILL:
            return false;
        case GridEntry::SAND:
        default:
            waterCount++;
            s.set(x, y, GridEntry::FLOWING);
            // Try flowing down
            if (recursive_flow(s, x, y+1))
                return true;
            else {
                // Stream was blocked, try flowing sideways
                bool left_flow = flow_sideways(s, x-1, y, -1);
                bool right_flow = flow_sideways(s, x+1, y, +1);
                bool can_flow = left_flow || right_flow;

                if (!can_flow) {
                    // Mark all water on this level as still
                    for (; s.get(x-1, y) == GridEntry::FLOWING; x--);
                    while (s.get(x, y) == GridEntry::FLOWING) {
                        s.set(x, y, GridEntry::STILL);
                        stillCount++;
                        x++;
                    }
                }

                return can_flow;
            }
    }
}

int run(const string in) {
    auto slice = parseInput(in);

    int x = SPRING_X, y = max(SPRING_Y, slice.minY);

    recursive_flow(slice, x, y);

    return stillCount;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(argv[1]);
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
