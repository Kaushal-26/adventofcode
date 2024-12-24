#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void setOin() {
        oin.clear(), oin.str(input);
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        std::map<std::string, int, std::greater<std::string>> wires;

        std::map<std::string, std::array<std::string, 3>> wire_logic;
        std::map<std::string, std::vector<std::string>> wires_map;
        std::map<std::string, int> in_degree;
        while (getline(std::cin, input)) {
                if (input == "") continue;
                if (std::find(input.begin(), input.end(), ':') != input.end()) {
                        std::replace(input.begin(), input.end(), ':', ' ');
                        setOin();

                        std::string wire, value; oin >> wire >> value;
                        wires[wire] = std::stoi(value);
                } else {
                        std::replace(input.begin(), input.end(), '-', ' ');
                        std::replace(input.begin(), input.end(), '>', ' ');
                        setOin();

                        std::string wire1, logic, wire2, result_wire; oin >> wire1 >> logic >> wire2 >> result_wire;
                        wire_logic[result_wire] = {wire1, wire2, logic};
                        wires_map[wire1].push_back(result_wire);
                        wires_map[wire2].push_back(result_wire);
                        in_degree[result_wire] = 2;
                }
        }

        std::queue<std::string> Q;
        for (auto &[wire, value] : wires) if (wires.find(wire) != wires.end()) {
                Q.push(wire);
        }

        while (!Q.empty()) {
                std::string wire = Q.front(); Q.pop();

                for (auto &next_wire : wires_map[wire]) {
                        in_degree[next_wire]--;
                        if (in_degree[next_wire] == 0) {
                                std::string wire1 = wire_logic[next_wire][0], wire2 = wire_logic[next_wire][1], logic = wire_logic[next_wire][2];
                                wires[next_wire] = logic == "AND" ? wires[wire1] & wires[wire2] : logic == "OR" ? wires[wire1] | wires[wire2] : logic == "XOR" ? wires[wire1] ^ wires[wire2] : -1;
                                assert(wires[next_wire] != -1);

                                Q.push(next_wire);
                        }
                }
        }

        long long answer = 0;
        for (auto &[wire, value] : wires) {
                std::cout << wire << " " << value << '\n';
                if (wire[0] == 'z') {
                        answer = answer * 2 + value;
                }
        }
        std::cout << answer << '\n';
        return 0;
}