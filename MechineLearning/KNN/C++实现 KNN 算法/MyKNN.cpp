#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
/*
*
* 用 c++ 实现 KNN 算法 —— 回归 /
* 计算距离默认使用 欧式距离
* 使用 vector 储存数据特征值
*/

// 定义每一个数据点
struct Point {
    std::vector<double> features;   // 特征向量
    double label;                   // 标签值
};

/*
    计算欧式距离
    公式:
        d(p,q) = √(p_k - q_k)^2
*/
double calc_Euclidean_distance(const Point& p1, const Point& p2) {
    auto f1 = p1.features;
    auto f2 = p2.features;


    double dis = 0.0;
    int n = f1.size();
    for (int i = 0;i < n;i++) {
        dis += (f1[i] - f2[i]) * (f1[i] - f2[i]);
    }
    return sqrt(dis);
}

// 比较器
struct CompareDistance {
    bool operator()(const std::pair<double, int>& a, const std::pair<double, int>& b) {
        // C++ 的 priority_queue 默认是最大堆
        return a.first < b.first;
    }
};
int KNearestNeighbor(const std::vector<Point>& train,
    const Point& test, int k) {
    /*
    * train -> 训练数据
    * test -> 测试数据
    * k -> 超参，窗口大小
    */
    // 因为我们要找的是距离最近的，要弹出的元素应该是距离比较远的，所以要用一个大根堆维护 
    std::priority_queue<std::pair<double, int>,
        std::vector<std::pair<double, int>>, CompareDistance> maxHeap;

    for (auto& p : train) {
        double res = calc_Euclidean_distance(p, test);
        maxHeap.push(std::make_pair(res, p.label));

        if (maxHeap.size() > k) {
            maxHeap.pop();
        }

    }

    std::map<int, int> cnt;
    while (!maxHeap.empty()) {
        cnt[maxHeap.top().second]++;
        maxHeap.pop();
    }

    //多数表决
    int majorityClass = -1;
    int maxCount = 0;
    for (const auto& pair : cnt) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            majorityClass = pair.first;
        }
    }

    return majorityClass;
}

int main() {
    std::vector<Point> trainingData = {
        {{1.0, 2.0}, 0},
        {{1.5, 1.8}, 0},
        {{1.0, 0.6}, 0},
        {{5.0, 8.0}, 1},
        {{8.0, 8.0}, 1},
        {{9.0, 11.0}, 1}
    };

    // 准备需要预测的测试数据
    Point testPoint = { {10.0, 10.0}, -1 };

    // 设置 K 值
    int k = 3;

    // 进行 KNN 分类
    int predictedClass = KNearestNeighbor(trainingData, testPoint, k);

    std::cout << "测试点特征: (" << testPoint.features[0] << ", " << testPoint.features[1] << ")" << std::endl;
    std::cout << "预测的类别标签为: " << predictedClass << std::endl;

    return 0;
}