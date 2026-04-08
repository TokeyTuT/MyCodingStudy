#include "seqstack.cpp"
#include <string>
#define maxLength 100

// using namespace std;
void PrintMatchedPairs(char *expression)
{
    seqstack<int> s(maxLength);
    // 入栈
    int j;
    int length = strlen(expression);
    for (int i = 0; i < length; i++)
    {
        if (expression[i] == '(')
            s.Push(i);
        else if (expression[i] == ')')
        {
            if (!s.isEmpty())
            {
                s.Pop(j); // 给j赋值
                std::cout << j << "与" << i << "匹配成功" << std::endl;
            }
        }
        else
        {
            // 数字 忽略
            continue;
        }
    }
    while (!s.isEmpty())
    {
        s.Pop(j);
        std::cout << "没有与" << j << "匹配的右括号" << std::endl;
    }
}

int main()
{
    char e[100] = "((q+1)+(1+2))";
    PrintMatchedPairs(e);
    // std::cout << "出生c++" << std::endl;
    return 0;
}
