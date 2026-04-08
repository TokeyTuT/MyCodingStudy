#include <iostream>
#include <string>
#include <vector>
#include <stack>

int Prio(const std::string op)
{
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else
        return 0;
}
std::vector<std::string> transport(const std::vector<std::string> nifix)
{
    std::stack<std::string> op;
    std::vector<std::string> postfix;
    for (const std::string ch : nifix)
    {
        if (isalnum(ch[0]))
        {
            postfix.push_back(ch);
        }
        else if (ch == "(")
        {
            op.push(ch);
        }
        else if (ch == ")")
        {
            while (!op.empty() && op.top() != "(")
            {
                postfix.push_back(op.top());
                op.pop();
            }
            if (!op.empty() && op.top() == "(")
            {
                op.pop();
            }
        } 
        else
        {
            while (!op.empty() && Prio(op.top()) >= Prio(ch))
            {
                postfix.push_back(op.top());
                op.pop();
            }
            op.push(ch);
        }
        while (!op.empty())
        {
            postfix.push_back(op.top());
            op.pop();
        }
        return postfix;
}


// 测试代码
//  int main()
//  {
//      std::vector<std::string> nifix = {"9", "+", "(", "3", "-", "1", ")", "*", "3", "+", "10", "/", "2"};
//      std::vector<std::string> postfix = transport(nifix);
//      for (std::vector<std::string>::iterator it = postfix.begin(); it != postfix.end(); it++)
//      {
//          std::cout << *it;
//      }
//      return 0;
//  }
