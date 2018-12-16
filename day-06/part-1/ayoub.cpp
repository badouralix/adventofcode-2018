#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <ctime>

using namespace std;

typedef struct Point {
    int x, y;
} Point;

int dist(int x0, int y0, int x1, int y1) {
    return abs(x1-x0) + abs(y1-y0);
}

int closest(int x, int y, const vector<Point> & points) {
    int min_i = -1, min_d = INT_MAX, d;
    for (int i = 0; i < points.size(); i++) {
        d = dist(x, y, points[i].x, points[i].y);
        if (d < min_d) {
            min_d = d;
            min_i = i;
        } else if (d == min_d) {
            min_i = -1;
        }
    }
    return min_i;
}

int run(string s) {
    int n = 0, N, M;
    vector<Point> points;
    Point topleft={INT_MAX, INT_MAX}, botright={0, 0};
    string line;
    istringstream stream(s);
    
    while(getline(stream, line)) {
        Point p;
        sscanf(line.c_str(), "%d, %d", &p.x, &p.y);
        points.push_back(p);
        topleft.x = (p.x < topleft.x)?p.x:topleft.x;
        topleft.y = (p.y < topleft.y)?p.y:topleft.y;
        botright.x = (p.x > botright.x)?p.x:botright.x;
        botright.y = (p.y > botright.y)?p.y:botright.y;
        n++;
    }

    for (int i = 0; i < n; i++) {
        points[i].x -= topleft.x;
        points[i].y -= topleft.y;
    }
    N = botright.x-topleft.x+1;
    M = botright.y-topleft.y+1;

    int count[n], i;
    bool infinite[n];
    for (int i = 0; i < n; i++) {
        count[i] = 0; infinite[i] = false;
    }

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            i = closest(x, y, points);
            if (x == 0 || x == N-1 ||
                y == 0 || y == M-1) infinite[i] = true;
            if (i == -1) continue;
            count[i]++;
        }
    }

    int max = 0;
    for (i = 0; i < n; i++) {
        if (!infinite[i]) max = (count[i] > max)?count[i]:max;
    }

    return max;
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
