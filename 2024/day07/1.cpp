// https://adventofcode.com/2024/day/7

#include <bits/stdc++.h>


std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(), oin.str(input);
}

void solve() {
        long long answer = 0;
        while (getline(std::cin, input)) {
                input.erase(std::find(input.begin(), input.end(), ':'));
                
                set_oin();

                std::vector<long long> A;
                for (long long val = 0; oin >> val; A.push_back(val));

                auto T = A;

                int N = (int) A.size();
                for (int i = 0, j = 2; i < 1 << (N - 2); ++i) {
                        for (j = 2; j < N; ++j) {
                                if (i >> (j - 2) & 1) {
                                        if (A[1] > 2 * (A[0] + A[j] - 1) / A[j]) {
                                                A[1] = -1;
                                                break;
                                        }

                                        A[1] *= A[j];
                                } else {
                                        if (A[1] > A[0] - A[j]) {
                                                A[1] = -1;
                                                break;
                                        }

                                        A[1] += A[j];
                                }
                        }

                        if (A[0] == A[1]) break;
                        A = T;
                }

                if (A[0] == A[1]) answer += A[0]; 
        }

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
