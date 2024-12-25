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

        std::vector<std::string> ngrid;
        for (int i = 0; i < rows; ++i) {
                std::string row;
                for (int j = 0; j < columns; ++j) {
                        if (grid[i][j] == '#') {
                                row += "##";
                        } else if (grid[i][j] == '.') {
                                row += "..";
                        } else if (grid[i][j] == '@') {
                                row += "@.";
                        } else if (grid[i][j] == 'O') {
                                row += "[]";
                        }
                }
                ngrid.push_back(row);
        }

        std::swap(grid, ngrid);
        rows = (int) grid.size(), columns = (int) grid[0].size();

        std::array<int, 2> robot = {-1, -1};
        for (int i = 0; i < rows; ++i)
                for (int j = 0; j < columns; ++j) if (grid[i][j] == '@') robot = {i, j};

        assert(robot[0] != -1);

        auto in = [&](int x, int y) -> bool {
                return x >= 0 && x < rows && y >= 0 && y < columns;
        };

        for (const auto &p : path) {
                for (int i = 0; i < 2; ++i) {
                        if (p == moves[i]) {
                                int nextX = robot[0] + dx[i], nextY = robot[1] + dy[i];
                                if (dy[i] < 0) {
                                        while (grid[nextX][nextY] == ']' && grid[nextX][nextY + dy[i]] == '[') {
                                                nextX += 2 * dx[i], nextY += 2 * dy[i];
                                        }
                                } else {
                                        while (grid[nextX][nextY] == '[' && grid[nextX][nextY + dy[i]] == ']') {
                                                nextX += 2 * dx[i], nextY += 2 * dy[i];
                                        }
                                }

                                if (in(nextX, nextY) && grid[nextX][nextY] == '.') {
                                        grid[robot[0]][robot[1]] = '.';
                                        robot[0] += dx[i], robot[1] += dy[i];
                                        grid[robot[0]][robot[1]] = '@';

                                        if (nextY < robot[1]) {
                                                for (int j = robot[1] - 1; j >= nextY; --j)
                                                        grid[robot[0]][j] = (robot[1] - j - 1) % 2 == 0 ? ']' : '[';
                                        } else {
                                                for (int j = robot[1] + 1; j <= nextY; ++j)
                                                        grid[robot[0]][j] = (j - robot[1] - 1) % 2 == 0 ? '[' : ']';
                                        }
                                }
                        }
                }
                for (int i = 2; i < 4; ++i) {
                        if (p == moves[i]) {
                                bool to_do = true;

                                std::vector<std::vector<int>> connected(columns);
                                connected[robot[1]].push_back(robot[0]);

                                std::queue<std::array<int, 2>> Q; Q.push(robot);
                                while (!Q.empty() && to_do) {
                                        auto [x, y] = Q.front(); Q.pop();

                                        connected[y].push_back(x);

                                        int nx = x + dx[i], ny = y + dy[i];
                                        if (grid[nx][ny] == '[') {
                                                Q.push({nx, ny});
                                                assert(grid[nx][ny + 1] == ']');
                                                Q.push({nx, ny + 1});
                                        } else if (grid[nx][ny] == ']') {
                                                Q.push({nx, ny});
                                                assert(grid[nx][ny - 1] == '[');
                                                Q.push({nx, ny - 1});
                                        } else if (grid[nx][ny] == '.') {
                                                connected[ny].push_back(nx);
                                        } else {
                                                to_do = false;
                                        }
                                }

                                if (to_do) {
                                        for (int col = 0; col < columns; ++col) {
                                                std::sort(connected[col].begin(), connected[col].end());
                                                connected[col].erase(std::unique(connected[col].begin(), connected[col].end()), connected[col].end());

                                                if (dx[i] > 0) {
                                                        for (int j = (int) connected[col].size() - 2; j >= 0; --j) {
                                                                std::swap(grid[connected[col][j]][col], grid[connected[col][j + 1]][col]);
                                                        }
                                                } else {
                                                        for (int j = 1; j < (int) connected[col].size(); ++j) {
                                                                std::swap(grid[connected[col][j]][col], grid[connected[col][j - 1]][col]);
                                                        }
                                                }
                                        }
                                        robot[0] += dx[i], robot[1] += dy[i];
                                }
                        }
                }
        }

        long long gps_coordinates = 0;
        for (int i = 0; i < rows; ++i) for (int j = 0; j < columns; ++j) if (grid[i][j] == '[') gps_coordinates += 100LL * i + j;

        std::cout << gps_coordinates << "\n";
}

int main() {
        std::cin.tie(0) -> sync_with_stdio(0);

        solve();
        return 0;
}

// 1.77245
