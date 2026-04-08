#include <iostream>
#include <vector>
#include <string>
// 数组不重复版本
// std::vector<std::vector<int>> result;
// std::vector<int> path;
// void backtracking(const std::vector<int>& Arr, int startIndex){
//     int size = Arr.size();
//     result.push_back(path); //保存每次节点 并且不能放在for循环中 否则会丢失空集
//     if(startIndex >= size) return;
//     for(int i = startIndex; i < size; i++){
//         path.push_back(Arr[i]);
//         backtracking(Arr, i + 1);
//         path.pop_back();
//     }
// }

// 数组可能有重复版本
std::vector<std::vector<int>> result;
std::vector<int> path;
std::vector<int> Used;
// 使用前要对数组进行排序
bool isSort = false;
void backtracking(const std::vector<int> &arr, int startIndex, std::vector<int> Used)
{
    if (Used[0] == NULL)
        Used.assign(arr.size(), 0);
    if (!isSort)
    {
        sort(arr.begin(), arr.end());
        isSort = true;
    }
    result.push_back(path);
    for (int i = startIndex; i < arr.size(); i++)
    {
        if (i > 0 && arr[i - 1] == arr[i] && Used[i - 1] == 0)
            continue; // 代表有相同数值的元素已经在同一层开辟了分支
        // 若arr[i-1]==arr[i]&&Used[i-1]==1,说明在这个分支这个路径下 相同数值的元素已开辟了在这个支 目前这个元素在这个支下 不影响结果重复
        path.push_back(arr[i]);
        Used[i] = 1;
        backtracking(arr, i + 1, Used);
        // 弹出
        Used[i] = 0;
        path.pop_back();
    }
}
