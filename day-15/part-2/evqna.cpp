#include <algorithm>
#include <climits>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Grid deltas sorted in reading order
const int DELTAS[][2] = {{0,-1}, {-1,0}, {+1,0}, {0,+1}};

enum class Object : char {
    OPEN = '.',
    WALL = '#',
    ELF = 'E',
    GOBLIN = 'G',
};

using Board = vector<vector<Object>>;

Board parse_input(const string& in) {
    istringstream iss(in);
    Board board;
    for (string line; getline(iss, line); ) {
        vector<Object> row;
        for (char c : line) {
            Object obj = static_cast<Object>(c);
            row.push_back(obj);
        }
        board.push_back(row);
    }
    return board;
}

struct Entity {
    Object type;
    int x, y;
    int attack;
    int hp = 200;

    Entity(Object _type, int _x, int _y, int _attack)
     : type(_type), x(_x), y(_y), attack(_attack) {}
};

// Map every tile to its entity id (index in entity vector)
// or -1 for open/wall tiles
using BoardToEntity = vector<vector<int>>;

struct BoardState {
    Board board;
    vector<Entity> entities;
    BoardToEntity entity_lookup;

    void dbg() const {
        for (size_t y = 0; y < board.size(); y++) {
            vector<int> entity_ids;
            for (size_t x = 0; x < board[y].size(); x++) {
                cout << static_cast<char>(board[y][x]);
                if (entity_lookup[y][x] != -1)
                    entity_ids.push_back(entity_lookup[y][x]);
            }
            for (const int entity_idx : entity_ids) {
                cout << " " << static_cast<char>(entities[entity_idx].type)
                     << " (" << entities[entity_idx].hp << ")";
            }
            cout << '\n';
        }
    }
};

void init_entities(BoardState& state, int elf_attack) {
    Board& board = state.board;
    state.entity_lookup.resize(board.size(), vector<int>(board[0].size(), -1));

    int next_id = 0;
    for (size_t y = 0; y < board.size(); y++) {
        for (size_t x = 0; x < board[y].size(); x++) {
            Object obj = board[y][x];
            if (obj == Object::ELF || obj == Object::GOBLIN) {
                int attack = (obj == Object::ELF) ? elf_attack : 3;
                state.entities.push_back(Entity(obj, x, y, attack));
                state.entity_lookup[y][x] = next_id++;
            }
        }
    }
}

// Store coordinates in {y, x} order because this matches
// the reading order (ie. sorting will do the right thing)
using Node = pair<int, int>;

Node resolve_target_ties(vector<Node>& targets) {
    return *min_element(begin(targets), end(targets));
}

int backtrack_path(Node start, Node end, map<Node, int>& followed_deltas) {
    Node cur = end;
    int delta = 0;
    while (cur != start) {
        delta = followed_deltas[cur];
        cur.second -= DELTAS[delta][0];
        cur.first -= DELTAS[delta][1];
    }
    return delta;
}

int find_target(const Entity& entity, const Board& board) {
    // BFS implementation
    set<Node> visited;
    queue<Node> queue;

    // Keep track of deltas that were followed to recompute full path
    map<Node, int> followed_deltas;
    // We need to find all targets at distance d then break ties
    map<Node, int> distance;
    // Targets are the tiles adjacent to enemy entities
    vector<Node> targets;
    int target_distance = -1;

    Node root = {entity.y, entity.x};
    visited.insert(root);
    queue.push(root);
    distance[root] = 0;

    while (!queue.empty()) {
        Node cur = queue.front();
        int d = distance[cur];

        // Break early if we move further than discovered targets
        if (target_distance >= 0 && d > target_distance)
            break;

        // Check for enemies in adjacent tiles,
        // if yes this tile is a target
        for (int i = 0; i < 4; i++) {
            int x = cur.second + DELTAS[i][0];
            int y = cur.first + DELTAS[i][1];
            Node next = {y, x};

            if (board[y][x] == Object::WALL || visited.count(next) > 0)
                continue;

            followed_deltas[next] = i;
            distance[next] = d + 1;
            visited.insert(next);
            if (board[y][x] == Object::OPEN) {
                queue.push(next);
            }
            else if (board[y][x] != entity.type) {
                // Found an enemy!
                // Mark the current node as a possible target and
                // keep looking for other targets at the same distance
                if (target_distance < 0)
                    target_distance = d;
                targets.push_back(cur);
                break;
            }
        }
        queue.pop();
    }

    if (targets.empty())
        return -1;

    Node target = resolve_target_ties(targets);
    // Assumes root != target (ie. no adjacent targets)
    return backtrack_path(root, target, followed_deltas);
}

