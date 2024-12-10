// https://adventofcode.com/2024/day/10

#include <bits/stdc++.h>

int rows, columns;
std::string input;
std::vector<std::string> grid;
std::vector<std::vector<int>> dp;

bool in(int R, int C) {
        return !(R < 0 || R >= rows || C < 0 || C >= columns);
}

int dfs(int R, int C) {
        if (dp[R][C] != -1) return dp[R][C];

        if (grid[R][C] == '9') return dp[R][C] = 1;

        int ret = 0;
        for (int dx = -1; dx <= 1; ++ dx)
                for (int dy = -1; dy <= 1; ++ dy)
                        if (abs(dx) + abs(dy) == 1 && in(R + dx, C + dy) && grid[R + dx][C + dy] == grid[R][C] + 1)
                                ret += dfs(R + dx, C + dy);

        return dp[R][C] = ret;
}

void solve() {
        while (getline(std::cin, input)) grid.push_back(input), columns = (int) input.size();

        rows = (int) grid.size();
        dp.resize(rows, std::vector<int>(columns, -1));

        int trailheads_rating = 0;
        for (int i = 0; i < rows; ++ i)
                for (int j = 0; j < columns; ++ j)
                        if (grid[i][j] == '0')
                                trailheads_rating += dfs(i, j);

        std::cout << trailheads_rating << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
