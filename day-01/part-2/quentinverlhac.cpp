#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

string run(string s)
{
    map<int, int> m;
    signed int frequency = -1;
    int total = 0;
    while (frequency < 0)
    {
        istringstream f(s);
        string line;
        while (frequency < 0 && getline(f, line))
        {
            int value = stoi(line);
            total += value;
            if (m.count(total) > 0)
            {
                frequency = total;
            }
            else
            {
                m.insert({total, 1});
            }
        }
        f.str(std::string());
    }
    return to_string(frequency);
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
