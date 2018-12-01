#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string run(string s)
{
    string line;
    istringstream stringStream(s);
    int res = 0;
    while (std::getline(stringStream, line, '\n'))
    {
        res += stoi(line.c_str());
    }
    return to_string(res);
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
