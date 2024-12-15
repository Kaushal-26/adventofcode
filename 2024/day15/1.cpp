//https://adventofcode.com/2024/day/15

#include <bits/stdc++.h>

std::string input;

std::string moves = "<>^v";
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void solve() {
        std::vector<std::string> grid;
        std::string path;

        int rows = 0, columns = 0, flag = 0;
        while (getline(std::cin, input)) {
                if ((int) input.size() == 0) {
                        flag = 1;
                        continue;
                }

                if (flag) {
                        path += input;
                } else {
                        grid.push_back(input);
                        ++ rows;
                        columns = std::max(columns, (int)input.size());
                }
        }

        std::array<int, 2> robot = {-1, -1};
        for (int i = 0; i < rows; ++i)
                for (int j = 0; j < columns; ++j) if (grid[i][j] == '@') robot = {i, j};

        assert(robot[0] != -1);

        auto in = [&](int x, int y) -> bool {
                return x >= 0 && x < rows && y >= 0 && y < columns;
        };

        int dir = -1, last_x = -1, last_y = -1;
        for (const auto &p : path) {
                for (int i = 0; i < 4; ++i) {
                        if (p == moves[i]) {
                                int nlast_x = robot[0] + dx[i], nlast_y = robot[1] + dy[i];
                                
                                flag = 0;
                                if (dir == i && last_x != -1) {
                                        flag = 1;
                                        nlast_x = last_x + dx[i], nlast_y = last_y + dy[i];
                                } else {
                                        dir = -1;
                                        last_x = -1, last_y = -1;
                                }

                                while (in(nlast_x, nlast_y) && grid[nlast_x][nlast_y] == 'O') {
                                        flag = 1;
                                        nlast_x += dx[i], nlast_y += dy[i];
                                }

                                if (in(nlast_x, nlast_y) && grid[nlast_x][nlast_y] == '.') {
                                        grid[robot[0]][robot[1]] = '.';
                                        robot[0] += dx[i], robot[1] += dy[i];
                                        assert(in(robot[0], robot[1]));
                                        grid[robot[0]][robot[1]] = '@';
                                        if (flag) {
                                                grid[nlast_x][nlast_y] = 'O';
                                                last_x = nlast_x, last_y = nlast_y;
                                        }
                                        dir = i;
                                }
                        }
                }
        }

        long long gps_coordinates = 0;
        for (int i = 0; i < rows; ++i) for (int j = 0; j < columns; ++j) if (grid[i][j] == 'O') gps_coordinates += 100LL * i + j;

        std::cout << gps_coordinates << "\n";

        // for (const auto &g : grid) std::cout << g << '\n';
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
