#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

string run(string s)
{
    stringstream ss(s);
    string line;
    int dupes = 0;
    int triples = 0;
    while (getline(ss, line))
    {
        map<char, int> m;
        for (auto it = line.begin(); it != line.end(); ++it)
        {
            if (m.find(*it) == m.end()) // Si on ne trouve pas c dans m, on l'ajoute
                m.insert(make_pair(*it, 1));
            else
                m[*it] += 1;
        }
        bool HasDupes = false;
        bool HasTriples = false;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            switch (it->second)
            {
            case (2):
            {
                HasDupes = true;
                break;
            }
            case (3):
            {
                HasTriples = true;
                break;
            }
            }
        }
        if (HasDupes)
            dupes++;
        if (HasTriples)
            triples++;
    }
    return to_string(dupes * triples);
}

int main(int argc, char **argv)
{

    // if (argc < 2) {
    //     cout << "Missing one argument" << endl;
    //     exit(1);
    // }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
