#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

string run(string s)
{
    // Parse input
    istringstream stream(s);
    string line;
    unordered_map<char, set<char>> requirements;
    while (getline(stream, line))
    {
        char from_task = line[5];
        char to_task = line[36];
        requirements[to_task].insert(from_task);
        requirements.emplace(pair<char, set<char>>(from_task, {}));
    }

    // Topological sort
    priority_queue<char, vector<char>, greater<char>> ready;
    for (auto const &x : requirements)
    {
        if (!x.second.size())
        {
            ready.push(x.first);
        }
    }
    vector<char> ordered_tasks;

    while (ready.size())
    {
        char task = ready.top();
        ready.pop();
        ordered_tasks.push_back(task);
        for (auto &x : requirements)
        {
            if (x.second.find(task) != x.second.end())
            {
                if (x.second.size() == 1)
                {
                    ready.push(x.first);
                }
                x.second.erase(task);
            }
        }
    }

    return string(ordered_tasks.begin(), ordered_tasks.end());
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
