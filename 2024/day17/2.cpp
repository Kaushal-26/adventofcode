// https://adventofcode.com/2024/day/17

#include <bits/stdc++.h>

// Time taken calculate
struct TimeCalculate {
        std::chrono::_V2::system_clock::time_point begin;
        TimeCalculate() {
                begin = std::chrono::high_resolution_clock::now();
        }
        void end() {
                auto end = std::chrono::high_resolution_clock::now();
                auto execution_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
                std::cout << std::fixed << std::setprecision(15) << "Execution Time: " << execution_time << "\n";
        }
};

std::string input;
std::istringstream oin;

void setOin(bool isInput = true) {
        if (isInput) getline(std::cin, input);
        oin.clear(), oin.str(input);
}

void solve() {
        std::vector<long long> program;
        std::vector<long long> registers(3);

        auto literal = [&](long long operand) -> long long {
                return operand;
        };

        auto combo = [&](long long operand) -> long long {
                if (operand < 4) return literal(operand);
                if (operand == 4) return registers[0];
                if (operand == 5) return registers[1];
                if (operand == 6) return registers[2];
                assert(0);
        };

        bool kill_point_found = false;
        int instruction_pointer = 0;
        std::vector<long long> outputs;

        auto opcode = [&](long long instructions, long long operand) {
                switch (instructions) {
                        case 0:
                                operand = combo(operand);
                                assert(operand < 64);
                                registers[0] = registers[0] / pow(2, operand);
                                break;
                        case 1:
                                registers[1] ^= literal(operand);
                                break;
                        case 2:
                                registers[1] = combo(operand) % 8;
                                break;
                        case 3:
                                if (registers[0] == 0) {
                                        kill_point_found = true;
                                        return;
                                }
                                instruction_pointer = literal(operand);
                                return;
                        case 4:
                                registers[1] ^= registers[2];
                                break;
                        case 5:
                                outputs.push_back(combo(operand) % 8);
                                break;
                        case 6:
                                operand = combo(operand);
                                assert(operand < 64);
                                registers[1] = registers[0] / pow(2, operand);
                                break;
                        case 7:
                                operand = combo(operand);
                                assert(operand < 64);
                                registers[2] = registers[0] / pow(2, operand);
                                break;
                        default:
                                assert(0);
                }
                instruction_pointer += 2;
        };
        
        auto simulate = [&]() {
                instruction_pointer = 0;
                kill_point_found = false;
                outputs.clear();
                while (instruction_pointer + 1 < (int) program.size() && !kill_point_found) {
                        opcode(program[instruction_pointer], program[instruction_pointer + 1]);
                }
        };

        std::string temp;
        for (auto &R : registers) {
                setOin();
                oin >> temp >> temp;
                oin >> temp; R = stoll(temp);
        }

        getline(std::cin, input); // extra line

        setOin();
        oin >> temp >> temp;

        input = temp;
        while (input.find(',') != std::string::npos) input[input.find(',')] = ' ';

        setOin(false);
        for (long long P = 0; oin >> P; ) program.push_back(P);


        // From Errichto's stream
        // First 10 bits are important

        std::vector<long long> posibilities;
        for (int i = 0; i < 1024; ++i) posibilities.push_back(i);
        
        long long pw = 1024;
        for (int i = 0; i < (int) program.size(); ++i) {
                std::vector<long long> new_posibilities;
                for (auto &P : posibilities) {
                        registers[0] = P, registers[1] = 0, registers[2] = 0;
                        simulate();

                        if (i >= (int) outputs.size() || outputs[i] != program[i]) continue;
                        for (int j = 0; j < 8; ++j) new_posibilities.push_back(j * pw + P);
                }
                posibilities = new_posibilities;
                pw *= 8;
        }

        for (auto &P : posibilities) {
                registers[0] = P, registers[1] = 0, registers[2] = 0;
                simulate();
                if (outputs.size() != program.size()) continue;
                std::cout << P << "\n";
                return;
        }
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 0.344198605000000
        return 0;
}

// 1.77245
