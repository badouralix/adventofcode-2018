#include <cstdio>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Coord {
    int x, y;
};

int abs(int x) {
    return x >= 0 ? x : -x;
}

int d(Coord A, Coord B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

std::vector<Coord> parse_input(const std::string in) {
    std::istringstream iss(in);
    std::vector<Coord> vec;

    for (std::string line; std::getline(iss, line); ) {
        Coord c;
        sscanf(line.c_str(), "%d , %d", &c.x, &c.y);
        vec.push_back(c);
    }

    return vec;
}

int solve(std::vector<Coord>& input) {
    const int MAX_X = 400;
    const int MAX_Y = 400;

    std::vector<int> regionPopulation(input.size());
    std::set<int> excluded;

    for (int x = 0; x <= MAX_X; x++) {
        for (int y = 0; y <= MAX_Y; y++) {
            Coord M = {x, y};

            int minDist = 10000, closest = -1;
            for (size_t k = 0; k < input.size(); k++) {
                int dist = d(M, input[k]);
                if (dist < minDist) {
                    closest = k;
                    minDist = dist;
                }
                else if (dist == minDist)
                    closest = -1;       // In case of ties mark region as 'unowned'
            }

            if (closest >= 0)
                regionPopulation[closest]++;

            // Mark all regions that touch edges as infinite
            if (x == 0 || x == MAX_X || y == 0 || y == MAX_Y)
                excluded.insert(closest);
        }
    }

    // Find most populated region that doesn't touch edges of box
    int largestRegionSize = 0;
    for (size_t region = 0; region < regionPopulation.size(); region++) {
        if (excluded.find(region) == excluded.end() && regionPopulation[region] > largestRegionSize) {
            largestRegionSize = regionPopulation[region];
        }
    }

    return largestRegionSize;
}

int main(int argc, char *argv[]) {
    auto input = parse_input(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
