// https://adventofcode.com/2024/day/6

#include <bits/stdc++.h>

int N, M, answer;
std::string input;
std::vector<std::string> grid;
std::vector<std::vector<std::array<bool, 4>>> visited;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool rec(int x, int y, int dir) {
        if (x < 0 || x >= N || y < 0 || y >= M || visited[x][y][dir]) return false;

        if (grid[x][y] == '#') return true;

        visited[x][y][dir] = true;
        if (rec(x + dx[dir], y + dy[dir], dir)) {
                dir = (dir + 1) % 4;
                rec(x + dx[dir], y + dy[dir], dir);
        }
        return false;
}

void solve() {
        while (getline(std::cin, input)) grid.push_back(input);

        assert((int)grid.size() > 0);

        N = grid.size(), M = grid[0].size(), answer = 0;
        visited.resize(N, std::vector<std::array<bool, 4>>(M, std::array<bool, 4>()));

        for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                        if (grid[i][j] == '^') rec(i, j, 0);

        for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                        bool ok = false;
                        for (int k = 0; k < 4; ++k) {
                                ok |= visited[i][j][k];
                        }
                        answer += ok == true;
                }
        }
        
        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
