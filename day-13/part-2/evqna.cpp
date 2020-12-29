#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const int GRID_SIZE = 150;

enum Facing {
    UP, RIGHT, DOWN, LEFT
};

Facing charToFacing(char cart) {
    if (cart == '<')    return LEFT;
    if (cart == '^')    return UP;
    if (cart == '>')    return RIGHT;
    if (cart == 'v')    return DOWN;
    exit(42);
}

enum Track {
    NONE, INTERSECTION, H, V, SLASH, BACKSLASH
};

Track charToTrack(char c) {
    switch (c) {
        case ' ':   return NONE;
        case '|': case 'v': case '^':   return V;
        case '-': case '<': case '>':   return H;
        case '\\':  return BACKSLASH;
        case '/':   return SLASH;
        case '+':   return INTERSECTION;
    }
    exit(37);
}

struct Cart {
    int x, y;
    Facing facing;
    Facing nextIntersection = LEFT;     // Pretend UP is 'go straight'
    bool crashed = false;

    // Order carts by x, y coords
    bool operator<(const Cart& b) const {
        return y < b.y || (y == b.y && x < b.x);
    }

    void move() {
        switch (facing) {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case UP:    y--; break;
            case DOWN:  y++; break;
        }
    }

    void updateFacing(Track track) {
        switch (track) {
            case SLASH:
                switch (facing) {
                    case UP:    facing = RIGHT; break;
                    case RIGHT: facing = UP; break;
                    case DOWN:  facing = LEFT; break;
                    case LEFT:  facing = DOWN; break;
                }
                break;
            case BACKSLASH:
                switch (facing) {
                    case UP:    facing = LEFT; break;
                    case RIGHT: facing = DOWN; break;
                    case DOWN:  facing = RIGHT; break;
                    case LEFT:  facing = UP; break;
                }
                break;
            case INTERSECTION:
                switch (nextIntersection) {
                    case LEFT:
                        switch (facing) {
                            case UP:    facing = LEFT; break;
                            case RIGHT: facing = UP; break;
                            case DOWN:  facing = RIGHT; break;
                            case LEFT:  facing = DOWN; break;
                        }
                        nextIntersection = UP;
                        break;
                    case UP:
                        nextIntersection = RIGHT;
                        break;
                    case RIGHT:
                        switch (facing) {
                            case UP:    facing = RIGHT; break;
                            case RIGHT: facing = DOWN; break;
                            case DOWN:  facing = LEFT; break;
                            case LEFT:  facing = UP; break;
                        }
                        nextIntersection = LEFT;
                    default:
                        break;
                }
            default:
                break;
        }
    }
};

struct State {
    array<array<Track, GRID_SIZE>, GRID_SIZE> tracks;
    vector<Cart> carts;
};

State parse(const string& in) {
    State state;
    istringstream iss(in);
    int y = 0;
    for (string line; getline(iss, line); y++) {
        for (int x = 0; x < line.length(); x++) {
            char c = line[x];
            state.tracks[y][x] = charToTrack(c);
            if (c == 'v' || c == '^' || c == '<' || c == '>')
                state.carts.push_back({x, y, charToFacing(c)});
        }
    }
    return state;
}

void tick(State& state) {
    // needed to iterate over carts in correct order
    sort(begin(state.carts), end(state.carts));

    for (size_t i = 0; i < state.carts.size(); i++) {
        // create a copy
        Cart moved_cart = state.carts[i];
        if (moved_cart.crashed) continue;
        moved_cart.move();

        // check for collisions
        for (Cart& c : state.carts) {
            if (c.x == moved_cart.x && c.y == moved_cart.y) {
                moved_cart.crashed = true;
                c.crashed = true;
            }
        }

        // update state
        Track tile = state.tracks[moved_cart.y][moved_cart.x];
        moved_cart.updateFacing(tile);
        state.carts[i] = moved_cart;
    }

    // delete crashed carts
    state.carts.erase(
        remove_if(
            begin(state.carts), end(state.carts),
            [](Cart c) { return c.crashed; }),
        end(state.carts));
}

string run(const string& s) {
    auto state = parse(s);

    while (state.carts.size() > 1) {
        tick(state);
    }

    auto cart = *state.carts.begin();
    return to_string(cart.x) + ',' + to_string(cart.y);
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
