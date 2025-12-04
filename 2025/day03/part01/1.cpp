// https://adventofcode.com/2025/day/3

#include <bits/stdc++.h>

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::string S;

        int total_output_joltage = 0;
        while (std::cin >> S) {
                int largest_digit = 0, largest_joltage = 0;
                for (auto &s : S) {
                        largest_joltage = std::max(largest_joltage, largest_digit * 10 + (s - '0'));
                        if (s - '0' >= largest_digit) {
                                largest_digit = s - '0';
                        }
                }
                total_output_joltage += largest_joltage;
        }

        std::cout << total_output_joltage << "\n";
        return 0;
}
