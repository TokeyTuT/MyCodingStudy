import numpy as np
import pandas as pd
from sklearn.linear_model import LogisticRegression # 逻辑回归模型
from sklearn.model_selection import train_test_split # 测试集和训练集划分
from sklearn.metrics import accuracy_score # 模型评估
from sklearn.preprocessing import StandardScaler

# 加载数据
data = pd.read_csv('./data/breast-cancer-wisconsin.csv')

# 数据预处理
# data.info()
data = data[data['Bare Nuclei'] != '?'] # 删除异常值
data['Bare Nuclei'] = data['Bare Nuclei'].astype('int32') # 改变数据类型
# data.info()

# 特征工程
x = data.iloc[:,1:-1]  # 切片是左闭右开
y = data.iloc[:,-1]

# 划分数据集
x_train,x_test,y_train,y_test = train_test_split(x,y,test_size=0.2,random_state=1)

# 对训练集和数据集进行标准化
transform = StandardScaler()
x_train = transform.fit_transform(x_train)
x_test = transform.transform(x_test)

# 模型训练
estimator = LogisticRegression()
estimator.fit(x_train,y_train)

# 模型预测
y_pre = estimator.predict(x_test)
print(y_pre)

# 模型预测
print(f"训练前评估{estimator.score(x_test,y_test)}")
print(f"训练后评估{accuracy_score(y_test,y_pre)}")
