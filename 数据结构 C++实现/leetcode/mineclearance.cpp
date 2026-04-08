#include<iostream>
#include<vector>
using namespace std;

/*
* 'M' 代表一个 未挖出的 地雷，
* 'E' 代表一个 未挖出的 空方块，
* 'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的 已挖出的 空白方块，
* 数字（'1' 到 '8'）表示有多少地雷与这块 已挖出的 方块相邻，
* 'X' 则表示一个 已挖出的 地雷。
*/

/*
* 根据以下规则，返回相应位置被点击后对应的盘面：
    * 如果一个地雷（'M'）被挖出，游戏就结束了--把它改为 'X' 。
    * 如果一个 没有相邻地雷 的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的 未挖出 方块都应该被递归地揭露。
    * 如果一个 至少与一个地雷相邻 的空方块（'E'）被挖出，修改它为数字（'1' 到 '8' ），表示相邻地雷的数量。
    * 如果在此次点击中，若无更多方块可被揭露，则返回盘面。
*/

int DIRS[8][2] = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j) {
    int cnt = 0;
    visited[i][j] = true;
    for (auto [dx, dy] : DIRS) { //第一次遍历 找找周围有几个雷
        int x = i + dx;
        int y = j + dy;
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y]) {
            continue;
        }
        if (board[x][y] == 'M') cnt++;
    }
    if (cnt != 0) { //数字 停止扩散
        board[i][j] = '0' + cnt;
        return;
    }
    board[i][j] = 'B';
    for (auto [dx, dy] : DIRS) {
        int x = i + dx;
        int y = j + dy;
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y] || board[x][y] != 'E') {
            //注意 这里有雷和数字都不应该再遍历了奥
            continue;
        }
        dfs(board, visited, x, y);
    }
}

int main() {
    //init
    int m, n;
    cin >> m >> n;
    vector<vector<char>> board(m, vector<char>(n));
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            cin >> board[i][j];
        }
    }
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<int> clicks(2);
    cin >> clicks[0] >> clicks[1];

    int click_r = clicks[0], click_c = clicks[1];
    if (board[click_r][click_c] == 'M') {
        board[click_r][click_c] = 'X';
    }
    else {
        dfs(board, visited, click_r, click_c);
    }

    for (auto b : board) {
        for (char d : b) {
            cout << d << "  ";
        }
        cout << endl;
    }
    return 0;
}