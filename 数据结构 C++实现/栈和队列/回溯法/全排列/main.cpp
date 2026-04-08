#include <iostream>
#include <vector>
#include <unordered_set>
std::vector<int> path;
std::vector<std::vector<int>> result;
// 现对Arr进行排序
void backtracking(const std::vector<int> Arr, std::vector<int> Used)
{
    if (path.size() == Arr.size())
    {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < Arr.size(); i++)
    {
        if (i > 0 && Arr[i - 1] == Arr[i] && Used[i - 1] == 1)
            continue;
        if (Used[i] == 1)
            continue;
        path.push_back(Arr[i]);
        Used[i] == 1;
        backtracking(Arr, Used);
        path.pop_back();
        Used[i] = 0;
    }
}

// 同样也可以用set容器写 而且这样不用提前排序
void backtracking2(const std::vector<int> Arr, std::vector<int> Used)
{
    if (path.size() == Arr.size())
    {
        result.push_back(path);
        return;
    }
    std::unordered_set<int> uset;
    for (int i = 0; i < Arr.size(); i++)
    {
        if (i > 0 && uset.find(Arr[i]) != uset.end())
            continue;
        if (Used[i] == 1)
            continue;
        path.push_back(Arr[i]);
        Used[i] == 1;
        backtracking2(Arr, Used);
        Used[i] = 0;
        path.pop_back();
    }
}