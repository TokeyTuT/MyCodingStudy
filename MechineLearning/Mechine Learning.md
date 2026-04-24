# 机器学习概论

## 机器学习算法分类

### 有监督学习

*   特点：有特征，有标签。
*   种类：
    *   连续  —— 回归
    *   不连续  —— 分类



### 无监督学习

*   特点：有特征，无标签
*   种类： 聚类，样本间有相似性



### 半监督学习

*   特点：有特征，部分有标签



## 强化学习

略





## 机器学习建模流程

*   获取数据：获取经验数据、图像数据、文本数据……
*   数据基本处理：数据缺失值处理、异常值处理……
*   特征工程：特征提取、特征预处理、特征降维
*   机器学习：线性回归、逻辑回归、决策树、GBDT
*   模型评估： 回归评测指标、分类评测指标、聚类评测指标



## 特征工程概览

*   含义：利用专业背景知识和技巧处理数据，让模型效果更好
*   内容：
    *   特征提取
    *   特征预处理
    *   特征降维
    *   特征选择
    *   特征组合

## 模型拟合问题

*   拟合：在机器学习领域，用来表示模型对样本点的拟合情况
    *   欠拟合：模型在训练集，测试集表现不好 —— 模型过于简单
    *   过拟合：训练集好、测试集不好 —— 模型太过复杂，数据不纯，训练量小
*   泛化：模型在新的数据集（非训练数据）上表现好坏的能力，简单来说就是评估模型的拟合能力



# KNN —— K 近邻算法

*   解决问题：分类问题、回归问题
*   算法思想：如果一个样本在特征空间中的 K 个最相似的样本大多数据摸一个类别，则该样本也属于这个类别
*   相似性：见下面的距离算法

*   K 值对结果的影响：
    *   K 过小，容易受到异常点的影响，容易发生过拟合
    *   K 过大，会受到样本均衡量的问题，欠拟合



## 流程

![image-20260413163145604](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260413163145604.png)



## KNN算法API

### 分类问题 API

分为下面这四步骤：

```python
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
```



### 回归问题API

分为下面的四步：

```python
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
```



## 常见距离算法

*   欧式距离 —— 两点在空间中的距离
	
    >   假设空间中有两个点 $P(p_1,p_2,...,p_n)$ 及 $Q(q_1,q_2,...,q_n)$，他们的欧式距离如下
   	>   $$
    >   d(p,q) = \sqrt{\sum_{k=1}^{n}(p_k-q_{k})}
    >   $$
    >   在机器学习中，我们可以把每一行看成一个点多维的点 *R*,它的维度就是所有特征值的列数
    >
    >   再根据另一个点算出与 *R* 的欧式距离即可
    
*   曼哈顿距离

    >   也叫城市街区距离，曼哈顿城市的特点：横平竖直
    >
    >   n维空间中有两个点 $P(p_1,p_2,...,p_n)$ 及 $Q(q_1,q_2,...,q_n)$，他们的曼哈顿距离如下:
    >   $$
    >   d(P,Q)=\sum^{n}_{i=1}\left|p_i-q_i\right|
    >   $$

*   切比雪夫距离

    >   国际象棋中，国王可以直行、横行、斜行，所以国王走一步可以移动到相邻八个放个中的任意一个，那么求国王从$(x_1,y_1)$到$(x_2,y_2)$最少需要走多少步？—— 这就是切比雪夫距离
    >
    >   n维空间中有两个点 $P(p_1,p_2,...,p_n)$ 及 $Q(q_1,q_2,...,q_n)$，他们的切比雪夫距离如下:
    >   $$
    >   d(P,Q)=\max(\left|p_i-q_i\right|)
    >   $$

*   闵可夫斯基距离 —— 闵氏距离

    >   n维空间中有两个点 $P(p_1,p_2,...,p_n)$ 及 $Q(q_1,q_2,...,q_n)$，他们的闵氏距离如下:
    >   $$
    >   d(P,Q)=\sqrt[r]{\sum_{k=1}^{n}\left|p_i-q_i\right|^r}
    >   $$
    >   



## 特征值的预处理

### 归一化

把原始数据映射到*[min,max]* (默认[0,1])之间
$$
X'=\frac {x - min} {max - min}
               \\
               \\
               X''=X'(max - min) + min
$$

*   $X'$–>基于公式算出来的结果

*   $X''$–>最终的结果
*   *min*–> 区间最小值
*   *max*–> 区间最大值

	**弊端**：
	容易受到最大值和最小值的影响，所以他一般用于处理 **小数据集**



```python
# 导包
from sklearn.preprocessing import MinMaxScaler
# 准备数据
x_train = [[10,20],[20,30],[30,40]]
# 对元数据进行归一化操作
transfer = MinMaxScaler(feature_range=(3,5))
# 对元数据进行归一化操作
x_train = transfer.fit_transform(x_train)

print(x_train)
```



