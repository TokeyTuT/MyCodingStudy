#include<iostream>
#include<vector> // 使用 vector 模拟矩阵
using namespace std;
/*
 假设：
 x[m][n] 是特征数据（m个样本，n个特征） 注意，这里的 x 包含了偏置项
 y[m] 是真实值
 w[n] 是权重
 alpha 是学习率
*/

//注：在传入参数的时候请对数据进行标准化或归一化
vector<double> gradientDescent(
    const vector<vector<double>>& x,
    const vector<double>& y,
    int epochs, //迭代次数
    double alpha = 0.01
) {
    int m = x.size(), n = x[0].size();
    // 初始化权重向量 w，初始值为 0
    vector<double> w(n, 0.0);
    for (int ep = 0;ep < epochs;ep++) {
        vector<double> h(m, 0);
        for (int i = 0;i < m;i++) {
            //计算每个样本点的预测值
            for (int j = 0;j < n;j++) {
                h[i] += w[j] * x[i][j];
            }
        }
        // 求每个 w_j 的偏导
        // vector<double> pre_w(n, 0.0);
        for (int j = 0;j < n;j++) {
            double pw = 0.0;
            for (int i = 0;i < m;i++) {
                pw += (h[i] - y[i]) * x[i][j];
            }

            //根据梯度下降法更新数据
            w[j] = w[j] - alpha * (pw / m);
        }
        // // 根据梯度下降规则更新
        // for (int j = 0;j < n;j++) {

        // }
    }
    return w;
}

int main() {
    // 准备测试数据
    // 假设真实的函数关系是: y = 10 + 2*x1 + 3*x2
    // 注意：x矩阵的第一列强行设为 1.0，用于和 w[0] (即截距/偏置) 相乘
    vector<vector<double>> X = {
        {1.0, 1.0, 2.0}, // 对应 y = 10 + 2*1 + 3*2 = 18
        {1.0, 2.0, 1.0}, // 对应 y = 10 + 2*2 + 3*1 = 17
        {1.0, 2.0, 3.0}, // 对应 y = 10 + 2*2 + 3*3 = 23
        {1.0, 3.0, 2.0}, // 对应 y = 10 + 2*3 + 3*2 = 22
        {1.0, 4.0, 4.0}  // 对应 y = 10 + 2*4 + 3*4 = 30
    };

    vector<double> y = { 18.0, 17.0, 23.0, 22.0, 30.0 };

    // 设置超参数
    int epochs = 10000;  // 训练 10000 轮
    double alpha = 0.01; // 学习率
    vector<double> w = gradientDescent(X, y, epochs, alpha);

    // 打印结果，看看模型有没有学到真实的规律 (w0接近10, w1接近2, w2接近3)
    cout << "==== 训练结束 ====" << endl;
    cout << "期望的完美参数: w[0]=10, w[1]=2, w[2]=3" << endl;
    cout << "你代码算出的参数:" << endl;
    for (int i = 0; i < w.size(); i++) {
        cout << "w[" << i << "] = " << w[i] << endl;
    }

    // 随便拿一条数据测试一下预测效果
    cout << "\n==== 预测测试 ====" << endl;
    // 假设输入特征是 x1=3.0, x2=2.0，真实的 y 应该是 22
    double pred_y = w[0] * 1.0 + w[1] * 3.0 + w[2] * 2.0;
    cout << "当输入 x1=3.0, x2=2.0 时:" << endl;
    cout << "真实值应为: 22.0" << endl;
    cout << "模型预测为: " << pred_y << endl;

    return 0;
}
