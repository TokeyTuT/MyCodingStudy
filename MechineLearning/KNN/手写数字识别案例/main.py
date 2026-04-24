import matplotlib.pyplot as plt
import pandas as pd
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import joblib # 保存模型

def train_data():
    # 定义函数，训练模型，保存模型
    df = pd.read_csv('data/手写数字识别.csv')
    # 数据预处理
    x = df.iloc[:,1:] # 特征列
    y = df.iloc[:,0] # 标签列

    # 对特征列进行 归一化
    x = x / 255

    # 拆分数据为测试集和训练集 —— 要保证数据均匀
    x_train,x_test,y_train,y_test = train_test_split(x,y,
                                                     test_size=0.2,
                                                     random_state=114514,
                                                     stratify=y) # 参考数据，保证数据均匀
    estimator = KNeighborsClassifier(n_neighbors=3)
    # 模型训练
    estimator.fit(x_train,y_train)

    # 模型评估
    print(f"准确率:{accuracy_score(y_test,estimator.predict(x_test))}")

    # 模型保存
    joblib.dump(estimator,'./_my_knn_model/手写数字识别.pkl') # pkl ———— Python(Pandas) 独有的文件类型
    print("模型保存成功")


# 使用模型读取图片
def use_model():
    # 读取图片
    img = plt.imread('data/demo.png') # 注意，这里的 img 会自动归一化，下面不需要再跑归一化了
    # print(img)
    # 绘制图片
    plt.imshow(img)
    plt.show()

    # 加载模型
    knn = joblib.load('./_my_knn_model/手写数字识别.pkl')

    # 预测图片
    y_read = knn.predict(img.reshape(1,-1))  # 28 * 28 -> 784
    # reshape(1,-1)等同于 1，784，适合在不知道多少列的情况下使用
    print(y_read)
if __name__ == '__main__':
    # train_data()
    use_model()