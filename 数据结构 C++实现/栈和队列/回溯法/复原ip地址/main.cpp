#include <iostream>
#include <string>
#include <vector>

bool isValid(const std::string s)
{
    // 合法的ip地址每个.前应该是1&3个有效数字
    if (s.size() == 1 || s.size() == 3)
        return true;
    return false;
}

// pointSum 代表打了几个点 正常的ip地址应该是三个点
// startIndex代表开始的数字

void backtracking(std::string s, int startIndex, int pointSum)
{
    if (pointSum = 3)
    {
        return;
    }
    for (int i = startIndex; i < s.size(); i++)
    {
        std::string temp=s.substr(startIndex,i);
        if(!isValid(temp)) break;
        //加一个.
        s.insert(s.begin() + i + 1, '.');
        pointSum++;
        //插入了一个逗号 所以要+2
        backtracking(s,startIndex+2,pointSum);
        pointSum--;
        s.erase(s.begin()+i+1);
    }
}

