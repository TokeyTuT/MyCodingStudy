#define MAX_SIZE 19
class Hash
{
private:
    int arr[MAX_SIZE];
public:
    //  初始化
    Hash(){
        for (int i = 0; i < MAX_SIZE;i++){
            arr[i] = __INT_MAX__;
        }
    }
    //哈希函数
    int hash(int x) { return x % 19; }
    //插入
    void insert(int x){
        int h = hash(x);
        int count = 1;
        while (arr[h] != __INT_MAX__&&arr[h]!=__INT_MAX__-1)
        {
            h = hash(x+count);
            count++;
        }
        arr[h] = x;
    }
    //删除
    bool Del(int x){
        int h = hash(x);
        int count;
        while (arr[h] != __INT_MAX__ && arr[h] != __INT_MAX__ - 1)
        {
            if (arr[h]==x){
                arr[h] = __INT_MAX__ - 1;
                return true;
            }
                h = hash(x + count);
            count++;
        }
        if (arr[h] == __INT_MAX__ && arr[h] == __INT_MAX__ - 1)
        {
            return false;
        }
    }
    bool Search(int x)
    {
        int h = hash(x);
        int count;
        while (arr[h] != __INT_MAX__ && arr[h] != __INT_MAX__ - 1)
        {
            if (arr[h] == x)
            {
                return false;
            }
            h = hash(x + count);
            count++;
        }
        if (arr[h] != __INT_MAX__ && arr[h] != __INT_MAX__ - 1)
        {
            arr[h] = x;
            return true;
        }
    }
};