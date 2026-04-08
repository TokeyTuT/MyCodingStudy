#include<iostream>
#include<vector>
using namespace std;
class Solution {
private:
    int DIRS[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // 给每个点打上两个标记，分别代表能否流向太平洋、大西洋
        vector<vector<int>> res;
        int m = heights.size(), n = heights[0].size();
        auto dfs = [&](auto&& dfs, int i, int j) -> pair<bool, bool> { //[太平洋，大西洋]
            int h = heights[i][j];
            heights[i][j] = 0;
            bool flag_Pacific = false;
            bool flag_Atlantic = false;
            for (auto [dx, dy] : DIRS) {
                int x = i + dx;
                int y = j + dy;
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    if (x < 0 || y < 0) {
                        flag_Pacific = true;
                    }
                    if (x >= m || y >= n) {
                        flag_Atlantic = true;
                    }
                    continue;
                }
                if (heights[x][y] > h && heights[x][y] == 0)
                    continue;
                auto [pac, atl] = dfs(dfs, x, y);
                if (pac)
                    flag_Pacific = true;
                if (atl)
                    flag_Atlantic = true;
            }
            if (flag_Atlantic && flag_Pacific)
                res.push_back({ i,j });
            return { flag_Pacific, flag_Atlantic };
            };
        for (int i = 0;i < m;i++) {
            for (int j = 0;j < n;j++) {
                if (heights[i][j] != 0) {
                    dfs(dfs, i, j);
                }
            }
        }
        return res;
    }
};
int main() {
    Solution s;
    // int m, n;
    // cin >> m >> n;
    vector<vector<int>> heights = { {1,2,2,3,5 },{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4} };
    // for (int i = 0;i < m;i++) {
    //     for (int j = 0;j < n;j++) {
    //         cin >> heights[i][j];
    //     }
    // }
    auto res = s.pacificAtlantic(heights);
    for (auto r : res) {
        for (int i : r) {
            cout << i << "  ";
        }
        cout << endl;
    }
    return 0;
} 