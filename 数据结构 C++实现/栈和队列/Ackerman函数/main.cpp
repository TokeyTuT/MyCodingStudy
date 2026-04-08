#include <iostream>
// 递归定义
int Akm(int m, int n)
{
    if (m == 0)
        return n + 1;
    if (m != 0 && n == 0)
        return Akm(m - 1, n);
    else
        return Akm(m - 1, Akm(m, n - 1));
}

int main()
{
    std::cout << Akm(3,4);
    return 0;
}
