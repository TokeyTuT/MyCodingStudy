// KMP算法是用于检查模式串是否存在于目标串的一种算法 这种算法的时间复杂度较低
// 获得前缀表
#include <string>
#include <iostream>
void getNext(int *Next, std::string str)
{
    // 初始化Next列表
    int j = 0, i; // j是前缀的指针 i是后缀的指针
    Next[j] = 0;
    for (i = 1; i < str.size(); i++)
    {
        // 前缀不等于后缀
        while (j > 0 && str[i] != str[j])
        {
            j = Next[j - 1];
        }
        // 前缀等于后缀
        if (str[i] == str[j])
        {
            j++;
        }
        // 保存 如果一直不相等 j会在while循环中变为0 不用担心
        Next[i] = j;
    }
}
// 返回查找到的字串下标 若无 则返回-1

int PMK_Search(const std::string &target, const std::string &pattern)
{
    if (pattern.empty())
        return 0; // 约定：空模式视为在位置0匹配

    // int n = (int)target.size();
    // int m = (int)pattern.size();
    std::vector<int> Next(pattern.size());
    getNext(Next.data(), pattern);
    int i = 0, j = 0;
    while (i < target.size())
    {
        if (target[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if (j > 0)
        {
            j = Next[j - 1];
        }
        else
        {
            i++;
        }
        if (j == pattern.size())
            return i - j;
    }
    return -1;
}

int main()
{
    std::string str1 = "aabaaabaaac";
    std::vector<int> next(str1.size());
    getNext(next.data(), str1);
    std::string str2 = "aabaaac";
    std::cout << PMK_Search(str1, str2) << std::endl;
    return 0;
}

// 时间复杂度O(m+n)