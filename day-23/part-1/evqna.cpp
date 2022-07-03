#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Bot {
    int x, y, z;
    int r;
};

vector<Bot> parse_input(const string& in) {
    istringstream iss(in);
    vector<Bot> vec;
    for (string line; getline(iss, line); ) {
        Bot bot;
        sscanf(line.c_str(), "pos=<%d,%d,%d>, r=%d",
                &bot.x, &bot.y, &bot.z, &bot.r);
        vec.push_back(bot);
    }
    return vec;
}

int abs(int x) {
    return x >= 0 ? x : -x;
}

int distance(Bot a, Bot b) {
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int count_in_range(Bot of, const vector<Bot>& bots) {
    int count = 0;
    for (Bot bot : bots) {
        if (distance(bot, of) <= of.r)
            count++;
    }
    return count;
}

int run(const string& in) {
    auto bots = parse_input(in);

    Bot strongest = *max_element(begin(bots), end(bots),
        [](const Bot& a, const Bot& b){ return a.r < b.r; });

    return count_in_range(strongest, bots);
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
