#include <iostream>
#include <bits/stdc++.h>
#include <thread>

int r, c, n, s, f;
char MapDirection[100+1][100+1];
int Distance[10][10];
std::vector<std::pair<int, int>> point_vector;
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
void Input() {
    std::cin >> r >> c >> n >> s >> f;
    for (int i = 0; i < r; ++i) {
        std::cin >> MapDirection[i];
    }
}

void BFS(std::pair<int, int> _s) {
    std::queue<std::pair<int, int>> q;
    q.push(_s);
    bool is_visited[r][c];
    //initialize is_visited
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            is_visited[i][j] = false;
        }
    }
    int d[r][c];
    //initialize distance array
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            d[i][j] = 0;
        }
    }
    is_visited[_s.first][_s.second] = true;
    while (!q.empty()) {
        std::pair<int, int> temp = q.front();
        q.pop();
        for (int i = 0; i < 8; ++i) {
            int next_r = dx[i] + temp.first;
            int next_c = dy[i] + temp.second;
            if (next_c >= 0 && next_c < c && next_r >= 0 && next_r < r) {
                if (is_visited[next_r][next_c] == false && MapDirection[next_r][next_c] != '#')
                {
                    d[next_r][next_c] = d[temp.first][temp.second] + 1;
                    if (MapDirection[next_r][next_c] != '.') {
                        Distance[MapDirection[_s.first][_s.second]-'0'][MapDirection[next_r][next_c] - '0'] = d[next_r][next_c];
                    }
                    is_visited[next_r][next_c] = true;
                    q.push({next_r, next_c});
                }
            }
        }
    }
}


void Solve() {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (MapDirection[i][j] != '#' && MapDirection[i][j] != '.') {
                BFS({i, j});
            }
        }
    }
    std::vector<int> permutation_arr;
    for (int i = 1; i <= n; ++i) {
        if (i != s && i != f) {
            permutation_arr.push_back(i);
        }
    }
    sort(permutation_arr.begin(), permutation_arr.end());
    int result = INT_MAX;
    if (!permutation_arr.empty()) {
        do
        {
            int temp_result = 0;
            temp_result = Distance[s][permutation_arr[0]] + Distance[permutation_arr[permutation_arr.size() - 1]][f];
            for (int i = 0; i < permutation_arr.size() - 1; ++i)
            {
                temp_result += Distance[permutation_arr[i]][permutation_arr[i + 1]];
            }
            result = std::min(temp_result, result);
        } while (std::next_permutation(permutation_arr.begin(), permutation_arr.end()));
    } else {
        result = Distance[s][f];
    }
    if (result == 0) result = -1;
    std::cout << result << "\n";
}

int main() {
    if (freopen("/home/avn/cpp_project/example/input.txt", "r", stdin) == nullptr) {
        std::cout << "failed" << std::endl;
        return 0;
    }
    freopen("/home/avn/cpp_project/example/output.txt", "w", stdout);
    Input();
    Solve();
    return 0;
}
