#include <cstdio>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
    std::istringstream istream(argv[1]);

    int doubles = 0, triples = 0;
    for (std::string line; std::getline(istream, line); ) {
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
    int checksum = doubles * triples;
    printf("%d\n", checksum);

    return 0;
}
