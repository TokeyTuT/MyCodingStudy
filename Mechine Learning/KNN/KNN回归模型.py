# 导包
from sklearn.neighbors import KNeighborsRegressor # knn算法回归模型

# 准备数据集
x_train = [[0,0,1],[1,1,0],[3,10,10],[1,1,1],[2,2,1],[3,3,1],[4,4,1],[5,5,1],[6,6,1],[7,7,1],[8,8,1],[9,9,1]]
y_train = [0,0.09,1,0.07,0.10,0.09,0.11,0.15,0.2,0.3,0.4,0.5]

x_test = [[3,11,8]]
# 创建回归模型对象
estimator = KNeighborsRegressor(n_neighbors=3)

# 模型训练
estimator.fit(x_train,y_train)

# 模型预测
y_test = estimator.predict(x_test)

print(y_test)