#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string run(string s)
{
    stringstream ss(s);
    string line;
    vector<vector<int>> fabric(1000, vector<int>(1000));
    int overlap_two_claims = 0;
    while (getline(ss, line))
    {
        size_t s2 = line.find(',');
        size_t s3 = line.find(':');
        size_t s4 = line.find('x');
        int left = stoi(line.substr(line.find('@') + 2, s2));
        int top = stoi(line.substr(s2 + 1, s3));
        int right = left + stoi(line.substr(s3 + 2, s4));
        int bottom = top + stoi(line.substr(s4 + 1, line.length()));
        for (int i = left; i < right; ++i)
        {
            for (int j = top; j < bottom; ++j)
            {
                fabric[i][j]++;
                if ((fabric[i])[j] == 2)
                    overlap_two_claims++;
            }
        }
    }
    return to_string(overlap_two_claims);
}

int main(int argc, char **argv)
{
    // if (argc < 2)
    // {
    //     cout << "Missing one argument" << endl;
    //     exit(1);
    // }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
