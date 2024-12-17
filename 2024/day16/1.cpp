// https://adventofcode.com/2024/day/16

#include <bits/stdc++.h>

std::string input;

const long long MAX = 1e18;
int N = 0, M = 0;
std::array<long long, 2> S, E;
std::vector<std::string> grid;
std::vector<std::vector<std::array<long long, 4>>> dp;

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};


// Time taken calculate
struct TimeCalculate {
        std::chrono::_V2::system_clock::time_point begin;
        TimeCalculate() {
                begin = std::chrono::high_resolution_clock::now();
        }
        void end() {
                auto end = std::chrono::high_resolution_clock::now();
                auto execution_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
                std::cout << std::fixed << std::setprecision(15) << "Execution Time: " << execution_time << "\n";
        }
};


void solve() {
        while (getline(std::cin, input)) {
                ++ N;
                M = std::max(M, (int) input.size());
                grid.push_back(input);
        }

        dp.resize(N, std::vector<std::array<long long, 4>>(M, {MAX, MAX, MAX, MAX}));

        // Dijikstra Algorithm
        std::priority_queue<std::array<long long, 4>, std::vector<std::array<long long, 4>>, std::greater<std::array<long long, 4>>> min_heap;
        for (int i = 0; i < N; ++ i) for (int j = 0; j < M; ++ j)
                if (grid[i][j] == 'S') S = {i, j}, dp[i][j][0] = 0, min_heap.push({0, i, j, 0});

        while (!min_heap.empty()) {
                auto [distance, X, Y, direction] = min_heap.top(); min_heap.pop();

                if (dp[X][Y][direction] != distance) continue;

                if (grid[X][Y] == 'E') E = {X, Y};

                for (int i = 0, nX, nY, new_distance; i < 4; ++ i) {
                        nX = X + dx[i], nY = Y + dy[i];
                        if (nX < 0 || nX >= N || nY < 0 || nY >= M || grid[nX][nY] == '#') continue;

                        new_distance = dp[X][Y][direction] + 1 + (i != direction) * 1000;
                        if (dp[nX][nY][i] > new_distance) {
                                dp[nX][nY][i] = new_distance;
                                min_heap.push({new_distance, nX, nY, i});
                        }
                }
        }

        long long print = MAX;
        for (int i = 0; i < 4; ++ i) print = std::min(print, dp[E[0]][E[1]][i]);

        std::cout << print << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 1.541041232000000s
        return 0;
}

// 1.77245
