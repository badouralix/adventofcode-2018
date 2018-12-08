#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int run(const string in) {
    istringstream iss(in);

    int doubles = 0, triples = 0;
    for (string line; getline(iss, line); ) {
        int hist[26] = {0};    // Letters are all in [a-z], just use array as histogram

        for (int i = 0; line[i] != 0; i++)
            hist[line[i] - 'a']++;
        
        bool has_double = false, has_triple = false;
        for (int count : hist) {
            if (count == 2)
                has_double = true;
            else if (count == 3)
                has_triple = true;
        }

        if (has_double)
            doubles++;
        if (has_triple)
            triples++;
    }

    return doubles * triples;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));
    
    cout << "_duration:" << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
