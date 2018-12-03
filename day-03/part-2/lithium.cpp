#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

string run(string s)
{
    stringstream ss(s);
    string line;
    vector<vector<int>> fabric(1000, vector<int>(1000));
    set<int> did_not_overlap = {};
    while (getline(ss, line))
    {
        size_t s1 = line.find('@');
        size_t s2 = line.find(',');
        size_t s3 = line.find(':');
        size_t s4 = line.find('x');
        int id = stoi(line.substr(1, s1));
        int left = stoi(line.substr(s1 + 2, s2));
        int top = stoi(line.substr(s2 + 1, s3));
        int right = left + stoi(line.substr(s3 + 2, s4));
        int bottom = top + stoi(line.substr(s4 + 1, line.length()));
        bool overlapped = false;
        for (int i = left; i < right; ++i)
            for (int j = top; j < bottom; ++j)
            {
                int target = fabric[i][j];
                if (target != 0)
                {
                    did_not_overlap.erase(target);
                    overlapped = true;
                }
                fabric[i][j] = id;
            }
        if (!overlapped)
            did_not_overlap.insert(id);
    }
    return to_string(*(did_not_overlap.begin()));
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
