#include <queue>
#include <vector>
#include <iostream>
// 二项式系数可以由杨辉三角形推出

void PrintYANGTriangle(int n)
{
    std::queue<int> coef;
    int s = 0, t;
    coef.push(1);
    coef.push(1);
    // 实际上这里的队列最终存储的是n+1行的系数 但是打印的是第n行的数据
    for (int i = 1; i <= n; i++)
    {
        std::cout << std::endl;
        // 在末尾插入0
        coef.push(0);
        // 不用再给s=0;
        // 因为内层for循环结束后 s=0 相当于在每层最开头赋值0
        for (int j = 1; j <= i + 2; j++)
        {
            t = coef.front();
            coef.pop();
            coef.push(s + t);
            s = t;
            if (j != i + 2)
                std::cout << s << "  ";
        }
    }
}
// int main()
// {
//     PrintYANGTriangle(3);
//     // std::cout << 1;
//     return 0;
// }
// 实现打印二项式(a+b)^n 保留最后一行的数据即可
void PrintBinomialEx(int n)
{
    std::queue<int> coef;
    coef.push(1);
    coef.push(1);
    int s = 0, t;
    for (int i = 1; i < n; i++) // 不能加<=这里不是打印 否则会存储n+1行的数据
    {
        // 插入0
        coef.push(0);
        for (int j = 1; j <= i + 2; j++)
        {
            t = coef.front();
            coef.pop();
            coef.push(s + t);
            s = t;
        }
    }
    // 由于队列不能随机访问 只能存到vector容器中以便访问
    std::queue<int> coef_temp(coef);
    std::vector<int> coef_v;
    while (!coef_temp.empty())
    {
        coef_v.push_back(coef_temp.front());
        coef_temp.pop();
    }
    for (int i = 0, j = n; i <= n && j >= 0; i++, j--)
    {
        if (i == 0)
        {
            std::cout << "a";
            (j == 1) ? std::cout << " + " : std::cout << "^" << j << " + ";
            continue;
        }
        if (j == 0)
        {
            std::cout << "b";
            (i == 1) ? std::cout << "" : std::cout << "^" << i;
            continue;
        }
        std::cout << coef_v[i] << "a^" << j << "b^" << i << " + ";
    }
}

int main()
{
    PrintBinomialEx(5);
    return 0;
}