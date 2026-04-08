#include "transports.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
// 将后缀表达式转入栈中运算

class Calu
{
public:
    Calu(std::vector<std::string> nifix) : result(0) { this->postfix = transport(postfix); };
    void clear()
    {
        postfix.clear();
    }
    int run()
    {
        double temp1 = 0;
        double temp2 = 0;
        double s = 0;
        for (const std::string &ch : postfix)
        {
            if (isalnum(ch[0]))
            {
                num.push(stoi(ch));
                continue;
            }
            else
            {
                temp1 = num.top();
                num.pop();
                temp2 = num.top();
                num.pop();
                if (ch == "+")
                {
                    num.push(temp1 + temp2);
                }
                if (ch == "*")
                {
                    num.push(temp1 * temp2);
                }
                if (ch == "/")
                {
                    num.push(temp2 / temp1);
                }
                if (ch == "-")
                {
                    num.push(temp2 - temp1);
                }
                continue;
            }
        }
        return num.top();
    }

private:
    std::vector<std::string> postfix;
    std::stack<int> num;
    int result;
};
int main()
{
    std::vector<std::string> nifix={"9", "+", "(", "3", "-", "1", ")", "*", "3", "+", "10", "/", "2"};
    Calu c(nifix);
    // Calu c;
    std::cout << c.run() << std::endl;
    return 0;
}
