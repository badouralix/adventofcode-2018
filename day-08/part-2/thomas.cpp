#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

pair<int, int> process(vector<int> &tree, int i_node)
{
    vector<int> child_values;
    int node_value = 0;
    int nb_child = tree[i_node];
    int nb_meta = tree[i_node + 1];
    int end = i_node + 1;
    for (int i = 0; i < nb_child; i++)
    {
        auto res = process(tree, end + 1);
        child_values.push_back(res.first);
        end = res.second;
    }
    if (nb_child)
    {
        for (int i = end + 1; i <= end + nb_meta; i++)
        {
            if (tree[i] && tree[i] <= nb_child)
            {
                node_value += child_values[tree[i] - 1];
            }
        }
    }
    else
    {
        for (int i = end + 1; i <= end + nb_meta; i++)
        {
            node_value += tree[i];
        }
    }
    return pair<int, int>(node_value, end + nb_meta);
}

string run(string s)
{
    // Parse input
    istringstream stream(s);
    string line;
    vector<int> tree;
    while (getline(stream, line, ' '))
    {
        tree.push_back(atoi(line.c_str()));
    }
    return to_string(process(tree, 0).first);
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
