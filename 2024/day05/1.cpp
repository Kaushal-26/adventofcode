// https://adventofcode.com/2024/day/5

#include <bits/stdc++.h>

std::string input;
std::istringstream oin;

void set_oin() {
        oin.clear(); oin.str(input);
}

void solve() {
        std::map<int, std::vector<int>> rules;

        long long answer = 0;
        while (getline(std::cin, input)) {
                if (input.find("|") != std::string::npos) {
                        input[input.find("|")] = ' ';
                        set_oin();

                        int page_1, page_2; oin >> page_1 >> page_2;
                        rules[page_1].push_back(page_2);
                } else if (input.find(",") != std::string::npos) {
                        for (auto &i : input) if (i == ',') i = ' ';
                        set_oin();

                        std::vector<int> pages;
                        int page;
                        while (oin >> page) pages.push_back(page);     

                        assert((int)pages.size() % 2);

                        bool correct = true;
                        std::set<int> previous;
                        for (int i = 0; i < (int)pages.size() && correct; ++i) {
                                for (auto &rule : rules[pages[i]]) {
                                        correct &= previous.find(rule) == previous.end();
                                        if (!correct) break;
                                }
                                previous.insert(pages[i]);
                        }

                        if (correct) answer += pages[(int)pages.size() / 2];
                }
        }

        std::cout << answer << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}