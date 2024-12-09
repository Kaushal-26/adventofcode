// https://adventofcode.com/2024/day/9

#include <bits/stdc++.h>

void solve() {
        std::string S; std::cin >> S;

        std::vector<int> T, V;
        for (int i = 0, x; i < (int) S.size(); ++i) {
                x = S[i] - '0';
                if (i % 2 == 0) {
                        while (x --> 0) T.push_back(i / 2), V.push_back((int)T.size() - 1);
                } else {
                        while (x --> 0) T.push_back(-1);
                }
        }

        for (int i = 0; i < (int) T.size(); ++i) if (T[i] == -1 && i < V.back()) {
                T[i] = T[V.back()];
                T[V.back()] = -1;
                V.pop_back();
        }

        long long result = 0;
        for (int i = 0; i < (int) T.size(); ++i) if (T[i] != -1) {
                result += i * T[i];
        }

        std::cout << result << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
