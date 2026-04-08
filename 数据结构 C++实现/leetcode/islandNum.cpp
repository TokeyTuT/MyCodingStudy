#include<iostream>
#include<queue>
#include<vector>
using namespace std;
//岛屿问题

int dir[4][2] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0} };

void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    if (grid[x][y] == 0 || visited[x][y] == true) return;
    visited[x][y] = true; //已访问
    for (int i = 0;i < 4;i++) { //遍历四个方向
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];
        if (next_x < 0 || next_y < 0 || next_x == grid.size() || next_y == grid[0].size()) {
            continue;
        }
        dfs(grid, visited, next_x, next_y);
        //一般有回溯 但是岛屿问题不需要回溯
    }
}

void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que;
    que.push({ x,y });
    while (!que.empty()) {
        auto [_x, _y] = que.front();
        que.pop();
        for (int i = 0;i < 4;i++) {
            int next_x = _x + dir[i][0];
            int next_y = _y + dir[i][1];
            if (next_x < 0 || next_y < 0 || next_x == grid.size() || next_y == grid[0].size()) {
                continue;
            }
            if (visited[next_x][next_y]||grid[next_x][next_y]==0) continue;
            visited[next_x][next_y] = true;
            que.push({next_x,next_y});
        }
    }
}
int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<vector<bool>> visited(m, vector<bool>(n, false)); //标记是否访问过
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            cin >> grid[i][j];
        }
    }
    int res = 0;
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            if (grid[i][j] == 1 && visited[i][j] == false) {
                res++;
                // dfs(grid, visited, i, j);
                bfs(grid, visited, i, j);
            }
        }
    }
    cout << res << endl;
    return 0;
}

