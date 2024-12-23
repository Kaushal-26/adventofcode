// https://adventofcode.com/2024/day/22

#include <bits/stdc++.h>

std::string input;

void mix(long long &secret_number, long long value) {
    secret_number ^= value;
}

void prune(long long &secret_number) {
    secret_number %= 16777216;
}

void go(long long &secret_number, int level = 2000) {
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

int main() {
    long long total_secret_number = 0;
    while (getline(std::cin, input)) {
        long long secret_number = stoll(input);
        go(secret_number);
        total_secret_number += secret_number;
    }
    std::cout << total_secret_number << "\n";
}

// 1.77245
