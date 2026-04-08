#include <iostream>
#include <vector>
#include <unordered_set>
/* 对于递增数列的子序列 要求是不能改变原数列的顺序 这个数列可能有重复元素 同样的 也要在树层进行去重处理
因此如果使用Used记录是否在本层重复很麻烦 要一个一个遍历 能发现是否被使用
因此我们引入unordered_set容器 与set容器不同的是 这个容器不会自动排序 减少了内存的使用
*/
std::vector<int> path;
std::vector<std::vector<int>> result;
void backtracking(const std::vector<int>& Arr,int startIndex)
{
    if(path.size()>1) result.push_back(path);
    std::unordered_set<int> isUsed;
    //不需要写终止条件 因为startIndex遍历到头后会自动停止
    for(int i=startIndex;i<Arr.size();i++){
        //如果下一个入path的数小于上一个数 直接剪去该分支
        
        if(i>0&&path.back()>Arr[i]||isUsed.find(Arr[i])!=isUsed.end()) continue;//注意find函数返回的是函数迭代器
        isUsed.insert(Arr[i]);
        path.push_back(Arr[i]);
        backtracking(Arr,i+1);
        //这里不需要回溯isUsed 因为它是局部变量 每次递归的时候都会重置
        path.pop_back();
    }
}



