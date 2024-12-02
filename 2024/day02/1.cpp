// https://adventofcode.com/2024/day/2

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void solve() {
        int safe_reports = 0;
        for (; getline(std::cin, input);) {
                oin.clear(); oin.str(input);

                std::vector<int> V;
                for (int inp = 0; oin >> inp;) {
                        V.push_back(inp);
                }

                bool safe = true;

                bool increasing = false, decreasing = false;
                for (int i = 1; i < (int)V.size() && safe; ++i) {
                        if (V[i] > V[i - 1]) {
                                if (decreasing) {
                                        safe = false;
                                }
                                increasing = true;
                        } else if (V[i] < V[i - 1]) {
                                if (increasing) {
                                        safe = false;
                                }
                                decreasing = true;
                        }
                        
                        safe &= std::abs(V[i] - V[i - 1]) >= 1 && std::abs(V[i] - V[i - 1]) <= 3;
                }

                safe_reports += safe == true;
        }

        std::cout << safe_reports << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
