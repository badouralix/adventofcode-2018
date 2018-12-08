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

    priority_queue<char, vector<char>, greater<char>> ready;
    for (auto const &x : requirements)
    {
        if (!x.second.size())
        {
            ready.push(x.first);
        }
    }

    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> events;
    int available_workers = 5;
    int t = 0;

    while (ready.size() || events.size())
    {
        if (ready.size() && available_workers)
        {
            char picked_task = ready.top();
            ready.pop();
            events.push(pair<int, char>(t + 60 + picked_task - 64, picked_task));
            available_workers--;
            continue;
        }
        else
        {
            char completed_task;
            tie(t, completed_task) = events.top();
            events.pop();
            available_workers++;
            for (auto &x : requirements)
            {
                if (x.second.find(completed_task) != x.second.end())
                {
                    if (x.second.size() == 1)
                    {
                        ready.push(x.first);
                    }
                    x.second.erase(completed_task);
                }
            }
        }
    }

    return to_string(t);
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
