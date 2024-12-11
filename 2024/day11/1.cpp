// https://adventofcode.com/2024/day/11

#include <bits/stdc++.h>

long long input;

void solve() {
        std::vector<long long> A;

        while (std::cin >> input) A.push_back(input);

        for (int days = 1; days <= 25; ++ days) {
                std::vector<long long> B;
                for (auto &a : A) {
                        if (a == 0) {
                                B.push_back(1);
                        } else if (std::to_string(a).size() % 2 == 0) {
                                auto T = std::to_string(a);
                                int SZ = (int) T.size() / 2;
                                B.push_back(stoll(T.substr(0, SZ))); B.push_back(stoll(T.substr(SZ)));
                        } else {
                                B.push_back(a * 2024);
                        }
                }
                std::swap(A, B);
        }

        std::cout << (int) A.size() << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
