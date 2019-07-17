#include <array>
#include <ctime>
#include <iostream>
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

vector<Sample> readSamples(const string& in) {
    istringstream iss(in);
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

int run(const string& in) {
    auto samples = readSamples(in);

    int nsamples = 0;
    for (const auto& sample : samples) {
        int matchingOps = 0;
        for (int op = 0; op < 16; op++) {
            Instruction ins = sample.ins;
            ins.op = (OpCode)op;
            int C = runOp(sample.before, ins);

            if (C == sample.after[sample.ins.c])
                matchingOps++;
        }

        if (matchingOps >= 3)
            nsamples++;
    }

    return nsamples;
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
