// https://adventofcode.com/2025/day/5

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
        // std::cin.exceptions(std::ios::badbit | std::ios::failbit);

        std::vector<std::array<int64_t, 2>> v;
        for (; std::getline(std::cin, input);) {
                if (input == "") break;

                std::ranges::replace(input, '-', ' ');
                setOin(false);

                int64_t a, b; oin >> a >> b;
                v.push_back({a, b});
        }

        std::ranges::sort(v);
        
        int64_t fresh_ingredient = 0;
        for (int i = 0, j = 0; i < (int) v.size(); ++i) {
                j = i;

                int64_t max = v[i][1];
                for (; j < (int)v.size() && max >= v[j][0]; ++j) {
                        max = std::max(max, v[j][1]);
                }

                fresh_ingredient += max - v[i][0] + 1;

                i = j - 1;
        }

        std::cout << fresh_ingredient << "\n";
        return 0;
}
