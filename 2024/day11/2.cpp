// https://adventofcode.com/2024/day/11

#include <bits/stdc++.h>

long long input;
std::map<long long, long long> dp[76];

long long rec(int times, long long val) {
        if (dp[times].find(val) != dp[times].end()) return dp[times][val];

        if (times == 0) return dp[times][val] = 1;

        long long answer = 0;

        if (val == 0) {
                answer += rec(times - 1, 1);
        } else if (std::to_string(val).size() % 2 == 0) {
                auto T = std::to_string(val);
                int SZ = (int) T.size() / 2;
                answer += rec(times - 1, stoll(T.substr(0, SZ)));
                answer += rec(times - 1, stoll(T.substr(SZ)));
        } else {
                answer += rec(times - 1, val * 2024);
        }

        return dp[times][val] = answer;
}

void solve() {
        std::vector<long long> A;

        while (std::cin >> input) A.push_back(input);

        long long answer = 0;
        for (auto &a : A) answer += rec(75, a);

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
