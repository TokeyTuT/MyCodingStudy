# from sklearn.datasets import load_boston
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import SGDRegressor
from sklearn.metrics import mean_squared_error, mean_absolute_error, root_mean_squared_error
import pandas as pd
import numpy as np

data_url = "http://lib.stat.cmu.edu/datasets/boston"
raw_df = pd.read_csv(data_url, sep="\\s+", skiprows=22, header=None)
data = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :2]])
target = raw_df.values[1::2, 2]

# print(f"形状:{data.shape}")
# print(f"标签:{target.shape}")

# 数据预处理
x_train, x_test, y_train, y_test = (
    train_test_split(data, target, test_size=0.2, random_state=12))

# 特征工程
scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

# 模型训练
# 创建线性回归 —— 随机梯度下降 模型对象
estimator = SGDRegressor(max_iter=1000, # 迭代次数
                         fit_intercept=True, # 使用偏置
                         learning_rate='constant', # 学习率  —— constant 代表学习率不变
                         eta0=0.01) # 学习率初始值
estimator.fit(x_train, y_train)

# print(f"权重：{estimator.coef_}")
# print(f"截距：{estimator.intercept_}")
# 预测结果
y_pre = estimator.predict(x_test)
# 评估模型
print(f"均方误差为:{mean_squared_error(y_test, y_pre)}")
print(f"平均绝对误差为:{mean_absolute_error(y_test, y_pre)}")
print(f"均方根误差为:{root_mean_squared_error(y_test, y_pre)}")
