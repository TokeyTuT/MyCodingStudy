#include<vector>
using namespace std;
vector<int> path;
vector<vector<int>> result;
void backtracking(int m,int n,int startIndex){
    if(path.size()==n) {
        result.push_back(path);
        return;
    }
    for(int i=startIndex;i<=m;i++)
    {
        path.push_back(i);
        backtracking(m,n,i+1);
        path.pop_back();
    }
}