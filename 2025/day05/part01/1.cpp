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

        
        int fresh_ingredient = 0;
        for (int64_t ingredient; std::cin >> ingredient;) {
                int L = 0, R = (int) v.size() - 1;
                while (L <= R) {
                        int mid = L + (R - L) / 2;

                        if (v[mid][1] < ingredient) {
                                L = mid + 1;
                        } else if (v[mid][0] > ingredient) {
                                R = mid - 1;
                        } else {
                                ++ fresh_ingredient;
                                break;
                        }
                }
        }

        std::cout << fresh_ingredient << "\n";
        return 0;
}
