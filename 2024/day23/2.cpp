// https://adventofcode.com/2024/day/23

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void setOin() {
        oin.clear(), oin.str(input);
}

const int _N = 26 * 26;
std::bitset<_N> adjacency_matrix[_N];
std::vector<int> adjacency_list[_N];

std::bitset<_N> dfs(int node, std::bitset<_N> &edges, std::bitset<_N> &nodes) {
        nodes[node] = 1;
        for (int i = nodes._Find_first(); i < _N; i = nodes._Find_next(i))
                if (!adjacency_matrix[node][i] || !edges[i]) {
                        nodes[node] = 0;
                        return std::bitset<_N>();
                }

        edges &= adjacency_matrix[node];

        std::bitset<_N> best = nodes;
        for (auto &second_node : adjacency_list[node]) if (!nodes[second_node]) {
                auto result = dfs(second_node, edges, nodes);
                if (result.count() > best.count()) best = result;
        }

        return best;
}

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

        for (int i = 0; i < _N; ++i) adjacency_matrix[i][i] = 1;

        std::bitset<_N> answer;
        for (int i = 0; i < _N; ++i) {
                std::bitset<_N> edges = adjacency_matrix[i], nodes = std::bitset<_N>();
                auto result = dfs(i, edges, nodes);
                if (result.count() > answer.count()) answer = result;
        }

        std::string password;
        for (int i = answer._Find_first(); i < _N; i = answer._Find_next(i))
                password += (char) (i / 26 + 'a'), password += (char) (i % 26 + 'a'), password += ',';

        password.pop_back();

        std::cout << password << "\n";
}

// 1.77245
