// https://adventofcode.com/2024/day/12

#include <bits/stdc++.h>
// #include <debug.h>

// https://atcoder.github.io/ac-library/production/document_en/dsu.html

namespace atcoder {

// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct dsu {
  public:
    dsu() : _n(0) {}
    dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

}

using namespace atcoder;

// dsu d(n)                 : dsu of n vertices 0 to n-1                   O(n)
// d.merge(a, b)    int     : connect, and returns parent                  O(a(n))
// d.same(a, b)     bool    : isconnected                                  O(a(n))
// d.leader(a)      int     : parent of a                                  O(a(n))
// d.size(a)        int     : size of component                            O(a(n))    
// d.groups()       vi<vi>  : ist of the vertices in a connected compo     O(n)


template<class T> bool ckmin(T &a, const T b) {
        return b < a ? a = b, 1 : 0;
}

template<class T> bool ckmax(T &a, const T b) {
        return b > a ? a = b, 1 : 0;
}


std::string input;

void solve() {
        std::vector<std::string> grid;

        int N = 0, M = 0;
        while (getline(std::cin, input)) {
                ++ N;
                grid.push_back(input);
                M = (int) input.size();
        }

        auto in = [&](int i, int j) -> bool {
                return i >= 0 && i < N && j >= 0 && j < M;
        };


        // Make connected component of the same color
        atcoder::dsu d(N * M);
        for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                        for (int dx = -1; dx <= 1; ++dx)
                                for (int dy = -1; dy <= 1; ++dy)
                                        if (abs(dx) + abs(dy) == 1)
                                                if (in(i + dx, j + dy) && grid[i][j] == grid[i + dx][j + dy])
                                                        d.merge(i * M + j, (i + dx) * M + j + dy);
        
        long long total_price = 0;

        std::vector<std::vector<int>> groups = d.groups();
        for (auto &group : groups) {
                sort(group.begin(), group.end());

                int A = (int) group.size();
                int S = 0;

                // dbg(group);

                std::map<int, int> back;
                for (int i = 0; i < A; ++i) back[group[i]] = i;


                // Make connected component of same row, column in a connected group
                atcoder::dsu D_X(A), D_Y(A);
                for (int i = 0, el, x, y; i < A; ++i) {
                        el = group[i];
                        x = el / M, y = el % M;

                        for (int dx = -1; dx <= 1; ++dx)
                                if (dx != 0 && in(x + dx, y) && grid[x][y] == grid[x + dx][y])
                                        D_X.merge(i, back[(x + dx) * M + y]);
                        for (int dy = -1; dy <= 1; ++dy)
                                if (dy != 0 && in(x, y + dy) && grid[x][y] == grid[x][y + dy])
                                        D_Y.merge(i, back[x * M + (y + dy)]);
                }

                std::vector<std::vector<int>> x_groups = D_X.groups(), y_groups = D_Y.groups();

                // dbg(x_groups, y_groups);

                for (auto &x_group : x_groups) {
                        sort(x_group.begin(), x_group.end());

                        // Solve from previous state to current state
                        // Here for same column checking for unconnected rows
                        int flag1 = 0, flag2 = 0;
                        for (auto &id : x_group) {
                                int node = group[id];
                                int new_x = node / M, new_y = node % M;

                                int new_flag1 = 0, new_flag2 = 0;
                                for (int dy = -1; dy <= 1; ++dy) if (dy != 0) {
                                        if (in(new_x, new_y + dy) && grid[new_x][new_y] == grid[new_x][new_y + dy]) {

                                        } else {
                                                if (dy < 0) new_flag1 = 1;
                                                else new_flag2 = 1;
                                        }
                                }

                                if (new_flag1 && !flag1) ++ S;
                                if (new_flag2 && !flag2) ++ S;

                                std::swap(new_flag1, flag1), std::swap(new_flag2, flag2);
                        }
                }

                for (auto &y_group : y_groups) {
                        sort(y_group.begin(), y_group.end());

                        // Solve from previous state to current state
                        // Here for same row checking for unconnected columns
                        int flag1 = 0, flag2 = 0;
                        for (auto &id : y_group) {
                                int node = group[id];
                                int new_x = node / M, new_y = node % M;
                                int new_flag1 = 0, new_flag2 = 0;
                                for (int dx = -1; dx <= 1; ++dx) if (dx != 0) {
                                        if (in(new_x + dx, new_y) && grid[new_x][new_y] == grid[new_x + dx][new_y]) {
                                        
                                        } else {
                                                if (dx < 0) new_flag1 = 1;
                                                else new_flag2 = 1;
                                        }
                                }
                                
                                if (new_flag1 && !flag1) ++ S;
                                if (new_flag2 && !flag2) ++ S;

                                std::swap(new_flag1, flag1), std::swap(new_flag2, flag2);

                        }
                }

                // dbg(A, S);

                total_price += (long long)A * S;
        }

        std::cout << total_price << "\n";

}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
