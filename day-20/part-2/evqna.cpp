#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int TARGET_DISTANCE = 1000;

using Room = pair<int, int>;
// Adjacency graph representation
using Graph = map<Room, set<Room>>;

map<Room, int> bfs_get_shortest_paths(const Graph& g, const Room& from) {
    set<Room> visited;
    queue<Room> queue;
    map<Room, int> distances;

    visited.insert(from);
    queue.push(from);
    distances[from] = 0;

    while (!queue.empty()) {
        Room cur = queue.front();
        int d = distances[cur];
        for (const auto& next : g.at(cur)) {
            if (visited.count(next) > 0)
                continue;

            distances[next] = d + 1;
            visited.insert(next);
            queue.push(next);
        }
        queue.pop();
    }

    return distances;
}

Room move(const Room& from, char direction) {
    int x = from.first, y = from.second;
    switch (direction) {
        case 'N':   return { x, y+1 };
        case 'S':   return { x, y-1 };
        case 'E':   return { x+1, y };
        case 'W':   return { x-1, y };
        default:    return from;
    }
}

struct Parser {
    const string& regex;
    int cur = 0;

    Parser(const string& in) : regex(in) {}

    char peek() const {
        return regex[cur];
    }

    bool match(char token) {
        if (peek() == token) {
            cur++;
            return true;
        }
        return false;
    }

    bool match_any(const string& tokens) {
        for (char token : tokens) {
            if (match(token))
                return true;
        }
        return false;
    }

    void expect(char token) {
        if (!match(token)) {
            cout << "Parsing error at " << cur << ": expected " << token << ", got " << peek() << "\n";
            exit(1);
        }
    }

    set<Room> parse_branch(Graph& g, const set<Room>& start_points);
    set<Room> parse_group(Graph& g, const set<Room>& start_points);
    Graph parse_graph();
};

void dbg(const set<Room>& rooms) {
    for (const Room& r : rooms)
        cout << "(" << r.first << "," << r.second << ") ";
    cout << "\n";
}

set<Room> Parser::parse_group(Graph& g, const set<Room>& start) {
    set<Room> endpoints;
    do {
        set<Room> branch_endpoints = parse_branch(g, start);
        endpoints.insert(begin(branch_endpoints), end(branch_endpoints));
    } while (match('|'));

    expect(')');
    return endpoints;
}

set<Room> Parser::parse_branch(Graph& g, const set<Room>& start) {
    set<Room> current_rooms = start;
    while (true) {
        char c = peek();
        if (match('(')) {
            current_rooms = parse_group(g, current_rooms);
        } else if (match_any("NSEW")) {
            set<Room> next_rooms;
            // Apply move to the reachable set
            for (const Room& room : current_rooms) {
                Room next_room = move(room, c);
                g[room].insert(next_room);
                g[next_room].insert(room);
                next_rooms.insert(next_room);
            }
            current_rooms = next_rooms;
        } else {
            break;
        }
    }
    return current_rooms;
}

Graph Parser::parse_graph() {
    Graph g;
    Room start = {0, 0};
    g[start];

    expect('^');
    set<Room> endpoints = parse_branch(g, {start});
    expect('$');
    return g;
}

int run(const string& in) {
    Parser parser(in);
    auto graph = parser.parse_graph();
    auto distances = bfs_get_shortest_paths(graph, {0, 0});

    int counter = 0;
    for (const auto& entry : distances) {
        if (entry.second >= TARGET_DISTANCE) counter++;
    }
    return counter;
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
