#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

vector<int> parse_input(string s)
{
    vector<int> output = {};
    size_t pos = s.find("\n");
    while ((pos = s.find("\n")) != std::string::npos) // check if we still find our delimiter in the string
    {
        output.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + 1); // "\n".length() == 1
    }
    output.push_back(stoi(s)); // let's not forget the last value
    return output;
}

int part1_loop(int f, set<int> seen, vector<int> modifs)
{
    for (auto it = modifs.begin(); it != modifs.end(); ++it)
    {
        f += *it;
        if (seen.count(f) == 1)
            return f;
        seen.insert(f);
    }
    return part1_loop(f, seen, modifs);
}

string run(string s)
{
    int f = 0;
    set<int> seen = {f};
    vector<int> modifs = parse_input(s);
    return to_string(part1_loop(f, seen, modifs));
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
