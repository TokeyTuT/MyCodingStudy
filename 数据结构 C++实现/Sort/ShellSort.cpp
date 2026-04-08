#include<iostream>
#include<vector>
void ShellSort(std::vector<int>& arr) {
    int n = arr.size();
    int gap = n / 2;
    while (gap) {
        for (int i = gap;i < n;i++) {
            int temp = arr[i];
            int j = i - gap;
            //向左边的组类看
            while (j >= 0 && arr[j] > temp) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j+gap] = temp;
        }
        gap /= 2;
    }
}
int main() {
    std::vector<int> arr{ 12,2141,325,3634,6346,342 };
    ShellSort(arr);
    for (int a : arr) {
        std::cout << a << "  ";
    }
    std::cout << std::endl;
}