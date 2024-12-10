// https://adventofcode.com/2024/day/10

#include <bits/stdc++.h>

int rows, columns;
std::string input;
std::vector<std::string> grid;

bool in(int R, int C) {
        return !(R < 0 || R >= rows || C < 0 || C >= columns);
}

void solve() {
        while (getline(std::cin, input)) grid.push_back(input), columns = (int) input.size();

        rows = (int) grid.size();

        int trailheads_score = 0;
        for (int i = 0; i < rows; ++ i)
                for (int j = 0; j < columns; ++ j)
                        if (grid[i][j] == '0') {
                                std::queue<std::array<int, 2>> Q({{i, j}});
                                std::set<std::array<int, 2>> seen;
                                while (!Q.empty()) {
                                        auto [R, C] = Q.front(); Q.pop();
                                        if (grid[R][C] == '9') {
                                                seen.insert({R, C});
                                                continue;
                                        }
                                        for (int dx = -1; dx <= 1; ++ dx)
                                                for (int dy = -1; dy <= 1; ++ dy)
                                                        if (abs(dx) + abs(dy) == 1)
                                                                if (in(R + dx, C + dy) && grid[R + dx][C + dy] == grid[R][C] + 1)
                                                                        Q.push({R + dx, C + dy});
                                }
                                trailheads_score += (int) seen.size();
                        }

        std::cout << trailheads_score << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
