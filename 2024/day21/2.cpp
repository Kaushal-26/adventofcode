// https://adventofcode.com/2024/day/21

#include <bits/stdc++.h>

const int LEVELS = 25;

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        std::map<char, int> mapped;

        // Mapped nodes
        for (char c = '0'; c <= '9'; c++) mapped[c] = c - '0';
        mapped['A'] = 10;
        mapped['<'] = 11, mapped['>'] = 12, mapped['^'] = 13, mapped['v'] = 14;

        std::map<int, std::array<int, 2>> keyPad[2];
        std::map<std::array<int, 2>, int> reverseKeyPad[2];

        // Directional KeyPad
        keyPad[0][13] = {0, 1}, keyPad[0][10] = {0, 2};
        keyPad[0][11] = {1, 0}, keyPad[0][14] = {1, 1}, keyPad[0][12] = {1, 2};

        // Numeric KeyPad
        keyPad[1][7] = {0, 0}, keyPad[1][8] = {0, 1}, keyPad[1][9] = {0, 2};
        keyPad[1][4] = {1, 0}, keyPad[1][5] = {1, 1}, keyPad[1][6] = {1, 2};
        keyPad[1][1] = {2, 0}, keyPad[1][2] = {2, 1}, keyPad[1][3] = {2, 2};
        keyPad[1][0] = {3, 1}, keyPad[1][10] = {3, 2};

        // Reverse Directional KeyPad
        for (auto &[key, value] : keyPad[0]) reverseKeyPad[0][value] = key;

        // Reverse Numeric KeyPad
        for (auto &[key, value] : keyPad[1]) reverseKeyPad[1][value] = key;

        // Level 0
        auto level0 = [&](int directionalKeyPad1, int directionalKeyPad2) -> long long {
                int x0 = keyPad[0][directionalKeyPad1][0], y0 = keyPad[0][directionalKeyPad1][1];
                int x1 = keyPad[0][directionalKeyPad2][0], y1 = keyPad[0][directionalKeyPad2][1];

                return std::abs(x0 - x1) + std::abs(y0 - y1) + 1;
        };

        // Level 1 to 25
        std::vector dp(15, std::vector(15, std::vector(15, std::vector(LEVELS, -1LL))));
        auto level2 = [&](auto&& self, int keyPad1, int keyPad2, int levelKeyPad, int level) -> long long {
                if (dp[keyPad1][keyPad2][levelKeyPad][level] != -1LL) return dp[keyPad1][keyPad2][levelKeyPad][level];

                bool numeric = level == LEVELS - 1;

                int x0 = keyPad[numeric][keyPad1][0], y0 = keyPad[numeric][keyPad1][1];
                int x1 = keyPad[numeric][keyPad2][0], y1 = keyPad[numeric][keyPad2][1];

                if (keyPad1 == keyPad2) {
                        return level == 0 ? level0(levelKeyPad, mapped['A']) : self(self, levelKeyPad, mapped['A'], mapped['A'], level - 1);
                }

                long long best = 2e18;

                if (x0 < x1) {
                        if (reverseKeyPad[numeric].find({x0 + 1, y0}) != reverseKeyPad[numeric].end()) {
                                int newKeyPad1 = reverseKeyPad[numeric][{x0 + 1, y0}];
                                long long newLevelDP = level == 0 ? level0(levelKeyPad, mapped['v']) : self(self, levelKeyPad, mapped['v'], mapped['A'], level - 1);
                                best = std::min(best, self(self, newKeyPad1, keyPad2, mapped['v'], level) + newLevelDP);
                        }
                } else if (x0 > x1) {
                        if (reverseKeyPad[numeric].find({x0 - 1, y0}) != reverseKeyPad[numeric].end()) {
                                int newKeyPad1 = reverseKeyPad[numeric][{x0 - 1, y0}];
                                long long newLevelDP = level == 0 ? level0(levelKeyPad, mapped['^']) : self(self, levelKeyPad, mapped['^'], mapped['A'], level - 1);
                                best = std::min(best, self(self, newKeyPad1, keyPad2, mapped['^'], level) + newLevelDP);
                        }
                }

                if (y0 < y1) {
                        if (reverseKeyPad[numeric].find({x0, y0 + 1}) != reverseKeyPad[numeric].end()) {
                                int newKeyPad1 = reverseKeyPad[numeric][{x0, y0 + 1}];
                                long long newLevelDP = level == 0 ? level0(levelKeyPad, mapped['>']) : self(self, levelKeyPad, mapped['>'], mapped['A'], level - 1);
                                best = std::min(best, self(self, newKeyPad1, keyPad2, mapped['>'], level) + newLevelDP);
                        }
                } else if (y0 > y1) {
                        if (reverseKeyPad[numeric].find({x0, y0 - 1}) != reverseKeyPad[numeric].end()) {
                                int newKeyPad1 = reverseKeyPad[numeric][{x0, y0 - 1}];
                                long long newLevelDP = level == 0 ? level0(levelKeyPad, mapped['<']) : self(self, levelKeyPad, mapped['<'], mapped['A'], level - 1);
                                best = std::min(best, self(self, newKeyPad1, keyPad2, mapped['<'], level) + newLevelDP);
                        }
                }

                return dp[keyPad1][keyPad2][levelKeyPad][level] = best;
        };

        long long totalComplexity = 0;

        std::string input;
        while (std::cin >> input) {
                int previous = mapped['A'];
                long long complexity = 0;
                for (auto &c : input) {
                        complexity += level2(level2, previous, mapped[c], mapped['A'], LEVELS - 1);
                        previous = mapped[c];
                }

                input.pop_back();
                totalComplexity += stoll(input) * complexity;
        }

        std::cout << totalComplexity << '\n';
}
