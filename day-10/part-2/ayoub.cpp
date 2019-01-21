#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
#include <ctime>

#define ALPHABET_SIZE 26
#define FLAG_SIZE 8
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 10
#define CHAR_SPACE 2
#define FLAG_WIDTH 62

using namespace std;

bool is_space(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n';}
int min(int a, int b) { return (a<b)?a:b; }
int max(int a, int b) { return (a>b)?a:b; }

typedef struct Point {
    int x, y, vx, vy;
} Point;

void advance(vector<Point> &points) {
    for (int i = 0; i < points.size(); i++) {
        points[i].x += points[i].vx;
        points[i].y += points[i].vy;
    }
}

bool within_rect(const vector<Point> &points, int width, int height) {
    int min_x = INT_MAX, min_y = INT_MAX,
        max_x = INT_MIN, max_y = INT_MIN;
    for (int i = 0; i < points.size(); i++) {
        min_x = min(min_x, points[i].x);
        min_y = min(min_y, points[i].y);
        max_x = max(max_x, points[i].x);
        max_y = max(max_y, points[i].y);
    }
    return (max_x-min_x < width) && (max_y-min_y < height);
}

int run(string s) {
    istringstream input(s);
    string line;
    vector<Point> points;

    while (getline(input, line)) {
        Point p;
        remove_if(line.begin(), line.end(), is_space);
        sscanf(line.c_str(), "position=<%d,%d>velocity=<%d,%d>", &p.x, &p.y, &p.vx, &p.vy);
        points.push_back(p);
    }

    int seconds = 0;
    while (!within_rect(points, FLAG_WIDTH, CHAR_HEIGHT)) {
        advance(points);
        seconds++;
    }    

    return seconds;
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
