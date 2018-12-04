#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#define ASLEEP 's'
#define AWAKE 'w'

using namespace std;

typedef struct Log {
    char type;
    int y, m, d, hh, mm;
    int id;
    bool operator<(Log b) const {
        return (y < b.y) ||
               (y == b.y && m < b.m) ||
               (y == b.y && m == b.m && d < b.d) ||
               (y == b.y && m == b.m && d == b.d && hh < b.hh) ||
               (y == b.y && m == b.m && d == b.d && hh == b.hh && mm < b.mm);
    }
} Log;

typedef struct Guard {
    char state;
    int sleeping_since;
    int counts[60];
} Guard;

Guard* newGuard() {
    Guard *guard = new Guard;

    guard->state = AWAKE;
    guard->sleeping_since = -1;
    for (int i = 0; i < 60; i++) guard->counts[i] = 0;

    return guard;
}

int run(string s) {
    istringstream stream(s);
    vector<Log> logs;
    char *cline;
    string line;

    while (getline(stream, line)) {
        cline = (char*)line.c_str();
        Log log;
        sscanf(cline, "[%d-%d-%d", &log.y, &log.m, &log.d);
        sscanf(cline+12, "%d:%d", &log.hh, &log.mm);
        log.type = cline[19];
        if (log.type == 'G') sscanf(cline+25, "#%d", &log.id);
        logs.push_back(log);
    }

    sort(logs.begin(), logs.end());

    unordered_map<int, Guard*> guards;
    int max = 0, max_id = 0, minute = 0, id = 0, sleep = 0;

    for (const Log &log: logs) {
        switch (log.type) {
        case 'G':
            id = log.id;
            if (guards.find(id) == guards.end())
                guards[id] = newGuard();
            guards[id]->state = AWAKE;
            break;
        case 'f':
            if (guards[id]->state == ASLEEP) break;
            guards[id]->sleeping_since = log.mm;
            guards[id]->state = ASLEEP;
            break;
        case 'w':
            if (guards[id]->state == AWAKE) break;
            sleep = log.mm - guards[id]->sleeping_since;
            for (int i = guards[id]->sleeping_since; i < log.mm; i++)
                guards[id]->counts[i]++;
            guards[id]->state = AWAKE;
            guards[id]->sleeping_since = -1;
            break;
        }
    }

    for (const pair<int,Guard*> &it: guards) {
        Guard *guard = it.second;
        int max_minute = 0;
        for (int i = 0; i < 60; i++) {
           if (guard->counts[i] > guard->counts[max_minute])
                max_minute = i;
        }
        if (guard->counts[max_minute] > max) {
            max = guard->counts[max_minute];
            minute = max_minute;
            max_id = it.first;
        }
    }
    
    return minute*max_id; 
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Missing one argument" << endl;
        exit(1);
    }
    cout << run(string(argv[1])) << "\n";
    return 0;
}
