#include<iostream>
#include<vector>
void InsertSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1;i < n;i++) {
        int temp = arr[i];
        int left = 0, right = i;
        while (left < right) {  //[left,right)
            int mid = left + (right - left) / 2; //防止溢出
            if (arr[mid] >= temp) right = mid;
            else  left = mid + 1;
        }
        //left+1就是我们要插入的位置
        int j;
        for (j = i;j > left;j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}

int main() {
    std::vector<int> arr{ 12,532,31,51,623,39,27 };
    InsertSort(arr);
    for (int a : arr) {
        std::cout << a << "  ";
    }
    std::cout << "\n";
    return 0;
}