#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

enum class RegionType {
    ROCKY = 0, WET = 1, NARROW = 2,
};

using Cave = vector<vector<RegionType>>;

int erosion_level(const vector<vector<int>>& geology, int x, int y, int depth) {
    return (geology[y][x] + depth) % 20183;
}

vector<vector<int>> geology_index(int depth, int target_x, int target_y) {
    vector<vector<int>> geology(target_y + 1, vector<int>(target_x + 1));
    for (int y = 0; y <= target_y; y++) {
        for (int x = 0; x <= target_x; x++) {
            if ((x == 0 && y == 0) || (x == target_x && y == target_y))   continue;
            else if (y == 0)
                geology[y][x] = x * 16807;
            else if (x == 0)
                geology[y][x] = y * 48271;
            else
                geology[y][x] = erosion_level(geology, x-1, y, depth) * erosion_level(geology, x, y-1, depth);
        }
    }
    return geology;
}

Cave build_cave_system(int depth, int target_x, int target_y) {
    int w = target_x + 1, h = target_y + 1;
    Cave cave(h, vector<RegionType>(w));
    auto geology = geology_index(depth, target_x, target_y);
    for (int y = 0; y <= target_y; y++) {
        for (int x = 0; x <= target_x; x++) {
            int erosion = erosion_level(geology, x, y, depth);
            cave[y][x] = static_cast<RegionType>(erosion % 3);
        }
    }
    return cave;
}

int risk_level(Cave cave) {
    int risk = 0;
    for (const auto& row : cave) {
        for (const auto type : row) {
            risk += static_cast<int>(type);
        }
    }
    return risk;
}

void dbg(const Cave& cave) {
    for (const auto& row : cave) {
        for (const auto type : row) {
            char c = '.';
            if (type == RegionType::WET)
                c = '=';
            else if (type == RegionType::NARROW)
                c = '|';
            cout << c << " ";
        }
        cout << "\n";
    }
}

int run(const string& in) {
    istringstream iss(in);
    string line;
    int depth, target_x, target_y;

    getline(iss, line);
    sscanf(line.c_str(), "depth: %d", &depth);
    getline(iss, line);
    sscanf(line.c_str(), "target: %d,%d", &target_x, &target_y);

    auto cave = build_cave_system(depth, target_x, target_y);
    // dbg(cave);
    return risk_level(cave);
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
