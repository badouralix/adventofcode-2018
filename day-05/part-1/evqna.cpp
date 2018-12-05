#include <cstdio>
#include <string>

int abs(int x) {
    return x >= 0 ? x : -x;
}

int solve(std::string& input) {
    bool hasChanged;
    do {
        hasChanged = false;
        size_t i = 0;
        while (i < input.length() - 1) {
            if (abs(input[i] - input[i+1]) == 32) {     // Hack for lower/upper case check
                input.erase(i, 2);
                hasChanged = true;
                // Opti: backtrack one character
                if (i > 0)  i--;
            }
            else {
                i++;
            }
        }
    } while(hasChanged);

    return input.length();
}

int main(int argc, char *argv[]) {
    auto input = std::string(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
