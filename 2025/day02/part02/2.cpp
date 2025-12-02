// https://adventofcode.com/2025/day/2

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

// Set input or output using stringstream
void setOin(bool isInput = true) {
        if (isInput) getline(std::cin, input);
        oin.clear(), oin.str(input);
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);
        std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::getline(std::cin, input);
        std::ranges::replace(input, ',', '\n');
        std::ranges::replace(input, '-', ' ');

        setOin(false);

        std::vector<std::array<int64_t, 2>> v;
        for (int64_t a, b; oin >> a >> b; ) {
                v.push_back({a, b});
        }

        int64_t MAX = v[0][0];
        for (auto &[a, b] : v) MAX = std::max({MAX, a, b});

        std::set<int64_t> S;
        for (int64_t i = 1, new_i, old_i, stop = 0; ; ++i) {
                new_i = old_i = i;
                stop = 0;
                while (1) {
                        int64_t digs = int64_t(log10(i)) + 1;

                        while (digs --> 0) {
                                if (new_i > MAX / 10) {
                                        stop = 1;
                                        break;
                                }
                                new_i *= 10;
                        }

                        if (stop || new_i > MAX - i) {
                                break;
                        }

                        new_i += i;

                        for (auto &[a, b] : v) {
                                if (new_i >= a && new_i <= b) {
                                        S.insert(new_i);
                                }
                        }
                }

                if (new_i == i) break;
        }

        std::cout << std::accumulate(S.begin(), S.end(), int64_t(0)) << "\n";

        return 0;
}
