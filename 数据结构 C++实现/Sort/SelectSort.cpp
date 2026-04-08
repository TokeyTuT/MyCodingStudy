#include<iostream>
#include<vector>
void SelectSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0;i < n;i++) {
        int min_idx = i;
        int mn = arr[i];
        for (int j = i + 1;j < n;j++) {
            if (mn > arr[j]) {
                min_idx = j;
                mn = arr[j];
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}
int main() {
    std::vector<int> arr{ 123,14,253,1243,323,53 };
    SelectSort(arr);
    for (int q : arr) {
        std::cout << q << "  ";
    }
    std::cout << std::endl;
}