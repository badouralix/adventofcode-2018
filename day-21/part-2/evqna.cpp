#include <array>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

const int N_REG = 6;
typedef array<int, N_REG> Regs;

// The register containing the value 'c'
// that is produced by the main program loop
const int MAIN_VAR_REG_ID = 3;
// The instruction pointer value when executing the program exit condition
const int EXIT_CONDITION_IP = 28;

enum OpCode {
    addr, addi,
    mulr, muli,
    banr, bani,
    borr, bori,
    setr, seti,
    gtir, gtri, gtrr,
    eqir, eqri, eqrr,
};

unordered_map<string, OpCode> OP_CODES = {
    {"addr", addr}, {"addi", addi},
    {"mulr", mulr}, {"muli", muli},
    {"banr", banr}, {"bani", bani},
    {"borr", borr}, {"bori", bori},
    {"setr", setr}, {"seti", seti},
    {"gtir", gtir}, {"gtri", gtri}, {"gtrr", gtrr},
    {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr},
};

struct Instruction {
    OpCode op;
    int a, b, c;
};

int runOp(const Regs& registers, Instruction x) {
    switch (x.op) {
        case addr:  return registers[x.a] + registers[x.b];
        case addi:  return registers[x.a] + x.b;
        case mulr:  return registers[x.a] * registers[x.b];
        case muli:  return registers[x.a] * x.b;
        case banr:  return registers[x.a] & registers[x.b];
        case bani:  return registers[x.a] & x.b;
        case borr:  return registers[x.a] | registers[x.b];
        case bori:  return registers[x.a] | x.b;
        case setr:  return registers[x.a];
        case seti:  return x.a;
        case gtir:  return x.a > registers[x.b];
        case gtri:  return registers[x.a] > x.b;
        case gtrr:  return registers[x.a] > registers[x.b];
        case eqir:  return x.a == registers[x.b];
        case eqri:  return registers[x.a] == x.b;
        case eqrr:  return registers[x.a] == registers[x.b];
        default: return 0;
    }
}

struct Program {
    vector<Instruction> instructions;
    Regs registers = {{0}};
    int ip = 0;
    int ip_register = 0;
    uint64_t num_cycles = 0;

    /*
     * The main program loop is entirely parametrized by the value of
     * register $3 on entry ('c'), which is also the output that is
     * compared with the user value 'x' as in:
     * 
     *      if c == x:
     *          exit()
     * 
     * Since 'x' is never used anywhere else, the solutions are:
     * - lower bound is the resulting 'c' value after one iteration
     *   of the outer loop
     * - upper bound is the last unique 'c' value produced by the loop
     *   before a duplicate is seen.
     */
    set<int> seen;
    int last_seen = 0;
    bool terminate = false;

    bool exit() const {
        return ip >= instructions.size() || terminate;
    }

    void runNextInstruction() {
        registers[ip_register] = ip;
        Instruction& i = instructions[ip];
        registers[i.c] = runOp(registers, i);
        ip = registers[ip_register];
        ip++;
        num_cycles++;
    }

    void hack() {
        if (ip == EXIT_CONDITION_IP) {
            int c = registers[MAIN_VAR_REG_ID];
            if (seen.count(c) > 0) {
                cout << "duplicate c=" << c << " (" << num_cycles << ")\n";
                cout << "total: " << seen.size() << "\n";
                registers[0] = last_seen;
                terminate = true;
            } else {
                seen.insert(c);
                last_seen = c;
            }
        }
    }
};

Program readProgram(const string& in) {
    istringstream iss(in);
    Program p;
    string line;

    getline(iss, line);
    sscanf(line.c_str(), "#ip %d", &p.ip_register);

    while (getline(iss, line)) {
        Instruction i;
        i.op = OP_CODES[line.substr(0, 4)];
        sscanf(line.c_str(), "%*s %d %d %d",
            &i.a, &i.b, &i.c);
        p.instructions.push_back(i);
    }
    return p;
}

int run(const string& in) {
    auto program = readProgram(in);

    while (!program.exit()) {
        program.runNextInstruction();
        program.hack();
    }

    // The solution was written to register 0
    return program.registers[0];
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
