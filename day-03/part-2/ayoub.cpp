#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};

int run(string s) {
    istringstream stream(s);
    string line;
    unordered_map<pair<int,int>, int, pair_hash> seen;
    int id, i, j, a, b;
    pair<int, int> p;

    while (getline(stream, line)) {
        sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id, &i, &j, &a, &b);
        for (int x = i; x < i+a; x++)
        for (int y = j; y < j+b; y++) {
            p = make_pair(x, y);
            if (seen.find(p) != seen.end()) seen[p]++;
            else seen[p] = 1;
        }
    }

    stream.clear();
    stream.str(s);

    while (getline(stream, line)) {
        sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id, &i, &j, &a, &b);
        bool overlap = false;
        for (int x = i; x < i+a; x++) {
            for (int y = j; y < j+b; y++) {
                p = make_pair(x, y);
                if (seen[p] > 1) {
                    overlap = true;
                    break;
                }
            }
            if (overlap) break;
        }
        if (!overlap) return id;
    }

    return -1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    auto answer = run(string(argv[1]));    
    cout << answer << "\n";
    return 0;
}
