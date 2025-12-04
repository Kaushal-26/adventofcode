// https://adventofcode.com/2025/day/4

#include <bits/stdc++.h>

int dx[8] = {0, -1, 0, 1, -1, 1, -1, 1};
int dy[8] = {1, 0, -1, 0, 1, -1, -1, 1};

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::string input;
        std::vector<std::string> grid;

        while (std::cin >> input) {
                grid.push_back(input);
        }

        auto remove_paper_rolls = [&]() -> int {
                int paper_rolls_accessable_by_forklift = 0;
                std::vector<std::array<int, 2>> remove;
                for (int i = 0, paper_rolls = 0; i < (int) grid.size(); ++i) {
                        for (int j = 0; j < (int) grid[i].size(); ++j) {
                                if (grid[i][j] != '@') continue;
                                paper_rolls = 0;
                                for (int k = 0; k < 8; ++k) {
                                        int ni = i + dx[k], nj = j + dy[k];
                                        if (ni >= 0 && ni < (int) grid.size() && nj >= 0 && nj < (int) grid[i].size()) {
                                                if (grid[ni][nj] == '@') {
                                                        ++ paper_rolls;
                                                }
                                        }
                                }
                                if (paper_rolls < 4) {
                                        remove.push_back({i, j});
                                        ++ paper_rolls_accessable_by_forklift;
                                }
                        }
                }
                for (auto &[x, y] : remove) {
                        grid[x][y] = '.';
                }
                return paper_rolls_accessable_by_forklift;
        };

        int total_paper_rolls_removed = 0;
        while (true) {
                auto paper_rolls_accessable_by_forklift = remove_paper_rolls();
                if (paper_rolls_accessable_by_forklift == 0) break;
                total_paper_rolls_removed += paper_rolls_accessable_by_forklift;
        }


        std::cout << total_paper_rolls_removed << "\n";
        return 0;
}


