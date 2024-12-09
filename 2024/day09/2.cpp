// https://adventofcode.com/2024/day/9

#include <bits/stdc++.h>

void solve() {
        std::string S; std::cin >> S;

        std::vector<std::array<int, 3>> T, M;

        int len = 0;
        for (int i = 0, x; i < (int) S.size(); ++i) {
                x = S[i] - '0';
                if (x == 0) continue;

                if (i % 2 == 0) {
                        T.push_back({i, len, len + x});
                } else {
                        M.push_back({x, len, len + x});
                }
                len += x;
        }

        std::set<std::array<int, 3>> A;
        for (int i = (int) T.size() - 1, add = 0; i >= 0; --i) {
                add = 0;
                for (int j = 0; j < (int) M.size() && !add; ++j) {
                        if (M[j][1] > T[i][1]) break;
                        if (M[j][0] >= T[i][2] - T[i][1]) {
                                A.insert({T[i][0], M[j][1], M[j][1] + T[i][2] - T[i][1]});
                                add = 1;
                                M[j][0] -= T[i][2] - T[i][1];
                                M[j][1] += T[i][2] - T[i][1];
                        }
                }

                if (!add) {
                        A.insert(T[i]);
                }
        }

        long long result = 0;
        for (auto &a : A) {
                for (int i = a[1]; i < a[2]; ++i) {
                        result += i * (a[0] / 2);
                }
        }

        std::cout << result << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
