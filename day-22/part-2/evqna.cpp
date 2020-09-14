#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <ctime>

using namespace std;

const int TOOL_SWITCH_COST = 7;

enum class Terrain {
    ROCKY = 0, WET = 1, NARROW = 2,
};

enum class Tool {
    NONE = 0, TORCH = 1, CLIMBING_GEAR = 2,
};

bool is_tool_compatible_with_terrain(int tool_id, Terrain terrain) {
    return tool_id != static_cast<int>(terrain);
}

// Implements a self-resizing 2D grid to provide
// convenient unbounded access to cave data.
class Cave {
  private:
    const int depth;
    vector<vector<int>> geology_data = {{0}};

    int erosion_level(int x, int y) const {
        return (geology_data[y][x] + depth) % 20183;
    }

    int geology_index(int x, int y) const {
        if (x == 0)
            return y * 48271;
        if (y == 0)
            return x * 16807;
        return erosion_level(x-1, y) * erosion_level(x, y-1);
    }

    int terrain_type(int x, int y) const {
        return erosion_level(x, y) % 3;
    }

    // Size of the currently mapped region:
    // (0,0) ... (max_x, max_y) (inclusive)
    int max_x = 0, max_y = 0;
    // Resize container to include target and compute
    // necessary geology data.
    void expand_mapping(int target_x, int target_y) {
         if (target_x > max_x) {
            for (int y = 0; y <= max_y; y++) {
                geology_data[y].resize(target_x + 1);
                for (int x = max_x + 1; x <= target_x; x++)
                    geology_data[y][x] = geology_index(x, y);
            }
            max_x = target_x;
        }

        if (target_y > max_y) {
            for (int y = max_y + 1; y <= target_y; y++) {
                geology_data.push_back(vector<int>(max_x + 1));
                for (int x = 0; x <= max_x; x++)
                    geology_data[y][x] = geology_index(x, y);
            }
            max_y = target_y;
        }
    }

  public:
    Cave(int depth_, int target_x, int target_y)
      : depth(depth_) {
        expand_mapping(target_x, target_y);
        geology_data[target_y][target_x] = 0;
    }

    Terrain get_region_type(int x, int y) {
        if (x > max_x || y > max_y)
            expand_mapping(x, y);
        return static_cast<Terrain>(terrain_type(x, y));
    }

    void dbg() const {
        const char terrain_display[] = {'.', '=', '|'};
        for (int y = 0; y <= max_y; y++) {
            for (int x = 0; x <= max_x; x++) {
                cout << terrain_display[terrain_type(x, y)] << " ";
            }
            cout << "\n";
        }
    }
};

struct NodeId {
    int x, y;
    int tool_id;

    bool operator==(const NodeId& rhs) const {
        return x == rhs.x && y == rhs.y && tool_id == rhs.tool_id;
    }
};

// Basic hashing for node id to enable hash set lookup
namespace std {
    template<> struct hash<NodeId> {
        size_t operator()(const NodeId& n) const noexcept {
            return hash<int>{}(1000 * n.x + n.y);
        }
    };
}

struct Node {
    NodeId id;
    int distance;

    bool operator>(const Node& rhs) const {
        return distance > rhs.distance;
    }
};

struct Edge {
    NodeId dest;
    int cost;
};

const int DELTAS[][2] = {{0,-1}, {-1,0}, {+1,0}, {0,+1}};

vector<Edge> outgoing_edges(Cave& cave, NodeId node) {
    vector<Edge> edges;
    // Move to adjacent region with current tool
    for (auto delta : DELTAS) {
        int x = node.x + delta[0];
        int y = node.y + delta[1];
        if (x >= 0 && y >= 0) {
            Terrain terrain = cave.get_region_type(x, y);
            if (is_tool_compatible_with_terrain(node.tool_id, terrain))
                edges.push_back({{x, y, node.tool_id}, 1});
        }
    }
    // Switch tool in current region
    for (int other_tool = 0; other_tool < 3; other_tool++) {
        if (is_tool_compatible_with_terrain(other_tool, cave.get_region_type(node.x, node.y))
            && other_tool != node.tool_id) {
            edges.push_back({{node.x, node.y, other_tool}, TOOL_SWITCH_COST});
        }
    }
    return edges;
}

int get_shortest_path(Cave& cave, int target_x, int target_y, Tool equipped_tool) {
    // Dijsktra shortest path implementation

    // Priority queue has max-heap semantics by default, so we invert the comparator.
    priority_queue<Node, vector<Node>, greater<Node>> queue;
    unordered_set<NodeId> visited;

    NodeId start = {0, 0, static_cast<int>(equipped_tool)};
    NodeId target = {target_x, target_y, static_cast<int>(Tool::TORCH)};

    queue.push({start, 0});

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();

        if (current.id == target)
            return current.distance;

        if (visited.count(current.id) > 0)
            continue;

        for (Edge edge : outgoing_edges(cave, current.id)) {
            if (visited.count(edge.dest) == 0)
                queue.push({edge.dest, current.distance + edge.cost});
        }

        visited.insert(current.id);
    }

    cout << "Error: did not reach target node\n";
    return -1;
}

int run(const string& in) {
    istringstream iss(in);
    string line;
    int depth, target_x, target_y;

    getline(iss, line);
    sscanf(line.c_str(), "depth: %d", &depth);
    getline(iss, line);
    sscanf(line.c_str(), "target: %d,%d", &target_x, &target_y);

    auto cave = Cave(depth, target_x, target_y);
    // cave.dbg();

    return get_shortest_path(cave, target_x, target_y, Tool::TORCH);
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
