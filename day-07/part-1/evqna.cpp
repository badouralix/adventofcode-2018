#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

struct Graph {
    map<char, set<char>> outgoingEdges;
    map<char, set<char>> incomingEdges;
};

Graph parse(const string& in) {
    Graph g;
    istringstream iss(in);

    for (string line; getline(iss, line); ) {
        char prereq = line[5];
        char step = line[36];
        g.outgoingEdges[prereq].insert(step);
        g.incomingEdges[step].insert(prereq);
        // Hacks to ensure all nodes have an entry in both maps
        g.incomingEdges[prereq];
        g.outgoingEdges[step];
    }

    return g;
}

set<char> findStartNodes(const Graph& graph) {
    set<char> start;
    for (const auto& x : graph.incomingEdges) {
        if (x.second.empty())
            start.insert(x.first);
    }
    return start;
}

string run(const string& in) {
    auto graph = parse(in);
    auto available = findStartNodes(graph);

    string process;
    while (!available.empty()) {
        char n = *available.begin();
        process += n;

        for (char m : graph.outgoingEdges[n]) {
            // We don't really need to erase from outgoingEdges because it won't be read again
            graph.incomingEdges[m].erase(n);
            if (graph.incomingEdges[m].empty())
                available.insert(m);
        }

        available.erase(n);
    }

    return process;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Missing one argument" << endl;
        exit(1);
    }

    clock_t start = clock();
    auto answer = run(string(argv[1]));

    cout << "_duration:" << float(clock() - start) * 1000.0 / CLOCKS_PER_SEC << "\n";
    cout << answer << "\n";
    return 0;
}
