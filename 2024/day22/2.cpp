// https://adventofcode.com/2024/day/22

#include <bits/stdc++.h>

std::string input;

void mix(long long &secret_number, long long value) {
        secret_number ^= value;
}

void prune(long long &secret_number) {
        secret_number %= 16777216;
}

std::vector<int> V;
std::map<std::array<int, 4>, int> mp;
void go(long long &secret_number, int level = 2000) {
        V.push_back(secret_number % 10);

        long long result = secret_number * 64;
        mix(secret_number, result);
        prune(secret_number);

        result = secret_number / 32;
        mix(secret_number, result);
        prune(secret_number);

        result = secret_number * 2048;
        mix(secret_number, result);
        prune(secret_number);

        if (level - 1) go(secret_number, level - 1);
}

void ops() {
        std::set<std::array<int, 4>> st;

        for (int i = 0; i + 4 < (int) V.size(); ++i) {
                std::array<int, 4> arr = {V[i + 1] - V[i], V[i + 2] - V[i + 1], V[i + 3] - V[i + 2], V[i + 4] - V[i + 3]};

                if (st.find(arr) == st.end()) {
                        mp[arr] += V[i + 4];
                        st.insert(arr);
                }
        }
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        while (getline(std::cin, input)) {
                V.clear();

                long long secret_number = stoll(input);
                go(secret_number);

                ops();
        }

        int maximum = 0;
        for (auto &[arr, value] : mp) {
                maximum = std::max(maximum, value);
        }

        std::cout << maximum << "\n";
}

// 1.77245
