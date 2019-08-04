#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generateRecipes(vector<int>& recipes, int target) {
    int elf_1 = 0, elf_2 = 1;

    while (recipes.size() < target) {
        int newRecipe = recipes[elf_1] + recipes[elf_2];
        if (newRecipe >= 10)    recipes.push_back(1);
        recipes.push_back(newRecipe % 10);

        elf_1 = (elf_1 + 1 + recipes[elf_1]) % recipes.size();
        elf_2 = (elf_2 + 1 + recipes[elf_2]) % recipes.size();
    }
}

uint64_t run(const string& in) {
    int nRecipes = stoi(in);
    vector<int> scoreboard = {3, 7};

    generateRecipes(scoreboard, nRecipes + 10);

    uint64_t combinedScore = 0;
    for (int i = 0; i < 10; i++) {
        combinedScore = 10 * combinedScore + scoreboard[nRecipes + i];
    }
    return combinedScore;
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
