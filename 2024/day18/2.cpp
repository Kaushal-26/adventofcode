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
std::vector<std::string> grid;
std::vector<std::vector<std::array<long long, 4>>> dp;
std::vector<std::array<long long, 2>> points;

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};


bool possible(int ASKED) {
        grid.clear(), grid.resize(N, std::string(M, '.'));
        dp.clear(), dp.resize(N, std::vector<std::array<long long, 4>>(M, {N * M, N * M, N * M, N * M}));

        for (int i = 0; i < ASKED; ++ i) {
                grid[points[i][0]][points[i][1]] = '#';
        }

        if (grid[0][0] == '#') {
                return false;
        }

        // Dijikstra Algorithm
        std::priority_queue<std::array<long long, 4>, std::vector<std::array<long long, 4>>, std::greater<std::array<long long, 4>>> min_heap;
        min_heap.push({0, 0, 0, 0});
        dp[0][0][0] = 0;

        while (!min_heap.empty()) {
                auto [distance, X, Y, direction] = min_heap.top(); min_heap.pop();

                if (dp[X][Y][direction] != distance) continue;

                if (X == N - 1 && Y == M - 1) {
                        return true;
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

        return false;
}

void solve() {
        while (getline(std::cin, input)) {
                std::replace(input.begin(), input.end(), ',', ' ');

                setOin(false);
                int X, Y; oin >> X >> Y;
                points.push_back({Y, X});
                N = std::max(N, Y + 1);
                M = std::max(M, X + 1);
        }

        int L = 0, R = (int) points.size() - 1, answer = R;
        while (L <= R) {
                int mid = (L + R) >> 1;

                if (!possible(mid + 1)) {
                        answer = std::min(answer, mid);
                        R = mid - 1;
                } else {
                        L = mid + 1;
                }
        }

        std::cout << points[answer][1] << "," << points[answer][0] << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        TimeCalculate timer;
        solve();
        timer.end(); // Execution Time: 0.612714106000000s
        return 0;
}

// 1.77245
