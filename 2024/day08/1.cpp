// https://adventofcode.com/2024/day/8

#include <bits/stdc++.h>


std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(), oin.str(input);
}

void solve() {
        std::vector<std::string> grid;
        
        while(getline(std::cin, input)) grid.push_back(input);

        std::map<int, std::vector<std::array<int, 2>>> antenna;

        int N = (int) grid.size(), M = (int) grid[0].size();
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (grid[i][j] != '.') {
                antenna[grid[i][j]].push_back({i, j});
        }

        std::vector<std::vector<bool>> antinodes(N, std::vector<bool>(M, false));

        auto good = [&](int x, int y) -> void {
                if (x >= 0 && x < N && y >= 0 && y < M) {
                        antinodes[x][y] = true;
                }
        };
        
        for (auto &[_, A] : antenna) {
                int K = (int) A.size();

                for (int i = 0, sx, sy, tx, ty, diffx, diffy; i < K; ++i) for (int j = i + 1; j < K; ++j) {
                        sx = A[i][0], sy = A[i][1], tx = A[j][0], ty = A[j][1];
                        
                        diffx = tx - sx, diffy = ty - sy;

                        good(sx - diffx, sy - diffy);
                        good(tx + diffx, ty + diffy);
                }
        }

        int answer = 0;
        for (const auto &x : antinodes) for (const auto &y : x) if (y) ++answer;

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
