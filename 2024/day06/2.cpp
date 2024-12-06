// https://adventofcode.com/2024/day/6

#include <bits/stdc++.h>

int N, M, answer, X, Y;
std::string input;
std::vector<std::string> grid;
std::vector<std::vector<std::array<bool, 4>>> visited;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool rec(int x, int y, int dir) {
        if (x < 0 || x >= N || y < 0 || y >= M) return false;

        if (visited[x][y][dir]) return true;

        if (grid[x][y] == '#') {
                int px = x - dx[dir], py = y - dy[dir];
                int ndir = (dir + 1) % 4;
                return rec(px + dx[ndir], py + dy[ndir], ndir);
        }

        visited[x][y][dir] = true;
        return rec(x + dx[dir], y + dy[dir], dir);
}

void solve() {
        while (getline(std::cin, input)) grid.push_back(input);

        assert((int)grid.size() > 0);

        N = grid.size(), M = grid[0].size(), answer = 0;
        visited.resize(N, std::vector(M, std::array<bool, 4>()));

        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (grid[i][j] == '^') {
                X = i, Y = j; break;
        }

        for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                        if (grid[i][j] == '.') {
                                grid[i][j] = '#';
                                visited.clear(); visited.resize(N, std::vector(M, std::array<bool, 4>()));
                                answer += rec(X, Y, 0) == true;
                                grid[i][j] = '.';
                        }

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
