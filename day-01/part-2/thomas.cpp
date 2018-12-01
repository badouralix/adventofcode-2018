#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

string run(string s)
{
    string line;
    int res = 0;
    set<int> seen({0});
    while (1)
    {
        istringstream stringStream(s);
        while (std::getline(stringStream, line, '\n'))
        {
            res += stoi(line.c_str());
            if (seen.find(res) != seen.end())
            {
                return to_string(res);
            }
            seen.insert(res);
        }
    }
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
