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
                for (int i = 0, x = 0; i < (int) pow(3, N - 2); ++i) {
                        x = i;
                        for (int j = 2; j < N; ++j) {
                                if (x % 3 == 0) {
                                        if (A[1] > 2 * (A[0] + A[j] - 1) / A[j]) {
                                                A[1] = -1;
                                                break;
                                        }

                                        A[1] *= A[j];
                                } else if (x % 3 == 1) {
                                        if (A[1] > A[0] - A[j]) {
                                                A[1] = -1;
                                                break;
                                        }

                                        A[1] += A[j];
                                } else {
                                        // A[1] *= pow(10, len(A[j]))
                                        // A[1] += A[j]
                                        long long power_of_ten = pow(10, static_cast<int>(log10(A[j]) + 1));
                                        if (A[1] > 2 * (A[0] + power_of_ten - 1) / power_of_ten) {
                                                A[1] = -1;
                                                break;
                                        }
                                        A[1] *= power_of_ten;

                                        if (A[1] > A[0] - A[j]) {
                                                A[1] = -1;
                                                break;
                                        }
                                        A[1] += A[j];
                                }
                                x /= 3;
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
