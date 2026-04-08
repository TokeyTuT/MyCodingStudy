#include<vector>
#include<numeric>
#include<iostream>
//二维形式
int getMaxValue(const std::vector<int>& value, const std::vector<int>& weight, int bagweight) {
    std::vector<std::vector<int>>  dp(weight.size(), std::vector<int>(bagweight + 1, 0));
    //初始化
    for (int j = 1;j <= bagweight;j++) {
        if (j < weight[0]) continue;
        dp[0][j] = value[0];
    }
    //遍历 i表示物品下标 j表示背包重量
    for (int i = 1;i < weight.size();i++) {
        for (int j = 0;j <= bagweight;j++) {
            if (weight[i] > j) dp[i][j] = dp[i - 1][j];//放不下 直接继承上一行
            else dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        }
    }
    // 打印dp数组
    for (int i = 0;i < weight.size();i++) {
        for (int j = 0;j <= bagweight;j++) {
            std::cout << dp[i][j] << "\t";
        }
        std::cout << "\n";
    }
    return dp[weight.size() - 1][bagweight];
}

//一维形式
int getMaxValue2(const std::vector<int>& value, const std::vector<int>& weight, int bagweight) {
    std::vector<int> dp(bagweight + 1, 0);
    for (int i = 0;i < weight.size();i++) {
        for (int j = bagweight;j >= 0;j--) {
            if (j < weight[i]) continue;
            dp[j] = std::max(dp[j], dp[j - weight[i]] + value[i]);
        }
        for (int i : dp) {
            std::cout << i << "\t";
        }
        std::cout << "\n";
    }
    //debug
    // for (int i : dp) {
    //     std::cout << i << "\t";
    // }
    // std::cout << "\n";
    return dp.back();
}
int main() {
    std::vector<int> value = { 15,20,40 };
    std::vector<int> weight = { 1,2,4 };
    int bagweight = 4;
    std::cout << getMaxValue(value, weight, bagweight) << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << getMaxValue2(value, weight, bagweight) << std::endl;
    return 0;
}