#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

string run(const string s)
{
    vector<int> nb_nodes;
    vector<int> nb_metadata{0};
    unsigned int i = 0;
    int sum_metadata = 0;
    while (i < tree.size())
    {
        if (nb_nodes.empty() || nb_nodes.back())
        {
            nb_nodes.push_back(tree[i]);
            nb_metadata.push_back(tree[i + 1]);
            i += 2;
        }
        else
        {
            for (int j = 0; j < nb_metadata.back(); j++)
            {
                sum_metadata += tree[i + j];
            }
            i += nb_metadata.back();
            nb_metadata.pop_back();
            nb_nodes.pop_back();
            if (!nb_nodes.empty())
            {
                nb_nodes.back()--;
            }
        }
    }
    return to_string(sum_metadata);
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
