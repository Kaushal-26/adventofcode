// https://adventofcode.com/2025/day/6

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

// Set input or output using stringstream
void setOin(bool isInput = true) {
        if (isInput) getline(std::cin, input);
        oin.clear(), oin.str(input);
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::vector<std::vector<int64_t>> problems;
        std::vector<char> operations;
        for (; std::getline(std::cin, input);) {
                if (input.find('+') == std::string::npos || input.find('*') == std::string::npos) {
                        setOin(false);

                        std::vector<int64_t> problem;
                        for (int64_t numbers; oin >> numbers;) {
                                problem.push_back(numbers);
                        }
                        problems.push_back(problem);
                } else {
                        setOin(false);

                        for (char operation; oin >> operation;) {
                                operations.push_back(operation);
                        }
                }
        }

        assert(operations.size() == problems[0].size());
        for (int i = 0; i < (int) problems.size(); ++i) assert(problems[i].size() == problems[0].size());

        int worksheet_length = operations.size();

        int64_t grand_total = 0;
        for (int j = 0; j < worksheet_length; ++j) {
                int64_t total = (operations[j] == '*' ? 1 : 0);
                for (int i = 0; i < (int) problems.size(); ++i) {
                        if (operations[j] == '*') {
                                total *= problems[i][j];
                        } else {
                                total += problems[i][j];
                        }
                }
                grand_total += total;
        }

        std::cout << grand_total << "\n";
        return 0;
}
