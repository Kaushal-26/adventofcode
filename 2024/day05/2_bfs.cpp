// https://adventofcode.com/2024/day/5

// BFS = 0.352512431000000s

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(); oin.str(input);
}

void solve() {
        std::map<int, std::set<int>> rules;

        long long answer = 0;
        while (getline(std::cin, input)) {
                if (input.find("|") != std::string::npos) {
                        input[input.find("|")] = ' ';
                        set_oin();

                        int page_1, page_2; oin >> page_1 >> page_2;
                        rules[page_1].insert(page_2);
                } else if (input.find(",") != std::string::npos) {
                        for (auto &i : input) if (i == ',') i = ' ';
                        set_oin();

                        std::vector<int> pages;
                        int page;
                        while (oin >> page) pages.push_back(page);     

                        assert((int)pages.size() % 2);
 
                        std::map<int, std::set<int>> previous;
                        for (int i = 0; i < (int)pages.size(); ++i) previous[pages[i]].insert(i);

                        auto bfs = [&](int node) {
                                std::queue<int> Q; Q.push(node);

                                int min_node = node;
                                while (!Q.empty()) {
                                        auto cur = Q.front(); Q.pop();

                                        min_node = std::min(min_node, cur);
                                        for (auto &rule : rules[pages[cur]]) {
                                                if (previous[rule].size() > 0 && *previous[rule].begin() < cur) {
                                                        Q.push(*previous[rule].begin());
                                                }
                                        }
                                }
                                if (min_node == node) return true;

                                previous[pages[min_node]].erase(min_node); previous[pages[node]].erase(node);
                                std::swap(pages[min_node], pages[node]);
                                previous[pages[min_node]].insert(min_node); previous[pages[node]].insert(node);

                                return false;
                        };

                        bool correct = true;
                        for (int i = 0; i < (int)pages.size(); ++i) {
                                while (!bfs(i)) correct = false;
                        }

                        if (!correct) answer += pages[(int)pages.size() / 2];
                }
        }

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}