bool is_target(Object object, const Entity& entity) {
    return (object == Object::ELF || object == Object::GOBLIN)
        && object != entity.type;
}

bool has_adjacent_target(const Entity& entity, const Board& board) {
    for (int i = 0; i < 4; i++) {
        int x = entity.x + DELTAS[i][0];
        int y = entity.y + DELTAS[i][1];
        if (is_target(board[y][x], entity))
            return true;
    }
    return false;
}

bool move(Entity& entity, BoardState& state) {
    if (has_adjacent_target(entity, state.board))
        return true;

    int direction = find_target(entity, state.board);
    if (direction < 0)
        return false;

    int x = entity.x + DELTAS[direction][0];
    int y = entity.y + DELTAS[direction][1];
    if (state.board[y][x] == Object::OPEN) {
        state.board[y][x] = entity.type;
        state.entity_lookup[y][x] = state.entity_lookup[entity.y][entity.x];
        state.board[entity.y][entity.x] = Object::OPEN;
        state.entity_lookup[entity.y][entity.x] = -1;
        entity.x = x;
        entity.y = y;
    }
    return true;
}

void attack(const Entity& attacker, BoardState& state) {
    int target_id = -1, min_hp = INT_MAX;
    for (int i = 0; i < 4; i++) {
        int x = attacker.x + DELTAS[i][0];
        int y = attacker.y + DELTAS[i][1];
        int id = state.entity_lookup[y][x];
        if (id != -1 && attacker.type != state.entities[id].type) {
            int target_hp = state.entities[id].hp;
            if (target_hp > 0 && target_hp < min_hp) {
                min_hp = target_hp;
                target_id = id;
            }
        }
    }

    if (target_id != -1) {
        Entity& target = state.entities[target_id];
        target.hp -= attacker.attack;
        if (target.hp <= 0) {
            state.board[target.y][target.x] = Object::OPEN;
            state.entity_lookup[target.y][target.x] = -1;
        }
    }
}

bool targets_exist(const Entity& entity, const BoardState& state) {
    for (const Entity& other : state.entities) {
        if (is_target(other.type, entity) && other.hp > 0)
            return true;
    }
    return false;
}

bool fight_round(BoardState& state) {
    Board& board = state.board;
    set<int> updated_entities;
    for (size_t y = 0; y < board.size(); y++) {
        for (size_t x = 0; x < board[y].size(); x++) {
            if (board[y][x] == Object::ELF || board[y][x] == Object::GOBLIN) {
                int entity_id = state.entity_lookup[y][x];
                if (updated_entities.count(entity_id) == 0) {
                    Entity& entity = state.entities[entity_id];

                    bool target_found = move(entity, state);
                    if (!target_found && !targets_exist(entity, state))
                        return false;
                    attack(entity, state);
                    updated_entities.insert(entity_id);
                }
            }
        }
    }
    return true;
}

int num_elves_alive(const vector<Entity>& entities) {
    int total = 0;
    for (const Entity& entity : entities) {
        if (entity.type == Object::ELF && entity.hp > 0)
            total++;
    }
    return total;
}

int outcome(int completed_rounds, const BoardState& final_state) {
    int hp_left = 0;
    for (const Entity& e : final_state.entities) {
        if (e.hp > 0)   hp_left += e.hp;
    }
    return completed_rounds * hp_left;
}

int run(const string& in) {
    BoardState initial_state;
    initial_state.board = parse_input(in);

    init_entities(initial_state, 3);
    int starting_elves = num_elves_alive(initial_state.entities);

    int elf_attack = 4;
    bool elves_win = false;
    int final_outcome = -1;
    while (!elves_win) {
        // Clone initial state
        BoardState state = initial_state;
        state.entities.clear();
        init_entities(state, elf_attack);

        int completed_rounds = 0;
        int elves_alive = starting_elves;
        while (fight_round(state)) {
            completed_rounds++;
            elves_alive = num_elves_alive(state.entities);
            if (elves_alive < starting_elves)
                break;
        }

        if (elves_alive == starting_elves) {
            elves_win = true;
            final_outcome = outcome(completed_rounds, state);
        }

        elf_attack++;
    }

    return final_outcome;
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
