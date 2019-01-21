#include <array>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int GRID_SIZE = 300;

int powerLevel(int serialID, int x, int y) {
    int rackID = x + 10;
    int power = (rackID * y + serialID) * rackID;
    power = power / 100 - 10 * (power / 1000);
    return power - 5;
}

string run(const string& s) {
    int serialID = stoi(s);
    array<array<int, GRID_SIZE + 1>, GRID_SIZE + 1> accumulator = {0};

    for (int x = 1; x <= GRID_SIZE; x++)
        for (int y = 1; y <= GRID_SIZE; y++)
            accumulator[x][y] = powerLevel(serialID, x, y) + accumulator[x-1][y] + accumulator[x][y-1] - accumulator[x-1][y-1];

    int xMax = 0, yMax = 0, sizeMax = 0, powerMax = 0;
    for (int size = 1; size <= GRID_SIZE; size++) {
        for (int i = 0; i <= GRID_SIZE - size; i++) {
            for (int j = 0; j <= GRID_SIZE - size; j++) {
                int power = accumulator[i+size][j+size] - accumulator[i+size][j] - accumulator[i][j+size] + accumulator[i][j];
                if (power > powerMax) {
                    powerMax = power;
                    xMax = i+1;
                    yMax = j+1;
                    sizeMax = size;
                }
            }
        }
    }

    return to_string(xMax) + "," + to_string(yMax) + "," + to_string(sizeMax);
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
