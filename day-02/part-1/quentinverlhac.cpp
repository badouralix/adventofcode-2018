#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

string run(string s)
{
    istringstream iss(s);
    string line;
    int twoLetters = 0;
    int threeLetters = 0;
    while (getline(iss, line))
    {
        map<char, int> map;
        string::iterator it;
        int twoLettersInLine = 0;
        int threeLettersInLine = 0;
        for (it = line.begin(); it < line.end(); it++)
        {
            char letter = *it;
            if (map.count(letter) > 0)
            {
                map[letter] += 1;
                int occurences = map[letter];
                if (occurences == 2)
                {
                    twoLettersInLine += 1;
                }
                else
                {
                    twoLettersInLine -= 1;
                    if (occurences == 3)
                    {
                        threeLettersInLine += 1;
                    }
                    else
                    {
                        threeLettersInLine -= 1;
                    }
                }
            }
            else
            {
                map.insert({letter, 1});
            }
        }
        if (twoLettersInLine >= 1)
        {
            twoLetters += 1;
        }
        if (threeLettersInLine >= 1)
        {
            threeLetters += 1;
        }
    }
    return to_string(twoLetters * threeLetters);
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
