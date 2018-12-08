#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Coord {
    int x, y;
};

int abs(int x) {
    return x >= 0 ? x : -x;
}

int d(Coord A, Coord B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

vector<Coord> parse_input(const string& in) {
    istringstream iss(in);
    vector<Coord> vec;

    for (string line; getline(iss, line); ) {
        Coord c;
        sscanf(line.c_str(), "%d , %d", &c.x, &c.y);
        vec.push_back(c);
    }

    return vec;
}

int run(const string& in) {
    const int MAX_X = 400;
    const int MAX_Y = 400;

    auto coords = parse_input(in);
    int regionSize = 0;
    for (int x = 0; x <= MAX_X; x++) {
        for (int y = 0; y <= MAX_Y; y++) {
            Coord M = {x, y};
            vector<int> distances;
            transform(coords.begin(), coords.end(), back_inserter(distances),
                           [=](auto P) { return d(M, P); });
            int totalDistance = accumulate(distances.begin(), distances.end(), 0);

            if (totalDistance < 10000)
                regionSize++;
        }
    }

    return regionSize;
}

int main(int argc, char **argv) {
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
