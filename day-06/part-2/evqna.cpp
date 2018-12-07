#include <algorithm>
#include <cstdio>
#include <iterator>
#include <numeric>
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

int solve(std::vector<Coord>& coords) {
    const int MAX_X = 400;
    const int MAX_Y = 400;

    int regionSize = 0;
    for (int x = 0; x <= MAX_X; x++) {
        for (int y = 0; y <= MAX_Y; y++) {
            Coord M = {x, y};
            std::vector<int> distances;
            std::transform(coords.begin(), coords.end(), std::back_inserter(distances),
                           [=](auto P) { return d(M, P); });
            int totalDistance = std::accumulate(distances.begin(), distances.end(), 0);

            if (totalDistance < 10000)
                regionSize++;
        }
    }

    return regionSize;
}

int main(int argc, char **argv) {
    auto input = parse_input(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
