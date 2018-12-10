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

int max_dist_x(const vector<Point> &points) {
    int max_dist = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            max_dist = max(max_dist, abs(points[i].x - points[j].x));
        }
    }
    return max_dist;
}

int max_dist_y(const vector<Point> &points) {
    int max_dist = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            max_dist = max(max_dist, abs(points[i].y - points[j].y));
        }
    }
    return max_dist;
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
    while (max_dist_x(points) > FLAG_WIDTH || 
           max_dist_y(points) > CHAR_HEIGHT) {
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
