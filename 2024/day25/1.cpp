// https://adventofcode.com/2024/day/25

#include <bits/stdc++.h>

std::string input;
int R = 7, C = 5;

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        std::vector<std::string> locks, keys;
        auto make = [&](std::vector<std::string> grid) {
                bool lock = grid[0][0] == '#';

                std::string heights_in_base10;
                for (int i = 0, j = 0; i < C; ++ i) {
                        for (j = 0; j < R && grid[j][i] == grid[0][0]; ++j);
                        heights_in_base10 += (lock ? j - 1 : R - j - 1) + '0';
                }

                if (lock)
                        locks.push_back(heights_in_base10);
                else
                        keys.push_back(heights_in_base10);
        };

        while (getline(std::cin, input)) {
                if (input.empty()) continue;

                std::vector<std::string> grid = {input};
                for (int i = 1; i < R; ++i) {
                        getline(std::cin, input);
                        grid.push_back(input);
                }

                make(grid);
        }

        int perfect_lock_key_pairs = 0;
        for (auto &lock : locks) {
                for (auto &key : keys) {
                        bool is_perfect = true;
                        for (int i = 0; i < (int) lock.size() && is_perfect; ++i) {
                                if (lock[i] - '0' + key[i] - '0' > 5) {
                                        is_perfect = false;
                                        break;
                                }
                        }
                        perfect_lock_key_pairs += is_perfect == true;
                }
        }

        std::cout << perfect_lock_key_pairs << "\n";

        return 0;
}
