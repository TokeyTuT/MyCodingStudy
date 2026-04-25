from sklearn.linear_model import LinearRegression
from sqlalchemy.engine import cursor


# 线性回归 API 入门
def demo1_linear_regression():
    x_train = [[160],[166],[172],[174],[180]]
    y_train = [56.3,60.6,65.1,68.5,75]
    x_test = [[176]]

    estimator = LinearRegression()
    # 训练模型
    estimator.fit(x_train,y_train)
    # 查看斜率 coef、截距 intercept
    print(estimator.coef_)
    print(estimator.intercept_)

    # 模型预测
    y_pre = estimator.predict(x_test)
    print(y_pre)


if __name__ == '__main__':
    demo1_linear_regression()