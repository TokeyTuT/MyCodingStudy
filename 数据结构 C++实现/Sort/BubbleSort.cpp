#include<vector>
#include<iostream>
void BubbleSort(std::vector<int>& arr, int pattern) {
    int n = arr.size();
    if (pattern == 0) {//从小到大
        for (int i = 0;i < n - 1;i++) { // n-1 防止下面arr[i+1]越界
            for (int j = 0;j < n - i - 1;j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    if (pattern == 1) {//从大到小
        for (int i = 0;i < n - 1;i++) {
            for (int j = 0;j < n - i - 1;j++) {
                if (arr[j] < arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

int main() {
    std::vector<int> vec{ 12, 32, 35, 1214, 25, 4, 7, 4, 75, 5 };
    BubbleSort(vec, 1);
    for (int n : vec) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    BubbleSort(vec, 0);
    for (int n : vec) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}