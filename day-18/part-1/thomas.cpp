#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

void print(const vector<vector<char>> &world)
{
    cout << "********** Beginning *********" << endl;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world[0].size(); j++)
        {
            cout << world[i][j];
        }
        cout << endl;
    }
}

unordered_map<char, int> get_adjacent_counts(const vector<vector<char>> &world, const int i, const int j)
{
    unordered_map<char, int> res;
    if (i - 1 >= 0 and j - 1 >= 0)
    {
        res[world[i - 1][j - 1]] += 1;
    }
    if (i - 1 >= 0)
    {
        res[world[i - 1][j]] += 1;
    }
    if (i - 1 >= 0 && j + 1 < world[0].size())
    {
        res[world[i - 1][j + 1]] += 1;
    }
    if (j - 1 >= 0)
    {
        res[world[i][j - 1]] += 1;
    }
    if (j + 1 < world[0].size())
    {
        res[world[i][j + 1]] += 1;
    }
    if (i + 1 < world.size() && j - 1 >= 0)
    {
        res[world[i + 1][j - 1]] += 1;
    }
    if (i + 1 < world.size())
    {
        res[world[i + 1][j]] += 1;
    }
    if (i + 1 < world.size() && j + 1 < world[0].size())
    {
        res[world[i + 1][j + 1]] += 1;
    }
    return res;
}

string run(string s)
{
    int NB_ITERATIONS = 10;

    // Parse input
    istringstream stream(s);
    string line;
    vector<vector<char>> prev_world;
    vector<vector<char>> world;
    while (getline(stream, line))
    {
        prev_world.push_back(vector<char>(line.begin(), line.end()));
        world.push_back(vector<char>(line.begin(), line.end()));
    }

    for (int it = 0; it < NB_ITERATIONS; it++)
    {
        for (int i = 0; i < world.size(); i++)
        {
            for (int j = 0; j < world[0].size(); j++)
            {
                auto adjacents = get_adjacent_counts(prev_world, i, j);
                if (prev_world[i][j] == '.' && adjacents['|'] >= 3)
                {
                    world[i][j] = '|';
                }
                else if (prev_world[i][j] == '|' && adjacents['#'] >= 3)
                {
                    world[i][j] = '#';
                }
                else if (prev_world[i][j] == '#' && (adjacents['#'] == 0 || adjacents['|'] == 0))
                {
                    world[i][j] = '.';
                }
            }
        }
        prev_world = vector<vector<char>>(world);
    }

    int trees = 0;
    int lumberyard = 0;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world[0].size(); j++)
        {
            trees += world[i][j] == '|';
            lumberyard += world[i][j] == '#';
        }
    }

    return to_string(trees * lumberyard);
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
