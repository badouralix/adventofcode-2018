#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int run(string s)
{
    istringstream stream(s);
    string line;
    int f = 0, sign, step;

    while (getline(stream, line))
    {
        sign = (line.at(0) == '+') ? 1 : -1;
        step = atoi(line.c_str() + 1);

        f += sign * step;
    }

    return f;
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
