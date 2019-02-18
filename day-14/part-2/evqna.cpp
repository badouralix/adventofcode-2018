#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool hasSuffix(const vector<int>& A, const vector<int>& suffix) {
    return equal(suffix.rbegin(), suffix.rend(), A.rbegin());
}

void generateRecipes(vector<int>& recipes, const vector<int>& target) {
    int elf_1 = 0, elf_2 = 1;

    while (!hasSuffix(recipes, target)) {
        int newRecipe = recipes[elf_1] + recipes[elf_2];
        if (newRecipe >= 10) {
            recipes.push_back(1);
            if (hasSuffix(recipes, target)) return;
        }
        recipes.push_back(newRecipe % 10);

        elf_1 = (elf_1 + 1 + recipes[elf_1]) % recipes.size();
        elf_2 = (elf_2 + 1 + recipes[elf_2]) % recipes.size();
    }
}

vector<int> stov(const string& s) {
    vector<int> v;
    for (char c : s)
        v.push_back(c - '0');
    return v;
}

int run(const string& in) {
    vector<int> scoreboard = {3, 7};
    vector<int> target = stov(in);

    generateRecipes(scoreboard, target);

    return scoreboard.size() - target.size();
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
