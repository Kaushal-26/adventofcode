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

        int paper_rolls_accessable_by_forklift = 0;
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
                                ++ paper_rolls_accessable_by_forklift;
                        }
                }
        }

        std::cout << paper_rolls_accessable_by_forklift << "\n";
        return 0;
}
