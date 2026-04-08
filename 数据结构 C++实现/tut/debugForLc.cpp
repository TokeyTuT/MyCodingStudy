#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
using namespace std;
int residuePrefixes(string s) {
    unordered_map<char, int> umap;
    int res = 0;
    int left = 0, n = s.size();
    for (int right = 0;right < n;right++) {
        umap[s[right]]++;
        if ((right + 1) % 3 == umap.size()) {
            res++;
        }
    }
    return res;
}

// int centeredSubarrays(vector<int>& nums) {
//     int res = 0;
//     int n = nums.size();
//     int sum = 0;
//     for (int i = 0; i < n; i++) {
//         int sum = 0;
//         unordered_set<int> uset;
//         for (int j = i; j < n; j++) {
//             sum += nums[j];
//             uset.insert(nums[j]);
//             if (uset.contains(sum)) {
//                 res++;
//             }
//         }
//     }
//     return res;
// }
long long countPairs(vector<string>& words) {
    int n = words.size();
    unordered_map<string, int> umap;
    int m = words[0].size();
    for (string s : words) { // 相当于预处理
        for (int i = 0; i < 26; i++) {
            for (char& c : s) {
                c += 1;
            }
            umap[s]++;
        }
    }
    // 枚举即可
    long long res = 0;
    for (string s : words) {
        res = umap[s] - 1;
    }
    return res;
}
int main() {
    // string s = "aa";
    // cout << residuePrefixes(s) << endl;
    // vector<int> nums{ 2,3 };
    // cout << centeredSubarrays(nums) << endl;
    vector<string> words{ "fusion","layout" };
    cout << countPairs(words) << endl;
    return 0;
}