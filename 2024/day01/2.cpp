#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void solve() {
        std::vector<int> X, Y;
        for (; getline(std::cin, input);) {
                oin.clear(); oin.str(input);

                int x, y; oin >> x >> y;
                X.push_back(x); Y.push_back(y);
        }

        sort(X.begin(), X.end()); sort(Y.begin(), Y.end());

        std::map<int, int> Y_map;
        for (auto &y : Y) ++ Y_map[y];

        long long answer = 0;
        for (int i = 0; i < (int)X.size(); ++i) answer += (long long)X[i] * Y_map[X[i]];

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0; 
}

// 1.77245
