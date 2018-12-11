#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int fuel(int x, int y, int serial)
{
    return (((x + 10) * y + serial) * (x + 10) / 100) % 10 - 5;
}

string run(string s)
{
    int serial = stoi(s);
    int sa_table[301][301];
    ;
    for (int x = 1; x <= 300; x++)
    {
        for (int y = 1; y <= 300; y++)
        {
            sa_table[x][y] = fuel(x, y, serial) + sa_table[x][y - 1] + sa_table[x - 1][y] - sa_table[x - 1][y - 1];
        }
    }

    int maxi = INT32_MIN;
    int max_x;
    int max_y;
    int size = 3;
    for (int x = 0; x <= 300 - size; x++)
    {
        for (int y = 0; y <= 300 - size; y++)
        {
            int total = sa_table[x][y] + sa_table[x + size][y + size] - sa_table[x + size][y] - sa_table[x][y + size];
            if (total > maxi)
            {
                maxi = total;
                max_x = x + 1;
                max_y = y + 1;
            }
        }
    }
    return to_string(max_x) + ',' + to_string(max_y);
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
