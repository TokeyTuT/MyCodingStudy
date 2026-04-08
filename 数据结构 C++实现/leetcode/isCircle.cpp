#include<vector>
#include<iostream>
using namespace std;

class Solution {
private:
    int DIRS[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    //   规定 上0 下1 左2 右3
    bool Move(int x, int y, int dir, int num, const vector<string>& plate) {
        int xx = x + DIRS[dir][0];
        int yy = y + DIRS[dir][1];
        if (xx < 0 || yy < 0 || xx >= plate.size() || yy >= plate[0].size()) {
            return false;
        }
        num--;
        if (num < 0) return false;

        char ch = plate[xx][yy];
        if (ch == 'O') {
            return true;
        }
        if (ch == 'E') { // 顺时针
            if (dir == 0)
                dir = 3;
            else if (dir == 1)
                dir = 2;
            else if (dir == 3)
                dir = 1;
            else if (dir == 2)
                dir = 0;
        }
        if (ch == 'W') { // 逆时针
            if (dir == 0)
                dir = 2;
            else if (dir == 1)
                dir = 3;
            else if (dir == 3)
                dir = 0;
            else if (dir == 2)
                dir = 1;
        }
        return Move(xx, yy, dir, num, plate);
    }

public:
    vector<vector<int>> ballGame(int num, vector<string>& plate) {
        vector<vector<int>> res;
        int m = plate.size(), n = plate[0].size();
        // for (int col = 1; col < n - 1; col++) {
        //     if (plate[0][col] == '.') {
        //         if (Move(0, col, 1, num, plate)) res.push_back({ 0,col });
        //     }
        //     if (plate[m - 1][col] == '.') {
        //         if (Move(m - 1, col, 0, num, plate)) res.push_back({ m - 1,col });
        //     }
        // }
        for (int row = 1;row < m - 1;row++) {
            if (plate[row][0] == '.') {
                if (Move(row, 0, 3, num, plate)) res.push_back({ row,0 });
            }
            // if (plate[row][n - 1] == '.') {
            //     if (Move(row, n - 1, 2, num, plate)) res.push_back({ row,n - 1 });
            // }
        }
        return res;
    }
};
int main() {
    Solution s;
    vector<string> plate = { ".....","....O","....O","....." };
    s.ballGame(3, plate);
    return 0;
}