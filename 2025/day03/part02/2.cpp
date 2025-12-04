// https://adventofcode.com/2025/day/3

#include <bits/stdc++.h>


// 1 2 3 4 5 6 7 8 9 10 11
// 1 2 3 4 5 6 7 8 9 10 11 12
// 1 2 3 4 5 6 7 8 9 10 11 12 13

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::string S;

        int64_t total_output_joltage = 0;
        while (std::cin >> S) {
                int64_t largest_joltage = 0, new_largest_joltage = 0;
                std::vector<int> digs, new_digs;
                for (int i = 0; i < 12; ++i) {
                        digs.push_back(S[i] - '0');
                        largest_joltage *= 10, largest_joltage += (S[i] - '0');
                }

                for (int i = 12, change = 0; i < (int) S.size(); ++i) {
                        new_digs.clear(), change = 0;
                        for (int j = 0; j < 12; ++j) {
                                new_largest_joltage = 0;
                                for (int k = 0; k < 12; ++k) {
                                        if (j == k) continue;
                                        new_largest_joltage *= 10;
                                        new_largest_joltage += digs[k];
                                }

                                new_largest_joltage *= 10, new_largest_joltage += S[i] - '0';
                                if (new_largest_joltage > largest_joltage) {
                                        largest_joltage = new_largest_joltage;
                                        for (auto d : digs) new_digs.push_back(d);
                                        new_digs.erase(new_digs.begin() + j);
                                        new_digs.push_back(S[i] - '0');
                                        change = 1;
                                }
                        }
                        if (change) digs = new_digs;
                }

                total_output_joltage += largest_joltage;
        }

        std::cout << total_output_joltage << "\n";
        return 0;
}
