from sklearn.linear_model import LinearRegression
from matplotlib import pyplot as plt
import numpy as np
from sklearn.metrics import mean_squared_error


def dm1():
    # 准备数据
    # 指定随机种子
    np.random.seed(115)

    x = np.random.uniform(-3, 3, 100)  # 模拟生成一百个数据
    y = 0.5 ** x ** 2 + x + 2 + np.random.normal(0, 1, 100)  # 添加噪声 e

    estimator = LinearRegression()
    estimator.fit(x.reshape(-1, 1), y)

    y_predict = estimator.predict(x.reshape(-1, 1))

    # 模型评估
    print(f'均方误差{mean_squared_error(y, y_predict)}')

    # 绘制散点图
    plt.scatter(x, y)
    plt.plot(x, y_predict, color='r')  # 以折线图的形式模拟预测值
    plt.show()


def dm2():
    # 1. 准备数据
    np.random.seed(115)
    x = np.random.uniform(-3, 3, 100)
    # 模拟一个二次方程关系：y = 0.5x^2 + x + 2 + 噪声
    y = 0.5 * x ** 2 + x + 2 + np.random.normal(0, 1, 100)

    # 2. 增加特征维度 (重要：LinearRegression 要求输入是二维矩阵)
    # 使用 np.column_stack 将 x 和 x^2 组合，形状变为 (100, 2)
    x_features = np.column_stack([x, x ** 2])

    # 3. 训练模型
    estimator = LinearRegression()
    estimator.fit(x_features, y)

    # 4. 预测
    y_predict = estimator.predict(x_features)

    # 5. 模型评估
    print(f'均方误差 (MSE): {mean_squared_error(y, y_predict):.4f}')

    # 6. 绘制结果
    plt.scatter(x, y, alpha=0.6, label='Original Data')

    # 注意：为了让绘出的回归线平滑，需要根据 x 的大小对预测值进行排序
    sort_idx = np.argsort(x)
    plt.plot(x[sort_idx], y_predict[sort_idx], color='r', label='Polynomial Fit')

    plt.title("Polynomial Regression (Degree 2)")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()

def dm3():
    # 1. 准备数据
    np.random.seed(115)
    x = np.random.uniform(-3, 3, 100)
    # 模拟一个二次方程关系：y = 0.5x^2 + x + 2 + 噪声
    y = 0.5 * x ** 2 + x + 2 + np.random.normal(0, 1, 100)

    # 2. 增加特征维度 (重要：LinearRegression 要求输入是二维矩阵)
    # 使用 np.column_stack 将 x 和 x^2 组合，形状变为 (100, 2)
    x_features = np.column_stack([x, x ** 2,x ** 3,x ** 4,x ** 5,x ** 6,x ** 7,x ** 8,x ** 9,x ** 10,x ** 11,x ** 12,x ** 13,x ** 14,x ** 15,x ** 16,x ** 17,x ** 18,x ** 19,x ** 20])

    # 3. 训练模型
    estimator = LinearRegression()
    estimator.fit(x_features, y)

    # 4. 预测
    y_predict = estimator.predict(x_features)

    # 5. 模型评估
    print(f'均方误差 (MSE): {mean_squared_error(y, y_predict):.4f}')

    # 6. 绘制结果
    plt.scatter(x, y, alpha=0.6, label='Original Data')

    # 注意：为了让绘出的回归线平滑，需要根据 x 的大小对预测值进行排序
    sort_idx = np.argsort(x)
    plt.plot(x[sort_idx], y_predict[sort_idx], color='r', label='Polynomial Fit')

    plt.title("Polynomial Regression (Degree 2)")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()



if __name__ == '__main__':
    # dm1()
    # dm2()
    dm3()