#include<vector>
using namespace std;

vector<int> path;
vector<vector<int>> result;
vector<bool>Used;
void backtracking(vector<int> A,int n,vector<bool> Used)
{
    if(Used[0]==NULL) {
        Used.assign(n,false);
    }
    if(path.size()==A.size())
    {
        result.push_back(path);
        return;
    }
    for(int i=0;i<A.size();i++){
        if(Used[i]) continue;
        Used[i]=true;
        path.push_back(A[i]);
        backtracking(A,n,Used);
        Used[i]=false;
        path.pop_back();
    }
}
