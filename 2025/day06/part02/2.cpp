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

        std::vector<std::string> problems;
        std::vector<char> operations;
        for (; std::getline(std::cin, input);) {
                if (input.find('+') == std::string::npos || input.find('*') == std::string::npos) {
                        setOin(false);
                        problems.push_back(input);
                } else {
                        setOin(false);

                        for (char operation; oin >> operation;) {
                                operations.push_back(operation);
                        }
                }
        }

        for (int i = 0; i < (int) problems.size(); ++i) assert(problems[i].size() == problems[0].size());

        int worksheet_length = problems[0].size();

        int64_t grand_total = 0;
        std::vector<int64_t> current_problems;

        auto process = [&]() {
                assert(operations.size() > 0);

                int64_t total = (operations.back() == '*' ? 1 : 0);
                for (auto &number : current_problems) if (operations.back() == '*') {
                        total *= number;
                } else {
                        total += number;
                }
                grand_total += total;

                operations.pop_back(), current_problems.clear();
        };

        for (int j = worksheet_length - 1; j >= 0; --j) {
                int64_t value = 0;
                int cnt = 0;
                for (int i = 0; i < (int) problems.size(); ++i) {
                        if (problems[i][j] >= '0' && problems[i][j] <= '9') {
                                value *= 10;
                                value += problems[i][j] - '0';
                        } else {
                                ++ cnt;
                        }
                }

                if (cnt == (int) problems.size()) {
                        process();
                } else {
                        current_problems.push_back(value);
                }
        }

        process();

        std::cout << grand_total << "\n";
        return 0;
}
