#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int mx = 0;
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int& area) {
    if (visited[x][y] || grid[x][y] == 0) return;
    visited[x][y] = true;
    area++;
    for (int i = 0;i < 4;i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) continue;
        dfs(grid, visited, nx, ny, area);
    }
    mx = max(mx, area);
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            if (visited[i][j] || grid[i][j] == 0) continue;
            else {
                int area = 0;
                dfs(grid, visited, i, j, area);
            }
        }
    }
    cout << mx << endl;
    return 0;
}
