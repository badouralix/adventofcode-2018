#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

string common(string s1, string s2)
{
    string output;
    for (unsigned int i = 0; i < s1.length(); i++)
        if (s1[i] == s2[i])
            output += s1[i];
    return output;
}

string run(string s)
{
    stringstream ss(s);
    string line;
    while (getline(ss, line))
    {
        stringstream _ss(s);
        string _line;
        while (getline(_ss, _line))
        {
            string c = common(line, _line);
            if (c.length() == line.length() - 1)
            {
                return c;
            }
        }
    }
    return "This should not have happened";
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
