#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

enum class ArmyType {
    IMMUNE_SYSTEM, INFECTION,
};

struct UnitGroup {
    ArmyType army;
    int n_units;
    int hit_points;
    int initiative;
    int attack_damage;
    string damage_type;
    set<string> immunities;
    set<string> weaknesses;

    bool alive() const {
        return n_units > 0;
    }

    int effective_power() const {
        return n_units * attack_damage;
    }

    int damage_vs(const UnitGroup& target) const {
        if (target.immunities.count(damage_type) > 0)
            return 0;
        if (target.weaknesses.count(damage_type) > 0)
            return 2 * effective_power();
        return effective_power();
    }

    int attack(UnitGroup& target) {
        int damage = damage_vs(target);
        int units_killed = min(damage / target.hit_points, target.n_units);
        target.n_units -= units_killed;
        return units_killed;
    }

    void dbg() const {
        cout << n_units << " " << hit_points << " " << attack_damage << " "
             << damage_type << " " << initiative;
        cout << " i:";
        for (auto& mod : immunities)
            cout << mod << ",";
        cout << " w:";
        for (auto& mod : weaknesses)
            cout << mod << ",";
        cout << "\n";
    }
};

using Units = vector<UnitGroup>;

void parse_modifiers(UnitGroup& g, const string& s) {
    istringstream iss(s);
    for (string mod_group; getline(iss, mod_group, ';'); ) {
        istringstream iss2(mod_group);
        string modifier_type;
        iss2 >> modifier_type;
        iss2.ignore(3); // "to "
        for (string damage_type; getline(iss2, damage_type, ','); ) {
            damage_type = damage_type.substr(1);    // Leading space
            if (modifier_type == "immune")
                g.immunities.insert(damage_type);
            else
                g.weaknesses.insert(damage_type);
        }
    }
}

UnitGroup parse_group(const string& line) {
    UnitGroup group;
    istringstream iss(line);

    size_t mod_start = line.find('(');
    size_t mod_end = line.find(')');

    if (mod_start != string::npos)
        parse_modifiers(group, line.substr(mod_start + 1, mod_end - mod_start - 1));

    iss >> group.n_units;
    iss.ignore(17); // " units each with "
    iss >> group.hit_points;
    iss.ignore(37); // " hit points with an attack that does "

    if (mod_start != string::npos)
        iss.ignore(mod_end - mod_start + 2);

    iss >> group.attack_damage;
    iss >> group.damage_type;
    iss.ignore(22); // " damage at initiative "
    iss >> group.initiative;

    return group;
}

Units parse_army(istringstream& iss, ArmyType type) {
    Units army;
    string line;
    // Skip army header
    getline(iss, line);
    while (getline(iss, line) && !line.empty()) {
        UnitGroup group = parse_group(line);
        group.army = type;
        army.push_back(group);
    }
    return army;
}

Units parse_input(const string& in) {
    Units all_units;
    istringstream iss(in);
    
    Units immune_system = parse_army(iss, ArmyType::IMMUNE_SYSTEM);
    Units infection = parse_army(iss, ArmyType::INFECTION);

    all_units.insert(all_units.end(), immune_system.begin(), immune_system.end());
    all_units.insert(all_units.end(), infection.begin(), infection.end());

    return all_units;
}

bool army_eliminated(const Units& all_units) {
    int immune_alive = 0, infection_alive = 0;
    for (const auto& unit : all_units) {
        if (unit.alive()) {
            if (unit.army == ArmyType::IMMUNE_SYSTEM)   immune_alive++;
            if (unit.army == ArmyType::INFECTION)       infection_alive++;
        }
    }
    return immune_alive == 0 || infection_alive == 0;
}

