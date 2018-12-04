#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

struct Rectangle {
    int id;
    int x, y;
    int w, h;
};

const int GRID_SIZE = 1000;

std::vector<Rectangle> parse_input(const std::string& in) {
    std::istringstream iss(in);
    std::vector<Rectangle> vec;

    for (std::string line; std::getline(iss, line); ) {
        Rectangle rect;
        sscanf(line.c_str(), "#%d @ %d , %d : %d x %d", &rect.id, &rect.x, &rect.y, &rect.w, &rect.h);
        vec.push_back(rect);
    }

    return vec;
}

int part_2(const std::vector<Rectangle>& claims) {
    int grid[GRID_SIZE][GRID_SIZE] = {{0}};
    
    for (auto& c : claims) {
        for (int x = c.x; x < c.x + c.w; x++) {
            for (int y = c.y; y < c.y + c.h; y++) {
                grid[x][y] += 1;
            }
        }
    }

    // Find non-conflicting claim
    for (auto& c : claims) {
        bool isValidClaim = true;
        for (int x = c.x; isValidClaim && x < c.x + c.w; x++) {
            for (int y = c.y; isValidClaim && y < c.y + c.h; y++) {
                if (grid[x][y] > 1)
                    isValidClaim = false;
            }
        }

        if (isValidClaim)
            return c.id;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    auto input = parse_input(argv[1]);
    
    printf("%d\n", part_2(input));

    return 0;
}
