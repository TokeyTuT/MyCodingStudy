# 导包
from sklearn.neighbors import KNeighborsClassifier

# 准备数据集(测试集 和 训练集)
x_train = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [8, 8], [9, 9], [10, 10]] # 训练集的特征
y_train = [0, 0, 0, 0, 0, 1, 1, 1, 1] # 训练集的标签

x_test = [[7,7]] # 测试集的特征数据

# 创建 KNN分类模型对象 , n_neighbors=3代表 k = 3
estimator = KNeighborsClassifier(n_neighbors=3)

# 模型训练
estimator.fit(x_train, y_train)

# 模型预测
y_test = estimator.predict(x_test)

print(y_test)