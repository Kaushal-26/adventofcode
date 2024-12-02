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

                int N = (int)V.size();
                auto T = V;

                if (N <= 2) {
                        if (N == 1) ++ safe_reports;
                        else if(N == 2) safe_reports += std::abs(V[0] - V[1]) >= 1 && std::abs(V[0] - V[1]) <= 3;
                        continue;
                }

                bool increasing = false, decreasing = false;
                auto perform = [&]() {
                        bool safe = true;
                        int break_point = -1;

                        for (int i = 1; i < (int)V.size() && safe; ++i) {
                                if (V[i] > V[i - 1]) {
                                        safe &= !decreasing;
                                } else if (V[i] < V[i - 1]) {
                                        safe &= !increasing;
                                }

                                safe &= std::abs(V[i] - V[i - 1]) >= 1 && std::abs(V[i] - V[i - 1]) <= 3;
                                if (!safe) break_point = i;
                        }

                        return break_point;
                };

                if (V[0] == V[N - 1]) {
                        V.erase(V.begin());
                        increasing = V[0] < V[N - 2]; decreasing = !increasing;
                        if (perform() == -1) {
                                safe_reports += 1;
                        } else {
                                V = T;
                                V.erase(V.begin() + N - 1);
                                increasing = V[0] < V[N - 2]; decreasing =!increasing;
                                if (perform() == -1) {
                                        safe_reports += 1;
                                }
                        }
                        continue;
                }

                increasing = V[0] < V[N - 1], decreasing = !increasing;
                int break_point = perform();
                if (break_point == -1) {
                        safe_reports += 1;
                } else {
                        V.erase(V.begin() + break_point);
                        increasing = V[0] < V[N - 2]; decreasing = !increasing;
                        if (perform() == -1) {
                                safe_reports += 1;
                        } else {
                                int new_break_point = 0;
                                if (break_point - 1 >= 0) {
                                        V = T;
                                        V.erase(V.begin() + break_point - 1);
                                        increasing = V[0] < V[N - 2]; decreasing = !increasing;
                                        new_break_point = perform();
                                        if (new_break_point == -1) {
                                                safe_reports += 1;
                                        }
                                }
                                if (new_break_point == 0 &&  break_point + 1 < N) {
                                        V = T;
                                        V.erase(V.begin() + break_point + 1);
                                        increasing = V[0] < V[N - 2]; decreasing = !increasing;
                                        new_break_point = perform();
                                        if (new_break_point == -1) {
                                                safe_reports += 1;
                                        }
                                }
                        }
                }

        }

        std::cout << safe_reports << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
