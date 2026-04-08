#include <iostream>
#include <vector>
using namespace std;
// 定义: 0代表空格 1代表Queen

class Solution
{
public:
    void Run(int n)
    {
        // 初始化
        vector<vector<int>> blackboard(n, vector<int>(n, 0));
        result.clear();
        this->backtracking(blackboard, n, 0);
        // for (const auto &solution : result)
        // {
        //     for (const auto &row : solution)
        //     {
        //         for (int v : row)
        //         cout << (v == 1 ? "Q " : ". ");
        //         cout << endl;
        //     }
        //     cout << "--------------------------" << endl;
        // }
        cout << "共找到:" << result.size() << " 个结果" << endl;
    }

private:
    bool isValid(const vector<vector<int>> &blackboard, int row, int col)
    {
        int n = blackboard.size();
        // 检查列
        for (int r = 0; r < row; r++)
        {
            if (blackboard[r][col] != 0)
                return false;
        }
        // 检查左上斜线
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--)
        {
            if (blackboard[r][c] != 0)
                return false;
        }
        // 检查右上斜线
        for (int r = row - 1, c = col + 1; r >= 0 && c < n; r--, c++)
        {
            if (blackboard[r][c] != 0)
                return false;
        }
        return true;
    }

    vector<vector<vector<int>>> result; // 接收所有结果
    void backtracking(vector<vector<int>> &blackboard, int n, int row)
    {
        if (row == n)
        {
            result.push_back(blackboard);
            // 不用考虑不符合情况的问题 下面的遍历有isValid函数检查
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (!isValid(blackboard, row, col))
                continue;
            blackboard[row][col] = 1;
            backtracking(blackboard, n, row + 1);
            // 弹出
            blackboard[row][col] = 0;
        }
    }
};

// 添加主函数
int main()
{
    int n;
    cout << "请输入n: ";
    cin >> n;
    Solution s;
    s.Run(n);
    return 0;
}