### 数据标准化

通过对原始数据进行标准化，转换为均值为 0 和标准差为 1 的标准正态分布的的数据
$$
X'=\frac{x-mean}{\sigma}
$$
*mean*为当前列的平均值，*σ* 代表当前列的标准差

场景： 
	适用于 **大数据集** 的处理



```python
from sklearn.preprocessing import StandardScaler

x_train = [[10,20],[20,30],[30,40],[40,50]]

# 创建标准化化对象
transfer = StandardScaler()

# 对数据集进行标准化操作
x_train = transfer.fit_transform(x_train)

print(x_train)

print(transfer.mean_) # 平均值
print(transfer.var_) #  方差
print(transfer.scale_) # 标准差
```

## 案例 —— 鸢尾花分析

*   如何评价一个模型的好坏？ 

    >   通常有两种方式：
    >
    >   1.   直接评分：通过调用模型自带的函数`estimator.score(x_test,y_test)` 返回一个百分数
    >   2.   间接评分：同意调用`from sklearn.metrics import accuracy_score`，里面有一个库函数`accuary_score(y_test,y_pre)`，注意，这里的`y_pre`是自己评估后的变量，这个函数不会自动帮你用模型预测。

```python
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
	# 两种方法没有明显差异，但是建议使用下面模型进行训练
if __name__ == '__main__':
    dm_iris()
```

## 交叉验证和网格搜索

#### 交叉验证

交叉验证是一种**数据的分割方**法，将数据划分为 n 份拿一次作为测试集、其他n - 1 份做训练集

验证原理：

*   第一次：把第一份数据作为验证集，其他数据做训练
*   第二次：把第二份数据作为验证集，其他数据做训练
*   ……
*   若使用训练集 + 验证集多次评估模型，取平均值作为模型得分

#### 网格搜索

KNN算法中，我们需要确定*k*，这种需要人工确定的参数叫做超参。

*   为什么？
    *   模型有很多超参数，其能力存在很大的差异。需要手动产生很多超参数组合，来训练模型
    *   每组超参数都采用**交叉验证**评估，最后选出最优参数建立模型
*   网格搜索是模型调参的有力工具，用来寻找最优超参数的工具

### API

![image-20260423184611139](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260423184611139.png)

```python
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split, GridSearchCV  # 网格搜索 + 交叉验证
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

iris_data = load_iris()
x_train,x_test,y_train,y_test = train_test_split(iris_data.data,iris_data.target,test_size=0.2)

# 特征标准化
sc = StandardScaler()
x_train = sc.fit_transform(x_train)
x_test = sc.transform(x_test)

# 模型的训练
# 创建 KNN 分类对象
estimator = KNeighborsClassifier()
# 定义字典记录超参数可能出现的值
param_dict = [{'n_neighbors':[i for i in range(1,11)]}]
# 交叉验证，网格搜索
estimator = GridSearchCV(estimator, # 模型对象
                         param_dict, # 超参数字典
                         cv=4) # 交叉验证折数

estimator.fit(x_train,y_train)
print(f"最优评分:{estimator.best_score_}")
print(f"最优超参组合:{estimator.best_params_}")
print(f"最优的估计器对象:{estimator.best_estimator_}")
print(f"具体的交叉验证结果:{estimator.cv_results_}")

```

>   但是这种方法得到的结果也也不是很准确，以上面的鸢尾花KNN算法为例，这里的最优超参受到折数、random_state、test_size 等影响

## 案例 —— 手写数字识别

*   数据介绍：

    *   数据文件 *train.csv* 以及 *test.csv*,包含了从0～9的手绘数据的灰度图像
    *   每个图片高 28 像素、宽 28 像素，一共784个像素
    *   每个像素取值范围为[0,255]，取值越大意味着颜色越深
    *   训练数据集( *train.csv* )一共785列
        *   第一列为标签，为该列对应的手写数字。
        *   其余列代表该图像的像素值
    *   训练集中的特征名称均有*pixel*前缀，后缀数字([0,783])代表了该像素的序号

*   如何保存模型？

    >   在实际开发中，我们不可能每次运行时都构建一次模型，这太浪费性能了，所以我们要将训练的模型保存下来，以便下次直接调用。

    *   借用 Python 中的库`joblib`

        ```python
        # 模型保存
        # 参数1 ： 模型对象
        # 参数2 ： 文件路径
        joblib.dump(estimator,'./_my_knn_model/手写数字识别.pkl')
        # pkl ———— Python(Pandas) 独有的文件类型
        ```
* 使用模型
  
  >   既然我们已经训练了模型，那么我们如何通过我们训练的模型来识别图片中的手写数字呢？

  

```python
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
```

