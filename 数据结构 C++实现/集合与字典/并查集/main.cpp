#define MAX_SIZE 50
class MyUnionFindSet
{
private:
    int parent[MAX_SIZE];

public:
    MyUnionFindSet(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
        }
    }
    int Find(int x)
    {
        return (parent[x] < 0) ? x : parent[x] = Find(parent[x]);
    }
    void Union(int x, int y)
    {
        int rootx = Find(x);
        int rooty = Find(y);
        if (rootx != rooty)
        {
            if(parent[rootx]<parent[rooty]){
                parent[rooty] = rootx;
            }
            else if(parent[rootx]>parent[rooty]){
                parent[rootx] = rooty;
            }
            else{
                parent[rooty] = rootx;
                parent[rootx]--;
            }
        }
    }
};