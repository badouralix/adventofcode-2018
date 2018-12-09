#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Board {
    list<int> b = {0};
    list<int>::iterator current = b.begin();

    void clockwise() {
        if (current == b.end())
            current = b.begin();
        current++;
    }

    void counterclockwise(int n) {
        for (int i = 0; i < n; i++) {
            if (current == b.begin())
                current = b.end();
            current--;
        }
    }

    int play(int marble) {
        if (marble % 23 != 0) {
            clockwise();
            b.insert(current, marble);
            return 0;
        }

        counterclockwise(8);
        int score = marble + *current;
        current = b.erase(current);
        clockwise();
        return score;
    }
};

uint64_t run(const string& s) {
    int players, lastMarble;
    istringstream iss(s);
    iss >> players;
    iss.ignore(30);
    iss >> lastMarble;
    lastMarble *= 100;

    Board board;
    vector<uint64_t> scores(players);
    int currentPlayer = 0;
    for(int nextMarble = 1; nextMarble <= lastMarble; nextMarble++) {
        scores[currentPlayer] += board.play(nextMarble);
        currentPlayer = (currentPlayer + 1) % players;
    }

    return *max_element(scores.begin(), scores.end());
}

int main(int argc, char** argv) {
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
