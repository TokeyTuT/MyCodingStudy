// 用回溯法实现数字组合
/*
如 1 2 3 4
两两组合为 12 13 14 23 24 34
*/
#include <iostream>
#include <vector>
#include <algorithm>

// n代表1～n的数 k代表需要组合的数组容量
void backtracking(int n, int k, int starIndex, std::vector<std::vector<int>> &result, std::vector<int> &path)
{
    if (path.size() == k)
    {
        // 路径上的元素集合完毕 插入result中
        result.push_back(path);
        return;
    }
    else
    {
        for (int i = starIndex; i <= n; i++)
        {
            path.push_back(i);
            backtracking(n, k, i + 1, result, path);
            path.pop_back();
        }
    }
}

int main()
{
    std::vector<std::vector<int>> result; // 数组的大小代表需要组合的个数
    std::vector<int> path;
    backtracking(10, 2, 1, result, path);
    return 0;
}