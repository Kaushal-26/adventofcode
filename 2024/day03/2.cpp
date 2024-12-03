// https://adventofcode.com/2024/day/3

#include <bits/stdc++.h>

std::string input;

void solve() {
        std::string S;
        while (getline(std::cin, input)) S += input;

        long long result = 0;
        bool flag = true;
        for (int i = 0; i < (int)S.size(); ++i) {
                if (S[i] == ')') {
                        if (i - 3 >= 0 && S.substr(i - 3, 4) == "do()") {
                                flag = true;
                        }
                        if (i - 5 >= 0 && S.substr(i - 6, 7) == "don't()") {
                                flag = false;
                        }
                }
                if (S[i] == '(' && i - 3 >= 0 && S.substr(i - 3, 3) == "mul") {
                        ++ i; // Move open bracket

                        std::string x;
                        while (i < (int)S.size() && S[i] >= '0' && S[i] <= '9') x += S[i], ++ i;

                        if (i == (int)S.size() || S[i] != ',') continue;

                        ++ i; // Move comma

                        std::string y;
                        while (i < (int)S.size() && S[i] >= '0' && S[i] <= '9') y += S[i], ++ i;
                        
                        if (i == (int)S.size() || S[i] != ')') continue;

                        if (flag)
                                result += std::stoi(x) * std::stoi(y);
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
