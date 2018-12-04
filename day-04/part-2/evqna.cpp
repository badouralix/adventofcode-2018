#include <algorithm>
#include <cstdio>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Record {
    int day, month, year;
    int hour, min;
    std::string msg;

    bool operator<(const Record& b) const {
        const Record& a = *this;
        if (a.year < b.year)
            return true;
        if (a.year == b.year && a.month < b.month)
            return true;
        if (a.year == b.year && a.month == b.month && a.day < b.day)
            return true;
        if (a.year == b.year && a.month == b.month && a.day == b.day && a.hour < b.hour)
            return true;
        if (a.year == b.year && a.month == b.month && a.day == b.day && a.hour == b.hour && a.min < b.min)
            return true;
        
        return false;
    }
};

std::vector<Record> parse_input(const std::string& in) {
    std::istringstream iss(in);
    std::vector<Record> vec;

    for (std::string line; std::getline(iss, line); ) {
        Record r;
        sscanf(line.c_str(), "[ %d - %d - %d %d : %d ]", &r.year, &r.month, &r.day, &r.hour, &r.min);
        r.msg = line.substr(19);
        vec.push_back(r);
    }

    return vec;
}

struct SleepPattern {
    int total_duration = 0;
    int freq_by_min[60] = {0};
};

std::map<int, SleepPattern> compute_sleep_patterns(const std::vector<Record>& sorted_input) {
    std::map<int, SleepPattern> guard_sleep_patterns;
    
    int current_guard_id = -1;
    int sleep_start = 0;

    for (const auto& r : sorted_input) {
        // Read first word
        size_t pos = r.msg.find(' ');
        std::string key = r.msg.substr(0, pos);
        if (key == "Guard") {
            current_guard_id = std::stoi(r.msg.substr(pos + 2));    // Ignore '#'
        }
        else if (key == "falls") {
            sleep_start = r.min;
        }
        else if (key == "wakes") {
            auto& data = guard_sleep_patterns[current_guard_id];
            data.total_duration += r.min - sleep_start;
            for (int i = sleep_start; i < r.min; i++)
                data.freq_by_min[i]++;
        }
    }

    return guard_sleep_patterns;
}

int solve(std::vector<Record>& input) {
    std::sort(input.begin(), input.end());

    auto guard_sleep_data = compute_sleep_patterns(input);

    // Find most slept minute across all guards
    int best_min = 0, best_guard = 0, cur_max = 0;
    for (const auto& x : guard_sleep_data) {
        for (int i = 0; i < 60; i++) {
            if (x.second.freq_by_min[i] > cur_max) {
                cur_max = x.second.freq_by_min[i];
                best_min = i;
                best_guard = x.first;
            }
        }
    }

    return best_guard * best_min;
}

int main(int argc, char *argv[]) {
    auto input = parse_input(argv[1]);
    
    printf("%d\n", solve(input));

    return 0;
}
