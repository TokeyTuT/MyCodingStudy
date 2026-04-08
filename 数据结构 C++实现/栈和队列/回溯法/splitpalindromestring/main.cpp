#include <iostream>
#include <vector>
#include <string>

class Solution
{
public:
    bool isPalindrome(const std::string &s, int start, int end)
    {
        for (int i = start, j = end; i < j; i++, j--)
        {
            if (s[i] != s[j])
            {
                return false;
            }
        }
        return true;
    }
    std::vector<std::string> temp; // 存放临时的数据
    std::vector<std::vector<std::string>> result;
    void backtracking(std::string target, int startIndex)
    {
        // 修改1：去掉循环内的 return，让回溯完整遍历所有分割
        if (startIndex >= target.size())
        {
            result.push_back(temp);
            return;
        }
        for (int i = startIndex; i < target.size(); i++)
        {
            if (!this->isPalindrome(target, startIndex, i))
                continue;
            std::string str = target.substr(startIndex, i - startIndex + 1);
            temp.push_back(str);
            backtracking(target, i + 1); // 修改2：递归时应传 i+1
            temp.pop_back();
        }
    }
    void run()
    {
        std::string s = "aabbaa";
        this->backtracking(s, 0);
        // 修改3：输出所有分割结果
        for (const auto &vec : result)
        {
            for (const auto &str : vec)
            {
                std::cout << str << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Solution s;
    s.run();
}