#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

int run(string s)
{
    int f = 0, sign, step;
    unordered_set<int> seen;
    seen.insert(f);

    while (1)
    {
        istringstream stream(s);
        string line;
        while (getline(stream, line))
        {
            sign = (line.at(0) == '+') ? 1 : -1;
            step = atoi(line.c_str() + 1);

            f += sign * step;

            if (seen.count(f))
                return f;
            seen.insert(f);
        }
    }

    return -1;
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
