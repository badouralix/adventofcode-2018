#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

void print(const vector<vector<char>> &world, ostream &output = cout)
{
    output << "********** Beginning *********" << endl;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world[0].size(); j++)
        {
            output << world[i][j];
        }
        output << endl;
    }
}

vector<vector<char>> from_string(string s)
{
    // Parse input
    istringstream stream(s);
    string line;
    vector<vector<char>> world;
    while (getline(stream, line))
    {
        world.push_back(vector<char>(line.begin(), line.end()));
    }

    return world;
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
    int NB_ITERATIONS = 1000000000;

    vector<vector<char>> world = from_string(s);
    vector<vector<char>> prev_world = vector<vector<char>>(world);

    unordered_map<string, int> prev_worlds = {{s, 0}};
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
        ostringstream os;
        print(world, os);
        string str = os.str();
        if (prev_worlds.find(str) == prev_worlds.end())
        {
            prev_worlds[str] = it;
        }
        else
        {
            unordered_map<int, string> inv_dict;

            for (auto i = prev_worlds.begin(); i != prev_worlds.end(); ++i)
            {
                inv_dict[i->second] = i->first;
            }

            int beginning_cycle = prev_worlds[str];
            int length_cycle = it - beginning_cycle;
            world = from_string(inv_dict[beginning_cycle + (NB_ITERATIONS - it - 1) % length_cycle]);

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
    }

    return "";
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
