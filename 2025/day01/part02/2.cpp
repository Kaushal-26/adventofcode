// https://adventofcode.com/2025/day/1

#include <bits/stdc++.h>

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        int count = 0;
        std::string S;

        int start = 50;
        while (std::cin >> S) {
                if (S[0] == 'L') {
                        std::ranges::reverse(S);
                        S.pop_back();
                        std::ranges::reverse(S);

                        int moves = std::stoi(S);
                        while (moves --> 0) {
                                -- start;
                                if (start == 0) ++ count;
                                if (start < 0) start = 99;
                        }
                } else {
                        std::ranges::reverse(S);
                        S.pop_back();
                        std::ranges::reverse(S);

                        int moves = std::stoi(S);
                        while (moves --> 0) {
                                ++ start;
                                if (start == 100) start = 0;
                                if (start == 0) ++ count;
                        }
                }
        }

        std::cout << count << "\n";

        return 0;
}
