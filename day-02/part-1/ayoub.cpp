#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void occurences(string s, int counts[])
{
    for (int i = 0; i < 26; i++)
        counts[i] = 0;
    for (char c : s)
        counts[c - 'a']++;
}

bool check(int counts[], int repeated)
{
    for (int i = 0; i < 26; i++)
        if (counts[i] == repeated)
            return true;
    return false;
}

int run(string s)
{
    istringstream stream(s);
    string line;
    int two = 0, three = 0;
    int counts[26];

    while (getline(stream, line))
    {
        occurences(line, counts);
        if (check(counts, 2))
            two++;
        if (check(counts, 3))
            three++;
    }

    return two * three;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    auto answer = run(string(argv[1]));    
    cout << answer << "\n";    

    return 0;
}
