//https://adventofcode.com/2024/day/14

#include <bits/stdc++.h>


std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(); oin.str(input);
}

void fix() {
        input.erase(input.find("p="), 2); input.erase(input.find("v="), 2);
        while (input.find(",") != std::string::npos) {
                input[input.find(",")] = ' ';
        }
}

void solve() {
        std::queue<std::array<int, 4>> Q, TQ;

        int N = 0, M = 0;
        while (getline(std::cin, input)) {
                fix(); set_oin();
                int X, Y, Vx, Vy; oin >> Y >> X >> Vy >> Vx; Q.push({X, Y, Vx, Vy});
                N = std::max(N, X + 1); M = std::max(M, Y + 1);
        }

        for (int repetition = 0; repetition < 100; ++repetition) {
                while (!TQ.empty()) TQ.pop();
                while (!Q.empty()) {
                        auto [X, Y, Vx, Vy] = Q.front(); Q.pop();
                        X += Vx; X += N; X %= N;
                        Y += Vy; Y += M; Y %= M;
                        TQ.push({X, Y, Vx, Vy});
                }
                std::swap(TQ, Q);
        }

        std::vector<std::vector<int>> x(N, std::vector<int>(M, 0));

        while (!Q.empty()) {
                auto [X, Y, Vx, Vy] = Q.front(); Q.pop();
                x[X][Y] += 1;
        }

        std::array<int, 4> quadrants;
        for (int i = 0; i < N; ++i) {
                for (int j = 0, t = 0; j < M; ++j) if (x[i][j] && !(i == N / 2 || j == M / 2)) {
                        t = 0;
                        if (i < N / 2) ++ t;
                        if (j < M / 2) t += 2;
                        quadrants[t] += x[i][j];
                }
        }

        std::cout << (long long)quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3] << '\n';
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
