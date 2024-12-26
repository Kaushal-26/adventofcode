// https://adventofcode.com/2024/day/21

#include <bits/stdc++.h>

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        // Mapped nodes
        std::map<char, int> mapped;
        for (char c = '0'; c <= '9'; c++) mapped[c] = c - '0';
        mapped['A'] = 10;
        mapped['<'] = 11, mapped['>'] = 12, mapped['^'] = 13, mapped['v'] = 14;

        // Directional KeyPad
        std::map<int, std::array<int, 2>> directionalKeyPad;
        directionalKeyPad[13] = {0, 1}, directionalKeyPad[10] = {0, 2};
        directionalKeyPad[11] = {1, 0}, directionalKeyPad[14] = {1, 1}, directionalKeyPad[12] = {1, 2};

        // Numeric KeyPad
        std::map<int, std::array<int, 2>> numericKeyPad;
        numericKeyPad[7] = {0, 0}, numericKeyPad[8] = {0, 1}, numericKeyPad[9] = {0, 2};
        numericKeyPad[4] = {1, 0}, numericKeyPad[5] = {1, 1}, numericKeyPad[6] = {1, 2};
        numericKeyPad[1] = {2, 0}, numericKeyPad[2] = {2, 1}, numericKeyPad[3] = {2, 2};
        numericKeyPad[0] = {3, 1}, numericKeyPad[10] = {3, 2};

        // Reverse Directional KeyPad
        std::map<std::array<int, 2>, int> reverseDirectionalKeyPad;
        for (auto &[key, value] : directionalKeyPad) reverseDirectionalKeyPad[value] = key;

        // Reverse Numeric KeyPad
        std::map<std::array<int, 2>, int> reverseNumericKeyPad;
        for (auto &[key, value] : numericKeyPad) reverseNumericKeyPad[value] = key;


        // Level 0
        std::vector dp0(15, std::vector(15, -1));
        auto level0 = [&](int directionalKeyPad1, int directionalKeyPad2) -> int {
                if (dp0[directionalKeyPad1][directionalKeyPad2] != -1) return dp0[directionalKeyPad1][directionalKeyPad2];

                int x0 = directionalKeyPad[directionalKeyPad1][0], y0 = directionalKeyPad[directionalKeyPad1][1];
                int x1 = directionalKeyPad[directionalKeyPad2][0], y1 = directionalKeyPad[directionalKeyPad2][1];

                return dp0[directionalKeyPad1][directionalKeyPad2] = std::abs(x0 - x1) + std::abs(y0 - y1) + 1;
        };

        // Level 1
        std::vector dp1(15, std::vector(15, std::vector(15, -1)));
        auto level1 = [&](auto&& self, int directionalKeyPad1, int directionalKeyPad2, int level0DirectionalKeyPad) -> int {
                if (dp1[directionalKeyPad1][directionalKeyPad2][level0DirectionalKeyPad] != -1) return dp1[directionalKeyPad1][directionalKeyPad2][level0DirectionalKeyPad];

                int x0 = directionalKeyPad[directionalKeyPad1][0], y0 = directionalKeyPad[directionalKeyPad1][1];
                int x1 = directionalKeyPad[directionalKeyPad2][0], y1 = directionalKeyPad[directionalKeyPad2][1];

                int best = 1e9;

                if (directionalKeyPad1 == directionalKeyPad2) {
                        return level0(level0DirectionalKeyPad, mapped['A']);
                }

                if (x0 < x1) {
                        if (reverseDirectionalKeyPad.find({x0 + 1, y0}) != reverseDirectionalKeyPad.end()) {
                                int newDirectionalKeyPad1 = reverseDirectionalKeyPad[{x0 + 1, y0}];
                                best = std::min(best, self(self, newDirectionalKeyPad1, directionalKeyPad2, mapped['v']) + level0(level0DirectionalKeyPad, mapped['v']));
                        }
                } else if (x0 > x1) {
                        if (reverseDirectionalKeyPad.find({x0 - 1, y0}) != reverseDirectionalKeyPad.end()) {
                                int newDirectionalKeyPad1 = reverseDirectionalKeyPad[{x0 - 1, y0}];
                                best = std::min(best, self(self, newDirectionalKeyPad1, directionalKeyPad2, mapped['^']) + level0(level0DirectionalKeyPad, mapped['^']));
                        }
                }

                if (y0 < y1) {
                        if (reverseDirectionalKeyPad.find({x0, y0 + 1}) != reverseDirectionalKeyPad.end()) {
                                int newDirectionalKeyPad1 = reverseDirectionalKeyPad[{x0, y0 + 1}];
                                best = std::min(best, self(self, newDirectionalKeyPad1, directionalKeyPad2, mapped['>']) + level0(level0DirectionalKeyPad, mapped['>']));
                        }
                } else if (y0 > y1) {
                        if (reverseDirectionalKeyPad.find({x0, y0 - 1}) != reverseDirectionalKeyPad.end()) {
                                int newDirectionalKeyPad1 = reverseDirectionalKeyPad[{x0, y0 - 1}];
                                best = std::min(best, self(self, newDirectionalKeyPad1, directionalKeyPad2, mapped['<']) + level0(level0DirectionalKeyPad, mapped['<']));
                        }
                }

                return dp1[directionalKeyPad1][directionalKeyPad2][level0DirectionalKeyPad] = best;
        };

        // Level 2
        std::vector dp2(15, std::vector(15, std::vector(15, -1)));
        auto level2 = [&](auto&& self, int numericKeyPad1, int numericKeyPad2, int level1DirectionalKeyPad) -> int {
                if (dp2[numericKeyPad1][numericKeyPad2][level1DirectionalKeyPad] != -1) return dp2[numericKeyPad1][numericKeyPad2][level1DirectionalKeyPad];

                int x0 = numericKeyPad[numericKeyPad1][0], y0 = numericKeyPad[numericKeyPad1][1];
                int x1 = numericKeyPad[numericKeyPad2][0], y1 = numericKeyPad[numericKeyPad2][1];

                int best = 1e9;

                if (numericKeyPad1 == numericKeyPad2) {
                        return level1(level1, level1DirectionalKeyPad, mapped['A'], mapped['A']);
                }

                if (x0 < x1) {
                        if (reverseNumericKeyPad.find({x0 + 1, y0}) != reverseNumericKeyPad.end()) {
                                int newNumericKeyPad1 = reverseNumericKeyPad[{x0 + 1, y0}];
                                best = std::min(best, self(self, newNumericKeyPad1, numericKeyPad2, mapped['v']) + level1(level1, level1DirectionalKeyPad, mapped['v'], mapped['A']));
                        }
                } else if (x0 > x1) {
                        if (reverseNumericKeyPad.find({x0 - 1, y0}) != reverseNumericKeyPad.end()) {
                                int newNumericKeyPad1 = reverseNumericKeyPad[{x0 - 1, y0}];
                                best = std::min(best, self(self, newNumericKeyPad1, numericKeyPad2, mapped['^']) + level1(level1, level1DirectionalKeyPad, mapped['^'], mapped['A']));
                        }
                }

                if (y0 < y1) {
                        if (reverseNumericKeyPad.find({x0, y0 + 1}) != reverseNumericKeyPad.end()) {
                                int newNumericKeyPad1 = reverseNumericKeyPad[{x0, y0 + 1}];
                                best = std::min(best, self(self, newNumericKeyPad1, numericKeyPad2, mapped['>']) + level1(level1, level1DirectionalKeyPad, mapped['>'], mapped['A']));
                        }
                } else if (y0 > y1) {
                        if (reverseNumericKeyPad.find({x0, y0 - 1}) != reverseNumericKeyPad.end()) {
                                int newNumericKeyPad1 = reverseNumericKeyPad[{x0, y0 - 1}];
                                best = std::min(best, self(self, newNumericKeyPad1, numericKeyPad2, mapped['<']) + level1(level1, level1DirectionalKeyPad, mapped['<'], mapped['A']));
                        }
                }

                return dp2[numericKeyPad1][numericKeyPad2][level1DirectionalKeyPad] = best;
        };

        long long totalComplexity = 0;

        std::string input;
        while (std::cin >> input) {
                int previous = mapped['A'];
                int complexity = 0;
                for (auto &c : input) {
                        complexity += level2(level2, previous, mapped[c], mapped['A']);
                        previous = mapped[c];
                }

                input.pop_back();
                totalComplexity += stoll(input) * complexity;
        }

        std::cout << totalComplexity << '\n';
}
