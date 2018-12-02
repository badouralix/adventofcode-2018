#include <iostream>
#include <string>

using namespace std;

string part1(string s)
{
    int f = 0;
    size_t pos = s.find("\n");
    while ((pos = s.find("\n")) != std::string::npos) // check if we still find our delimiter in the string
    {
        f += stoi(s.substr(0, pos));
        s.erase(0, pos + 1); // "\n".length() == 1
    }
    f += stoi(s); // let's not forget the last value
    return to_string(f);
}

string run(string s)
{
    return part1(s);
}

int main(int argc, char **argv)
{
    /* Gain some ms
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    */
    cout << run(string(argv[1])) << "\n";
    return 0;
}