int find_target_id(const UnitGroup& attacker, const Units& units, const set<int>& reserved_targets) {
    int target_id = -1;
    int max_damage = 0;
    int max_target_power = 0;
    int max_target_initiative = 0;
    for (size_t i = 0; i < units.size(); i++) {
        const UnitGroup& defender = units[i];
        if (defender.alive() && defender.army != attacker.army && reserved_targets.count(i) == 0) {
            int damage = attacker.damage_vs(defender);
            int target_power = defender.effective_power();
            int target_initiative = defender.initiative;

            if (damage == 0)    continue;

            if (damage > max_damage || (damage == max_damage && target_power > max_target_power)
                || (damage == max_damage && target_power == max_target_power && target_initiative > max_target_initiative)) {
                target_id = i;
                max_damage = damage;
                max_target_power = target_power;
                max_target_initiative = target_initiative;
            }
        }
    }
    return target_id;
}

vector<int> select_targets(const Units& units) {
    vector<int> target_selection_order(units.size());
    iota(target_selection_order.begin(), target_selection_order.end(), 0);  // Init [0, n)
    sort(target_selection_order.begin(), target_selection_order.end(),
        [&units](const int& a, const int& b) {
            const UnitGroup& lhs = units[a];
            const UnitGroup& rhs = units[b];
            return lhs.effective_power() > rhs.effective_power()
                    || (lhs.effective_power() == rhs.effective_power()
                        && lhs.initiative > rhs.initiative);
        });

    vector<int> targets(units.size());    // targets[attacker] = defender (indexing into units)
    set<int> reserved_targets;
    for (const int i : target_selection_order) {
        const UnitGroup& attacker = units[i];
        if (attacker.alive()) {
            int target = find_target_id(attacker, units, reserved_targets);
            targets[i] = target;
            if (target != -1) {
                reserved_targets.insert(target);
            }
        }
    }
    return targets;
}

bool resolve_attacks(Units& units, const vector<int>& targets) {
    vector<int> attack_resolution_order(units.size());                          // Indices into units
    iota(attack_resolution_order.begin(), attack_resolution_order.end(), 0);    // Init [0, n)
    sort(attack_resolution_order.begin(), attack_resolution_order.end(),
        [&units](const int a, const int b) {
            return units[a].initiative > units[b].initiative;
        });
    
    int round_kills = 0;
    for (const int i : attack_resolution_order) {
        if (targets[i] != -1) {
            UnitGroup& attacker = units[i];
            UnitGroup& target = units[targets[i]];
            if (attacker.alive() && target.alive()) {
                round_kills += attacker.attack(target);
            }
        }
    }

    // The simulation can reach a state where no unit is able to damage any other
    // (eg. both immune to other's damage type).
    return round_kills > 0;
}

void apply_boost(int boost, Units& units) {
    for (auto& unit : units) {
        if (unit.army == ArmyType::IMMUNE_SYSTEM)
            unit.attack_damage += boost;
    }
}

struct RoundResult {
    ArmyType winner;
    int units_left = 0;
};

RoundResult simulation(int boost, const Units& initial_unit_state) {
    Units state = initial_unit_state;
    apply_boost(boost, state);

    while (!army_eliminated(state)) {
        bool deadlocked = !resolve_attacks(state, select_targets(state));
        if (deadlocked) {
            // cout << "Deadlock for boost=" << boost << "\n";
            return RoundResult{ArmyType::INFECTION, -1};
        }
    }

    RoundResult result;
    for (const auto& unit : state) {
        if (unit.alive()) {
            result.winner = unit.army;
            result.units_left += unit.n_units;
        }
    }
    return result;
}

int run(const string& in) {
    const Units input = parse_input(in);

    // Binary search for minimal boost value
    int search_min = 0, search_max = 10000;
    RoundResult result;
    while (search_min < search_max) {
        int boost = (search_min + search_max) / 2;
        // cout << search_min << " " << search_max << " " << boost << "\n";
        result = simulation(boost, input);
        if (result.winner == ArmyType::INFECTION)
            search_min = boost + 1;
        else
            search_max = boost;
    }

    result = simulation(search_min, input);

    return result.units_left;
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
