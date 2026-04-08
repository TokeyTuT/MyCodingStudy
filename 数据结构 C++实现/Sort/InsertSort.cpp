#include<vector>
#include<iostream>

void InsertSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1;i < n;i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        //循环结束时 arr[j]<=temp 所以应该要在arr[j+1]处填充
        arr[j + 1] = temp;
    }
}
int main() {
    std::vector<int> arr{ 1,23,35,44,53,63,4,1,124 };
    InsertSort(arr);
    for (int a : arr) {
        std::cout << a << "  ";
    }
    std::cout << std::endl;
}