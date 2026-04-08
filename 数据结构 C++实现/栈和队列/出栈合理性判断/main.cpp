// 题目描述:一个栈的顺序为1,2,3,……,N,判断p1,p2,p3……是否为合法出栈顺序

#include <stack>
#include <queue>
#include <iostream>

bool isValid(int n,std::queue<int> q)
{
    std::stack<int> s;
    int y=1;
    while(s.size()<=n&&!q.empty())
    {
        s.push(y);
        y++;
        while(!s.empty()&&!q.empty()&&s.top()==q.front()){
            s.pop();
            q.pop();
        }
        if(y==n+1) break;
    }
    if(q.empty()&&s.empty()) return true;
    else return false;
}