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

bool alphabet[ALPHABET_SIZE][CHAR_HEIGHT][CHAR_WIDTH];
const string alphabet_file_path = "./day-10/alphabet.txt";

void build_alphabet() {
    int c = 0, y = 0, x = 0;
    
    for (c = 0; c < ALPHABET_SIZE; c++)
    for (y = 0; y < CHAR_HEIGHT; y++)
    for (x = 0; x < CHAR_WIDTH; x++) alphabet[c][y][x] = false;

    ifstream stream;
    string line;

    c = -1; y = 0;

    stream.open(alphabet_file_path);
    while (getline(stream, line)) {
        if (y == CHAR_HEIGHT) {
            c = -1; y = 0;
            continue;
        }
        if (c == -1) {
            c = line.at(0)-'A';
            continue;
        }
        
        for (x = 0; x < line.size() && x < CHAR_WIDTH; x++)
            alphabet[c][y][x] = line.at(x) == '#';
        y++;
    }
    stream.close();
}

char read_char(bool g[CHAR_HEIGHT][FLAG_WIDTH], int x_offset) {
    int c = 0;
    bool found = false;
    while (!found && c < ALPHABET_SIZE) {
        found = true;
        for (int x = 0; x < CHAR_WIDTH; x++) {
            for (int y = 0; y < CHAR_HEIGHT; y++) {
                if (g[y][x+x_offset] != alphabet[c][y][x]) {
                    found = false;
                    break;
                }
            }
            if (!found) break;
        }
        if (found) return (char)(c+'A');
        c++;
    }
    return '?';
}

string read_flag(const vector<Point> &points) {
    int min_x = INT_MAX, min_y = INT_MAX;
    for (int i = 0; i < points.size(); i++) {
        min_x = min(min_x, points[i].x);
        min_y = min(min_y, points[i].y);
    }
    
    bool g[CHAR_HEIGHT][FLAG_WIDTH];
    for (int y = 0; y < CHAR_HEIGHT; y++)
    for (int x = 0; x < FLAG_WIDTH; x++)
        g[y][x] = false;

    for (int i = 0; i < points.size(); i++) {
        g[points[i].y-min_y][points[i].x-min_x] = true;
    }

    char flag[FLAG_SIZE+1];
    flag[FLAG_SIZE] = '\0';

    for (int i = 0; i < FLAG_SIZE; i++) {
        flag[i] = read_char(g, i*(CHAR_WIDTH+CHAR_SPACE));
    }

    return string(flag);
}

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

string run(string s) {
    istringstream input(s);
    string line;
    vector<Point> points;

    build_alphabet();

    while (getline(input, line)) {
        Point p;
        remove_if(line.begin(), line.end(), is_space);
        sscanf(line.c_str(), "position=<%d,%d>velocity=<%d,%d>", &p.x, &p.y, &p.vx, &p.vy);
        points.push_back(p);
    }

    while (max_dist_x(points) > FLAG_WIDTH || 
           max_dist_y(points) > CHAR_HEIGHT)
        advance(points);

    return read_flag(points);
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
