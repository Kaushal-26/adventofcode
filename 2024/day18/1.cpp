// https://adventofcode.com/2024/day/18

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
const int ASKED = 1024;
std::vector<std::string> grid;
std::vector<std::vector<std::array<long long, 4>>> dp;

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};

void solve() {
        std::vector<std::array<long long, 2>> points;
        while (getline(std::cin, input)) {
                std::replace(input.begin(), input.end(), ',', ' ');

                setOin(false);
                int X, Y; oin >> X >> Y;
                points.push_back({Y, X});
                N = std::max(N, Y + 1);
                M = std::max(M, X + 1);
        }

        grid.resize(N, std::string(M, '.'));
        dp.resize(N, std::vector<std::array<long long, 4>>(M, {N * M, N * M, N * M, N * M}));

        for (int i = 0; i < ASKED; ++ i) {
                grid[points[i][0]][points[i][1]] = '#';
        }

        if (grid[0][0] == '#') {
                assert(false);
        }

        // Dijikstra Algorithm
        std::priority_queue<std::array<long long, 4>, std::vector<std::array<long long, 4>>, std::greater<std::array<long long, 4>>> min_heap;
        min_heap.push({0, 0, 0, 0});
        dp[0][0][0] = 0;

        while (!min_heap.empty()) {
                auto [distance, X, Y, direction] = min_heap.top(); min_heap.pop();

                if (dp[X][Y][direction] != distance) continue;

                if (X == N - 1 && Y == M - 1) {
                        std::cout << distance << "\n";
                        return;
                }

                for (int i = 0, nX, nY, new_distance; i < 4; ++ i) {
                        nX = X + dx[i], nY = Y + dy[i];
                        if (nX < 0 || nX >= N || nY < 0 || nY >= M || grid[nX][nY] == '#') continue;

                        new_distance = dp[X][Y][direction] + 1;
                        if (dp[nX][nY][i] > new_distance) {
                                dp[nX][nY][i] = new_distance;
                                min_heap.push({new_distance, nX, nY, i});
                        }
                }
        }

        assert(false);
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 1.489918375000000s
        return 0;
}

// 1.77245
