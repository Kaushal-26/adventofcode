// https://adventofcode.com/2024/day/13

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(); oin.str(input);
}

void fix() {
        std::string S;
        for (auto &i : input) {
                if (i >= '0' && i <= '9') S += i;
                if ((int) S.size() > 0 && i == ' ') S += i; 
        }
        input = S;
}

void solve() {
        long long tokens = 0;
        while (getline(std::cin, input)) {
                int a, b, c;
                int p, q, r;
                for (int j = 0; j < 3; ++j) {
                        fix(); set_oin();
                        if (j == 0) {
                                oin >> a >> p;
                        } else if (j == 1) {
                                oin >> b >> q;
                        } else {
                                oin >> c >> r;
                        }
                        getline(std::cin, input);
                }

                long long numerator = (long long)c * p - (long long)a * r;
                long long denominator = (long long)b * p - (long long)a * q;

                if (numerator % denominator) continue;

                long long y = numerator / denominator;
                long long x = (c - b * y);

                if (x % a) continue;

                x /= a;

                tokens += 3 * x + y;
        }

        std::cout << tokens << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
