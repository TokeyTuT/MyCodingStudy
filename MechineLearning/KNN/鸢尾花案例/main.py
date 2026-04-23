from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split    # 分割数据集的
from sklearn.neighbors import KNeighborsClassifier      # KNN 算法
from sklearn.preprocessing import StandardScaler        # 数据标准化的
from sklearn.metrics import accuracy_score              # 模型评估 ，测评模型正确性

from KNN_分类思路 import estimator


def dm_iris():
    # 获取基本数据集
    iris_data = load_iris()

    # 将数据集拆成训练集和测试集
    x_train,x_test,y_train,y_test = train_test_split(iris_data.data,iris_data.target,test_size=0.2)

    # 数据集预处理，标准化
    transformer = StandardScaler() # 创建标准化对象
    # fit_transform —— 先训练再转换，一般用于处理训练集
    x_train = transformer.fit_transform(x_train)
    # 重复进行标准化时，常用 transform 一般对测试集使用
    x_test = transformer.transform(x_test)

    # 机器学习 —— KNN
    # 创建模型对象
    estimator = KNeighborsClassifier(n_neighbors=3)
    estimator.fit(x_train,y_train)

    # 预测结果
    y_pre = estimator.predict(x_test)
    print(y_pre)

    # 自定义测试集
    my_data = [[7.8,2.1,3.9,1.6]]
    # 注意这里自己的数据集也要进行标准化
    my_data = transformer.transform(my_data)
    my_pre_proba = estimator.predict_proba(my_data)
    print(f"模型预测各分类的概率为:{my_pre_proba}")

    # 模型评估
    # 1.直接评分，基于训练集的特征，测试集的标签
    print(f"模型评分:{estimator.score(x_test,y_test)}")

    # 2.基于测试集标签和预测结果进行评分
    print(f"模型评分:{accuracy_score(y_test,y_pre)}")

if __name__ == '__main__':
    dm_iris()