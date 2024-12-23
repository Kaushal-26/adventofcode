// https://adventofcode.com/2024/day/23

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void setOin() {
        oin.clear(), oin.str(input);
}

const int _N = 26 * 26;
int adjacency_matrix[_N][_N];
std::vector<int> adjacency_list[_N];

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        auto get_value = [&](const std::string &a) {
                return (a[0] - 'a') * 26 + (a[1] - 'a');
        };

        while (getline(std::cin, input)) {
                std::replace(input.begin(), input.end(), '-', ' ');
                setOin();

                std::string a, b; oin >> a >> b;

                int A = get_value(a), B = get_value(b);
                adjacency_matrix[A][B] = 1, adjacency_matrix[B][A] = 1;
                adjacency_list[A].push_back(B), adjacency_list[B].push_back(A);
        }

        long long answer = 0;
        for (int i = 0; i < _N; ++i) {
                if (i / 26 == 't' - 'a') {
                        for (int p = 0; p < (int) adjacency_list[i].size(); ++p) {
                                for (int q = p + 1; q < (int) adjacency_list[i].size(); ++q) {
                                        if (adjacency_list[i][p] / 26 == 't' - 'a' && adjacency_list[i][p] < i) continue;
                                        if (adjacency_list[i][q] / 26 == 't' - 'a' && adjacency_list[i][q] < i) continue;

                                        if (adjacency_matrix[adjacency_list[i][p]][adjacency_list[i][q]]) ++ answer;
                                }
                        }
                }
        }

        std::cout << answer << "\n";
}

// 1.77245
