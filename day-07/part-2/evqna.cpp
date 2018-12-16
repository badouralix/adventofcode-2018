#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int WORKERS = 5;
const int FIXED_TIME = 60;

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

struct Task {
    char id;
    int timeToCompletion;
};

void assignTasks(vector<Task>& workers, set<char>& tasks) {
    for (auto& task : workers) {
        if (task.id == 0 && !tasks.empty()) {
            char n = *tasks.begin();
            task.id = n;
            task.timeToCompletion = FIXED_TIME + (n - 'A' + 1);
            tasks.erase(n);
        }
    }
}

int run(const string& in) {
    auto graph = parse(in);
    auto available = findStartNodes(graph);

    int T = 0;
    int nDone = 0, nTasks = graph.outgoingEdges.size();
    vector<Task> workers(WORKERS);

    assignTasks(workers, available);

    while (nDone < nTasks) {
        auto done = workers[0];
        for (auto w : workers) {
            if (w.id > 0 && w.timeToCompletion < done.timeToCompletion || done.id == 0)
                done = w;
        }
        
        // Update timers, find available tasks and reassign work
        int elapsed = done.timeToCompletion;
        T += elapsed;
        nDone++;
        
        for (char m : graph.outgoingEdges[done.id]) {
            graph.incomingEdges[m].erase(done.id);
            if (graph.incomingEdges[m].empty())
                available.insert(m);
        }

        for (auto& w : workers) {
            if (w.id > 0) {
                w.timeToCompletion -= elapsed;
                if (w.id == done.id)
                    w.id = 0;
            }
        }

        assignTasks(workers, available);
    }

    return T;
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
