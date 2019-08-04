#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef array<int, 4> Regs;

enum OpCode {
    addr, addi,
    mulr, muli,
    banr, bani,
    borr, bori,
    setr, seti,
    gtir, gtri, gtrr,
    eqir, eqri, eqrr,
};

struct Instruction {
    OpCode op;
    int a, b, c;
};

struct Sample {
    const Regs before, after;
    Instruction ins;
};

vector<Sample> readSamples(istringstream& iss) {
    vector<Sample> vec;

    while (iss.peek() == 'B') {
        string line;
        Regs before, after;
        Instruction i;
        
        getline(iss, line);
        sscanf(line.c_str(), "Before: [%d, %d, %d, %d]",
            &before[0], &before[1], &before[2], &before[3]);
        
        getline(iss, line);
        sscanf(line.c_str(), "%d %d %d %d",
            (int*)&i.op, &i.a, &i.b, &i.c);
        
        getline(iss, line);
        sscanf(line.c_str(), "After: [%d, %d, %d, %d]",
            &after[0], &after[1], &after[2], &after[3]);
        
        getline(iss, line);
        vec.push_back({before, after, i});
    }

    return vec;
}

vector<Instruction> readProgram(istringstream& iss) {
    vector<Instruction> vec;
    for (string line; getline(iss, line); ) {
        Instruction i;
        sscanf(line.c_str(), "%d %d %d %d",
            (int*)&i.op, &i.a, &i.b, &i.c);
        vec.push_back(i);
    }
    return vec;
}

int runOp(const Regs& registers, Instruction x) {
    int rega = registers[x.a], regb = registers[x.b];
    switch (x.op) {
        case addr:  return rega + regb;
        case addi:  return rega + x.b;
        case mulr:  return rega * regb;
        case muli:  return rega * x.b;
        case banr:  return rega & regb;
        case bani:  return rega & x.b;
        case borr:  return rega | regb;
        case bori:  return rega | x.b;
        case setr:  return rega;
        case seti:  return x.a;
        case gtir:  return x.a > regb;
        case gtri:  return rega > x.b;
        case gtrr:  return rega > regb;
        case eqir:  return x.a == regb;
        case eqri:  return rega == x.b;
        case eqrr:  return rega == regb;
        default: return 0;
    }
}

vector<int> translateOpCodes(const vector<Sample>& samples) {
    vector<set<int>> possibleCodes(16);
    vector<int> translatedCodes(16);

    for (const auto& sample : samples) {
        Instruction ins = sample.ins;
        int sampledOp = ins.op;
        
        set<int> matchingOps;
        for (int op = 0; op < 16; op++) {
            ins.op = (OpCode)op;
            if (runOp(sample.before, ins) == sample.after[ins.c])
                matchingOps.insert(op);
        }

        if (possibleCodes[sampledOp].empty())
            possibleCodes[sampledOp] = matchingOps;
        else {
            // Vomi
            set<int> intersection;
            set<int>& a = possibleCodes[sampledOp];
            set_intersection(a.begin(), a.end(), matchingOps.begin(), matchingOps.end(),
                inserter(intersection, intersection.begin()));
            possibleCodes[sampledOp] = intersection;

            if (intersection.size() == 1) {
                // Mark matching op as translation for sampled op
                // and remove it from other tables
                int code = *possibleCodes[sampledOp].begin();
                translatedCodes[sampledOp] = code;

                for (int i = 0; i < 16; i++) {
                    if (i != sampledOp)
                        possibleCodes[i].erase(code);
                }
            }
        }
    }

    return translatedCodes;
}

int run(const string& in) {
    istringstream iss(in);
    auto samples = readSamples(iss);
    iss.ignore(2);  // Skip 2 blank lines
    auto program = readProgram(iss);

    auto codeTranslations = translateOpCodes(samples);

    // for (int i = 0; i < codeTranslations.size(); i++) {
    //     cout << i << " -> " << codeTranslations[i] << "\n";
    // }

    Regs registers = {0};
    for (auto& ins : program) {
        ins.op = (OpCode)codeTranslations[(int)ins.op];
        registers[ins.c] = runOp(registers, ins);
    }

    return registers[0];
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
