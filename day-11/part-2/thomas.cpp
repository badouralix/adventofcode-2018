#include <iostream>
#include <string>
#include <ctime>

using namespace std;

string run(string s)
{
    int serial = stoi(s);
    int grid[301][301];
    for (int x = 1; x <= 300; x++)
    {
        for (int y = 1; y <= 300; y++)
        {
            int rack_id = x + 10;
            grid[x][y] = (rack_id * y + serial) * rack_id;
            grid[x][y] = (grid[x][y] % 1000 - grid[x][y] % 100) / 100;
            grid[x][y] -= 5;
        }
    }

    int maxi = numeric_limits<int>::min();
    int max_x;
    int max_y;
    int max_size;
    for (int size = 1; size <= 300; size++)
    {
        for (int x = 1; x < 302 - size; x++)
        {
            for (int y = 1; y < 302 - size; y++)
            {
                int total = 0;
                for (int i = x; i < x + size; i++)
                {
                    for (int j = y; j < y + size; j++)
                    {
                        total += grid[i][j];
                    }
                }
                if (total > maxi)
                {
                    maxi = total;
                    max_x = x;
                    max_y = y;
                    max_size = size;
                }
            }
        }
    }
    return to_string(max_x) + ',' + to_string(max_y) + ',' + to_string(max_size);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));

    cout << "_duration:" << float(clock() - start) * 1000.0 / CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
