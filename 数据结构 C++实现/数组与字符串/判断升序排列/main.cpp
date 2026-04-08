#include <iostream>
#include <vector>

bool isAscendingOrder(std::vector<int> Arr, int startIndex)
{
    if (startIndex == Arr.size() - 1)
    {
        return true;
    }
    if (isAscendingOrder(Arr, startIndex + 1))
        return Arr[startIndex] < Arr[startIndex + 1];
    return false;
}

int main()
{
    std::vector<int> v = {1, 2, 4};
    std::cout << isAscendingOrder(v, 0) << std::endl;
    return 0;
}