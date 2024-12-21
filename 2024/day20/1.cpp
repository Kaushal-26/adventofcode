// https://adventofcode.com/2024/day/20

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


int N = 0, M = 0;
const int INF = (int) 1e9;
std::vector<std::string> grid;
std::array<int, 2> S, E;
std::vector<std::vector<std::array<int, 2>>> distance;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int t) {
        std::queue<std::array<int, 3>> Q;
        Q.push({0, S[0], S[1]}), distance[S[0]][S[1]][t] = 0;

        while (!Q.empty()) {
                auto [d, x, y] = Q.front(); Q.pop();

                if (x == E[0] && y == E[1]) continue;

                for (int i = 0; i < 4; ++i) {
                        int nx = x + dx[i], ny = y + dy[i];
                        if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

                        if (grid[nx][ny] != '#' && distance[nx][ny][t] > d + 1) {
                                distance[nx][ny][t] = d + 1;
                                Q.push({d + 1, nx, ny});
                        }
                }
        }
}

void solve() {
        while (getline(std::cin, input)) {
                ++ N;
                grid.push_back(input);
                M = std::max(M, (int) input.size());
        }

        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 'S') S = {i, j};
                if (grid[i][j] == 'E') E = {i, j};
        }

        distance.resize(N, std::vector<std::array<int, 2>>(M, {INF, INF}));

        bfs(0);
        std::swap(S, E);
        bfs(1);
        std::swap(S, E);

        int without_cheats = distance[E[0]][E[1]][0];
        std::vector<int> with_cheats;
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (grid[i][j] == '#') {
                for (int p = 0; p < 4; ++p) {
                        int nx = i + dx[p], ny = j + dy[p];
                        if (nx < 0 || ny < 0 || nx >= N || ny >= M || grid[nx][ny] == '#') continue;

                        for (int q = 0; q < 4; ++q) if (q < p) {
                                int nnx = i + dx[q], nny = j + dy[q];
                                if (nnx < 0 || nny < 0 || nnx >= N || nny >= M || grid[nnx][nny] == '#') continue;

                                for (int t = 0, answer = INF; t < 2; ++t) {
                                        if (distance[nx][ny][t] == INF || distance[nnx][nny][!t] == INF) continue;
                                        answer = distance[nx][ny][t] + distance[nnx][nny][!t] + 2;
                                        if (answer < without_cheats) with_cheats.push_back(answer);
                                }
                        }
                }
        }

        std::sort(with_cheats.begin(), with_cheats.end());

        std::vector<std::array<int, 2>> freq;
        for (const auto& x : with_cheats) if (freq.empty() || freq.back()[0] != x) {
                freq.push_back({x, 1});
        } else {
                freq.back()[1]++;
        }

        for (int i = 1; i < (int) freq.size(); ++i) {
                if (without_cheats - freq[i][0] >= 100) {
                        freq[i][1] += freq[i - 1][1];
                } else {
                        freq[i][1] = freq[i - 1][1];
                }
        }

        if (without_cheats - freq[0][0] < 100) {
                std::cout << "0\n";
                return;
        }

        std::cout << freq.back()[1] << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 0.050830700000000s
        return 0;
}

// 1.77245
