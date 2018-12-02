#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string run(string s)
{
    istringstream f(s);
    string line;
    int total = 0;
    while (getline(f, line))
    {
        int value = stoi(line);
        total += value;
    }
    return to_string(total);
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
