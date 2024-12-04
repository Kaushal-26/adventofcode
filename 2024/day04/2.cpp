// https://adventofcode.com/2024/day/4

#include <bits/stdc++.h>

std::string input;

// First 4 side adjacent, Second 4 diagonal adjacent,  next 8 knight moves in chess.
const int dx[16] = {1, 0, 0, -1, 1, 1, -1, -1, 2, 2, 1, 1, -1, -1, -2, -2};
const int dy[16] = {0, -1, 1, 0, -1, 1, -1, 1, -1, 1, -2, 2, -2, 2, -1, 1};

std::string XMAS = "MSMS";

void solve() {
        std::vector<std::string> grid;
        while(getline(std::cin, input)) {
                grid.push_back(input);
        }

        int N = (int)grid.size();
        if (N == 0) {
                std::cout << "0\n";
                return;
        }

        int M = (int)grid[0].size();

        int count = 0;

        for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) if (grid[i][j] == 'A') {
                        bool found = true;
                        for (int dir = 4, ni, nj; dir < 8; ++dir) {
                                ni = i + dx[dir], nj = j + dy[dir];
                                found &= (ni >= 0 && ni < N && nj >= 0 && nj < M && (grid[ni][nj] == 'M' || grid[ni][nj] == 'S'));
                        }
                        if (found) {
                                // As all 4 diagonals exists and are either M or S
                                // Check for different chars in alternate diagonal
                                for (int dir = 4, ni, nj, di, dj; dir < 8; ++dir) {
                                        ni = i + dx[dir], nj = j + dy[dir];
                                        di = i + -dx[dir], dj = j + -dy[dir];
                                        found &= grid[ni][nj] != grid[di][dj];
                                }
                                count += found == true;
                        }
                }
        }

        std::cout << count << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
