#include <vector>
class Solution
{
private:
    // 只要一个解法 用bool作返回值
    bool backtracking(std::vector<std::vector<int>> &blackboard)
    {
        // 不需要判断终止条件 第一层遍历到结束即结束
        for (int row = 0; row < 9; row++) // 遍历行
        {
            for (int col = 0; col < 9; col++) // 遍历列
            {
                if (blackboard[row][col] != 0)
                    continue;                      // 已经占有数 返回
                for (int num = 1; num < 10; num++) // 测试每个数
                {
                    if (this->isValid(blackboard, num, row, col))
                        continue;
                    blackboard[row][col] = num;
                    if (backtracking(blackboard))
                        return true;
                    // 回溯
                    blackboard[row][col] = 0;
                }
                return false; // 没有符合的数
            }
        }
        return true; // 已经排满的标志 这是留给最后一次递归的
        /*
        这样想 现在9*9的棋盘已经填满 来到最后一次递归 试着推断这三层for循环 是不是只会到这里了
        所以说这是留给最后一次的填满的标志
        */
    }
    bool isValid(const std::vector<std::vector<int>> &blackboard, int targetNum, int row, int col)
    {
        // 遍历列
        for (int r = 0; r < 9; r++)
        {
            if (blackboard[r][col] == targetNum)
                return false;
        }
        // 遍历行
        for (int c = 0; c < 9; c++)
        {
            if (blackboard[row][c] == targetNum)
                return false;
        }
        // 检测3*3宫格 10*10棋盘写法
        for (int r = row - 1; r <= row + 1; r++)
        {
            for (int c = col - 1; c <= col + 1; c++)
            {
                if (r == row && c == col)
                    continue;
                if (blackboard[r][c] == targetNum)
                    return false;
            }
        }
        //9*9棋盘写法
    //     int startRow = (row / 3) * 3;
    //     int startCol = (col / 3) * 3;
    //     for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
    //     for (int j = startCol; j < startCol + 3; j++) {
    //         if (board[i][j] == val ) {
    //             return false;
    //         }
    //     }
    // }
        return true;
    }
};