#include<iostream>
using namespace std;
int count=0;
void hanoi(int n,char src,char tmp,char target){
    if(n==1){
        // cout<<"Move top disk from peg "<<src<<" to peg "<<target<<endl;
        ::count++;
        return;
    }
    else
    {
        hanoi(n-1,src,target,tmp); //将src上面n-1个盘转到tmp柱上
        //此时src柱子还剩一个盘子
        // cout<<"Move top disk from peg "<<src<<" to peg "<<target<<endl;
        ::count++;
        hanoi(n-1,tmp,src,target);//将tmp上n-1个盘转到target柱上
    }
}

int main(){
    hanoi(5,'A','B','C');
    cout<<::count<<endl;
    return 0;
}