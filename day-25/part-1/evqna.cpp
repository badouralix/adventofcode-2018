#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int CONSTELLATION_MAX_DELTA = 3;

struct Coord {
    int x, y, z, t;
};

int d(Coord A, Coord B) {
    return abs(A.x - B.x) + abs(A.y - B.y) + abs(A.z - B.z) + abs(A.t - B.t);
}

bool connected(Coord A, Coord B) {
    return d(A, B) <= CONSTELLATION_MAX_DELTA;
}

vector<Coord> parse_input(const string& in) {
    istringstream iss(in);
    vector<Coord> vec;
    for (string line; getline(iss, line); ) {
        Coord c;
        sscanf(line.c_str(), "%d,%d,%d,%d", &c.x, &c.y, &c.z, &c.t);
        vec.push_back(c);
    }
    return vec;
}

struct Graph {
    int N;
    vector<bool> adj;

    Graph(int _N) : N(_N) {
        adj.resize(N * N);
    }

    bool get(int i, int j) const {
        return adj[N * i + j];
    }

    void set(int i, int j) {
        adj[N * i + j] = true;
        adj[N * j + i] = true;
    }
};

void dfs_connected_component(const Graph& g, int node, int component, vector<int>& components) {
    components[node] = component;
    for (int i = 0; i < g.N; i++) {
        if (g.get(node, i) && components[i] == 0)
            dfs_connected_component(g, i, component, components);
    }
}

int count_connected_components(const Graph& g) {
    vector<int> node_to_component(g.N);
    int component = 0;
    for (int i = 0; i < g.N; i++) {
        if (node_to_component[i] == 0) {
            component++;
            dfs_connected_component(g, i, component, node_to_component);
        }
    }
    return component;
}

int run(const string& s) {
    auto coords = parse_input(s);
    
    Graph g(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        for (size_t j = i + 1; j < coords.size(); j++) {
            if (connected(coords[i], coords[j])) {
                g.set(i, j);
            }
        }
    }

    return count_connected_components(g);
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
