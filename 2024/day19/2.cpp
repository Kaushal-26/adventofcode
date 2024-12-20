// https://adventofcode.com/2024/day/19

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

// Set input or output using stringstream
void setOin(bool isInput = true) {
        if (isInput) getline(std::cin, input);
        oin.clear(), oin.str(input);
}

// Time taken calculate
struct TimeCalculate {
        std::chrono::_V2::system_clock::time_point begin;
        TimeCalculate() {
                begin = std::chrono::high_resolution_clock::now();
        }
        void end() {
                auto end = std::chrono::high_resolution_clock::now();
                auto execution_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
                std::cout << std::fixed << std::setprecision(15) << "Execution Time: " << execution_time << "s\n";
        }
};



std::vector<std::string> towels;
std::vector<std::string> designs;

void solve() {
        getline(std::cin, input);
        while (input.find(",") != std::string::npos) {
                std::replace(input.begin(), input.end(), ',', ' ');
        }
        setOin(false);
        while (oin >> input) {
                towels.push_back(input);
        }

        getline(std::cin, input); // blank line
        while (getline(std::cin, input)) {
                designs.push_back(input);
        }

        std::vector<long long> dp;
        auto rec = [&](auto &&self, int id, std::string &design) -> long long {
                if (id == (int) design.size()) {
                        return 1;
                }

                if (dp[id] != -1) {
                        return dp[id];
                }

                long long ways = 0;
                for (int i = 0; i < (int) towels.size(); ++ i) {
                        if (id + (int) towels[i].size() > (int) design.size() 
                        || towels[i] != design.substr(id, towels[i].size())) {
                                continue;
                        }

                        ways += self(self, id + towels[i].size(), design);
                }

                return dp[id] = ways;
        };

        long long total_degins_patterns = 0;
        for (auto &design : designs) {
                dp.clear(), dp.resize(design.size(), -1);
                total_degins_patterns += rec(rec, 0, design);
        }

        std::cout << total_degins_patterns << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 1.593300503000000s
        return 0;
}

// 1.77245
