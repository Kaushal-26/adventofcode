// https://adventofcode.com/2025/day/7

#include <bits/stdc++.h>

std::string input;

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::vector<std::string> grid;
        int N = 0, M = 0;
        while (std::cin >> input) {
                grid.push_back(input);
                ++ N;
                M = (int)input.size();
        }

        std::vector dp(N, std::vector<long long>(M, -1));
        auto dfs = [&](auto&& self, int x, int y) -> long long {
                if (x == N) return 1LL;
                if (y >= M || x < 0 || y < 0) return 0LL;

                if (dp[x][y] != -1) return dp[x][y];

                long long ret = 0;
                if (grid[x][y] == '^') {
                        ret += self(self, x, y - 1);
                        ret += self(self, x, y + 1);
                } else {
                        ret = self(self, x + 1, y);
                }

                // std::cout << x << " " << y << " " << ret << "\n";
                return dp[x][y] = ret;
        };

        int Sx = 0, Sy = 0;
        for (int i = 0; i < M; ++i) {
                if (grid[0][i] == 'S') {
                        Sx = 0, Sy = i;
                        break;
                }
        }

        std::cout << dfs(dfs, Sx, Sy) << "\n";
        return 0;
}
