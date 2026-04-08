#include <iostream>
#include <vector>
#include <algorithm>
// #include<cmatch>
class Solution
{
public:
    int sum = 0;
    std::vector<std::vector<int>> result;
    std::vector<int> temp;
    void Combination(std::vector<int> Arr, int target, std::vector<int> Used, int starIndex)
    {
        if (sum > target)
            return;
        if (sum == target)
        {
            result.push_back(temp);
            return;
        }
        for (int i = starIndex; i < Arr.size(); i++)
        {
            if (i > 1 && Arr[i - 1] == Arr[i] && Used[i - 1] == 0)
                continue;
            if (Used[i] == 1)
                continue;
            temp.push_back(Arr[i]);
            sum += Arr[i];
            Used[i] = 1;
            Combination(Arr, target, Used, i + 1);
            // 弹出
            sum -= Arr[i];
            temp.pop_back();
        }
    }
    void Run()
    {
        std::vector<int> Arr = {1, 4, 5, 12, 6, 7, 3, 23, 1, 5, 3, 2, 1, 4, 2, 1, 14, 6, 8};
        sort(Arr.begin(), Arr.end());
        int target = 10;
        std::vector<int> Used(Arr.size(), 0);
        this->Combination(Arr, target, Used, 0);
        for (std::vector<std::vector<int>>::iterator it = result.begin(); it != result.end(); it++)
        {
            for (const int i : *it)
            {
                std::cout << i << "  ";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Solution sl;
    sl.Run();
    return 0;
}
