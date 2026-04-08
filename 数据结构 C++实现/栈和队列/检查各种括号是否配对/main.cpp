#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
using namespace std;
// 检测右括号
unordered_map<char, char> bracket_match = {
    {')', '('},
    {']', '['},
    {'}', '{'}};
// 检测左括号
unordered_map<char, char> reversed_bracket_match = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}};
bool isValid(const string &s)
{
    stack<char> leftbracket;
    for (const char c : s)
    {
        // 检测到右括号
        if (bracket_match.count(c))
        {
            // 对比栈顶
            if (leftbracket.empty())
                return false; // 栈顶为空
            else if (leftbracket.top() != bracket_match[c])
                return false;
            else
            {
                leftbracket.pop();
            }
        }
        // 检测到右括号
        else if (reversed_bracket_match.count(c))
        {
            // 入栈
            leftbracket.push(c);
        }
        else
        {
            continue;
        }
    }
    return true;
}
int main() {
    std::string test = "{[()]}";
    if (isValid(test)) {
        std::cout << "括号配对正确" << std::endl;
    } else {
        std::cout << "括号配对错误" << std::endl;
    }
    return 0;
}