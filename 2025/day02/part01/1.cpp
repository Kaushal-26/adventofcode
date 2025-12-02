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

        int64_t invalid_ids = 0;
        for (int64_t i = 1, new_i; ; ++i) {
                int64_t digs = int64_t(log10(i)) + 1;

                new_i = i;
                while (digs --> 0) new_i *= 10;
                new_i += i;

                if (new_i > MAX) break;

                for (auto &[a, b] : v) {
                        if (new_i >= a && new_i <= b) {
                                invalid_ids += new_i;
                        }
                }
        }

        std::cout << invalid_ids << "\n";

        return 0;
}
