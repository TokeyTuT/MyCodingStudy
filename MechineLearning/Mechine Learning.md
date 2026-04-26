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



# 线性回归

*   一元线性回归：只有一列特征 
    $$
    y = wx + b
    $$
    ​	其中*w* 称为权重，*b* 称为偏置

*   多元线性回归：含有多列特征
    $$
    y = w_1x_1 + w_2x_2 + ...+w_nx_n + b
    $$
    如果用矩阵向量表示这个回归函数
    $$
    % 优化后的排版
    \begin{align}
        \text{权重向量：} \quad \mathbf{w} &= \begin{pmatrix} w_1 & w_2 & \dots & w_n \end{pmatrix}^\top \\
        \text{特征向量：} \quad \mathbf{x} &= \begin{pmatrix} x_1 & x_2 & \dots & x_n \end{pmatrix}^\top \\
        \text{回归函数：} \quad y &= \mathbf{w}^\top \mathbf{x} + b
    \end{align}
    $$
    

## 线性回归API

基本操作

```python
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
```



上面的数据可以拟合出多个回归函数，那么最终应取哪一条呢？

![image-20260425000117542](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260425000117542.png)

由此，我们引出了**损失函数**，用来描述真实值和预测值的关系

## 损失函数

*   误差 = 预测值 - 误差值
*   损失函数：用于描述每个**样本点** 和 其**预测值**之间的关系，让损失函数最小，就是让**误差和**最小，线性回归效率越高，评估效果越好

对于一线性回归，我们可以猜测其损失函数为：
$$
Lose(w,b)=\sum_{i=1}^{n}(wx_i+b-y_i)^2
$$
注意，误差有可能是负的，所以我们考虑平方相加

如果我们将上面的函数其展开，我们可以得到一个二次函数：
$$
F(x) = Lose(w,b)=px^2+qx+r
\\
$$
要让损失函数最小，也就是让$F(x)$ 最小，通过简单的运算，可以求到 *w* 的最优值

>   **注：**这只是一种思路，并不是严谨推导方法，推导过程见下



上面的损失函数用了***均方误差***(Mean-Square Error,MSE)：

*   均方误差：

$$
J(w,b) = \frac 1m\sum_{i=1}^m(h(x_i)-y_i)^2
$$

除了均方误差外，我们还有***平均绝对值误差***(Mean Absolute Error,MAE)

*   平均绝对值误差：

    ​	
    $$
    J(w,b)=\frac1m\sum_{i=1}^m|h(x_i) - y_i|
    $$

### 正规方程法

#### 一元线性回归

对于一元线性回归函数:
$$
J(w,b) = \frac 1m\sum_{i=1}^m(h(x_i)-y_i)^2 = \frac 1m\sum_{i=1}^m(wx_i+b-y_i)^2
$$
我们的目的是求$J(w,b)$的极小值，由于 $w,b$均为变量，所以我们对函数进行求偏导：

*   对 $w$ 求偏导，整理得:
    $$
    \frac{\partial J(w,b)}{\partial w}=w\sum_{i=1}^m x_i^2+b\sum_{i=1}^mx_i-\sum_{i=1}^mx_iy_i
    $$

*   对 $b$ 求偏导，整理得：
    $$
    \frac {\partial J(w,b)}{\partial b}=k\sum_{i=1}^mx_i+mb-\sum_{i=1}^my_i
    $$

由拉格朗日乘数法：
$$
\begin{cases}
\frac{\partial J(w,b)}{\partial w}=0\\
\frac{\partial J(w,b)}{\partial b}=0
\end{cases}
$$
方程实际上是一个二元一次方程，解除解$(w',b')$即可，这一对解就是一元线性回归的模型方程



#### 多元线性回归

在多元线性回归中，对于第 $i$ 个样本：
$$
\hat y_i=\sum_{j=1}^m w_jx_{ij} + b
$$
第$i$ 个样本的损失:
$$
\varepsilon_i=(\hat y_i - y_i)^2=\left[\left(\sum_{j=1}^m w_jx_{ij} + b\right)-y_i\right]
$$
进一步，我们可以导出多元线性回归的损失函数:
$$
J(w)=\sum_{i=1}^n\sum_{j=1}^m (w_jx_{ij} + b-y_i)
$$
我们可以把 $w_i$ 的集合看做向量$w^T$
$$
w=(w_1,w_2,\dots,w_m)
$$
剩下的推导暂时pass，因为我还没学完线代



### 梯度下降法

*   什么是梯度

    *   单变量函数中，梯度就是某一点的切线斜率：有方向：函数增长最快的方向
    *   多变量函数中，梯度就是某一个点的偏导数；有方向：偏导数分量的向量方向

*   梯度下降公式:

    循环迭代求当前点的梯度，更新当前的权重参数
    $$
    \theta_{i+1}=\theta_{i}-\alpha\frac {\partial}{\partial\theta_i}J(\theta)
    $$
    其中：

    *   $\alpha$ 为学习率（步长）不能太大，也不能太小，机器学习中：$[0.001,0.01]$
    *   梯度是上升最快的方向，我们需要的是下降最快的方向，所以需要加负号

![image-20260425163633317](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260425163633317.png)

![image-20260425163825868](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260425163825868.png)

*   有关学习率：
    *   学习率太小：下降速率太慢
    *   学习率太大：容易错过最低点、产生下降过程中的震荡、甚至梯度爆炸

但是，我们不可能一开始就知道损失函数，那么我们如何确定函数呢？

---

以二元线性回归为例：

假设我们有 $m$ 个样本数据。对于第 $i$ 个样本，特征为 $x_1^{(i)}$ 和 $x_2^{(i)}$，真实值为 $y^{(i)}$。我们的多元线性回归模型（预测函数 $h$）为：
$$
h(x^{(i)}) = w_1 x_1^{(i)} + w_2 x_2^{(i)} + b
$$
由此我们可以导出损失函数$J$，为了后续求导时抵消掉平方项产生的系数 2，我们通常会在前面乘上一个 $\frac{1}{2}$：
$$
J(w_1, w_2, b) = \frac{1}{2m} \sum_{i=1}^{m} (h(x^{(i)}) - y^{(i)})^2
$$
现在，我们的目标就是：找到一组 $(w_1, w_2, b)$，使得函数 $J(w_1, w_2, b)$ 的值达到全局最小。

**对 $w_1$ 求偏导：**
$$
\frac{\partial J}{\partial w_1} = \frac{1}{m} \sum_{i=1}^{m} (h(x^{(i)}) - y^{(i)}) \cdot x_1^{(i)}
$$
**对 $w_2$ 求偏导：**

$$
\frac{\partial J}{\partial w_2} = \frac{1}{m} \sum_{i=1}^{m} (h(x^{(i)}) - y^{(i)}) \cdot x_2^{(i)}
$$

**对 $b$ 求偏导：**
$$
\frac{\partial J}{\partial b} = \frac{1}{m} \sum_{i=1}^{m} (h(x^{(i)}) - y^{(i)})
$$
拿到每一组变量的偏导之后，根据梯度下降的规则：$\theta_{i+1}=\theta_{i}-\alpha\frac {\partial}{\partial\theta_i}J(\theta)$

每一次迭代的更新规则如下：

$$
w_1 := w_1 - \alpha \frac{\partial J}{\partial w_1}
$$
$$
w_2 := w_2 - \alpha \frac{\partial J}{\partial w_2}
$$
$$
b := b - \alpha \frac{\partial J}{\partial b}
$$

初始时，我们不知道$(w_1,w_2,b)$，我们可以任取一个合理的数即可，这对元组会在迭代之后自动收敛

>   我们考虑这个案例：
>
>   假设我们想要预测一个大学生的 **GPA**（目标变量 $y$）。影响 GPA 的因素有很多，我们挑出两个最关键的特征（这就是“多元”的由来）：
>
>   -   $x_1$：每周复习专业课的小时数
>   -   $x_2$：每周在 LeetCode 上刷题的数量
>
>   我们假设它们之间是一个“线性”的关系，也就是可以用一个公式来表达：
>   $$
>   y_{预测} = w_1 x_1 + w_2 x_2 + b
>   $$
>   这符合上面的二元线性回归，现在我们对上面的求到的偏导进行验证。
>
>   假设我们有两个学生的数据（样本量 $m=2$）：
>
>   -   **样本 1**：$x_1^{(1)}=2$（复习 2 小时），$x_2^{(1)}=1$（刷 1 题），真实 GPA $y^{(1)}=3.5$
>   -   **样本 2**：$x_1^{(2)}=3$（复习 3 小时），$x_2^{(2)}=2$（刷 2 题），真实 GPA $y^{(2)}=4.0$
>
>   我们依然使用瞎猜的初始参数和学习率 $\alpha$：
>
>   -   $w_1 = 0.5$
>   -   $w_2 = 0.5$
>   -   $b = 1.0$
>   -   $\alpha = 0.1$
>
>   ------
>
>   ### 代入偏导数公式
>
>   现在，我们把这 2 个样本的误差和特征值，代入到上一回提到的偏导数（梯度）公式中
>
>   **计算 $w_1$ 的偏导数：**
>
>   $$\begin{align*} \frac{\partial J}{\partial w_1} = -1.75 \end{align*}$$
>
>   **计算 $w_2$ 的偏导数：**
>
>   $$\begin{align*} \frac{\partial J}{\partial w_2} &= -1.0 \end{align*}$$
>
>   **计算 $b$ 的偏导数：**
>
>   *(注意：$b$ 后面没有特征 $x$，所以直接对误差求和取平均即可)*
>
>   $$\begin{align*} \frac{\partial J}{\partial b}  &= -0.75 \end{align*}$$
>
>   **偏导数的意义：** 这里算出来的 $-1.75$、$-1.0$ 和 $-0.75$ 就是当前的梯度向量。它综合了两个样本的情况，告诉我们：为了让整体误差变小，$w_1$ 需要向上调整的力度最大，其次是 $w_2$，最后是 $b$。
>
>   ------
>
>   ### 更新参数
>
>   利用梯度下降的更新规则 $w := w - \alpha \frac{\partial J}{\partial w}$，代入学习率 $0.1$：
>
>   -   $w_1 := 0.5 - 0.1 \times (-1.75) = 0.5 + 0.175 = \mathbf{0.675}$
>   -   $w_2 := 0.5 - 0.1 \times (-1.0) = 0.5 + 0.1 = \mathbf{0.6}$
>   -   $b := 1.0 - 0.1 \times (-0.75) = 1.0 + 0.075 = \mathbf{1.075}$
>
>   ------
>
>   ###  检验效果
>
>   我们用刚刚更新好的新参数 $(0.675, 0.6, 1.075)$，重新对这两个样本预测一次，看看误差是不是真的变小了：
>
>   **对于样本 1 (真实值 3.5)：**
>
>   -   新预测值：$0.675 \times 2 + 0.6 \times 1 + 1.075 = 1.35 + 0.6 + 1.075 = \mathbf{3.025}$
>   -   绝对误差从 $1.0$ 缩小到了 $0.475$。
>
>   **对于样本 2 (真实值 4.0)：**
>
>   -   新预测值：$0.675 \times 3 + 0.6 \times 2 + 1.075 = 2.025 + 1.2 + 1.075 = \mathbf{4.3}$
>   -   绝对误差从 $0.5$ 缩小到了 $0.3$。
>
>   **结论：** 经过仅仅一次严谨的偏导数计算和参数更新，**所有样本的预测误差都显著缩小了**。在实际应用中，计算机就是通过高效的矩阵运算，把这套流程在一秒钟内跑上几万次，最终找到那组让误差无限趋近于最小值的最优解。



---

于是，我们可以导出多元线性回归方程的梯度下降法求解过程：

如果我们有 $n$ 个特征值，一共有 $m$ 个样本数的情况下

为了计算方便、让过程具有统一性，我们定义偏差 $b$，那一项代表$1*b$，记$x^{(0)} = 1$

对于**第 $i$ 个样本**，它的预测公式为：

$$
h(x^{(i)}) = w_1 x_1^{(i)} + w_2 x_2^{(i)} + \dots + w_n x_n^{(i)} + b
$$
对应的误差函数：
$$
J(w_0, w_1, \dots, w_n) = \frac{1}{2m} \sum_{i=1}^{m} (h(x^{(i)}) - y^{(i)})^2
$$

如果我们对$w_j$求偏导
$$
\frac{\partial J}{\partial w_j}=\frac 1m\sum_{i=1}^m(h(x^{(i)})-y^{(i)})x^{(i)}_j
$$
根据梯度下降的更新规则：
$$
w_j:=w_j-\alpha\frac{\partial}{\partial w_j}J(w_0, w_1, \dots, w_n)
$$
将样本代入，不断迭代，就可以求到对应最优解。



## 模型评估方法

*   均方误差(Mean Squared Error MSE)：
   $$
   MSE=\frac 1n\sum_{i=1}^n (y_i - \hat y_i)^2
   $$

    
   
*   平均绝对值误差(Mean Absolute Error MAE)：
   $$
   MAE =\frac1n\sum_{i=1}^n|y_i-\hat y_i|
   $$

*   均方根误差(Root Mean Squered Error RMSE):
   $$
   RMSE=\sqrt{\frac 1n\sum_{i=1}^n (y_i - \hat y_i)^2}
   $$
   

绝大多数情况下：$RMSE > MAE$，因为 RMSE 有一个平方项，会放大误差

*   MAE 和 RMSE 都能对模型进行评估
*   RMSE 对异常值更敏感



## API



![image-20260426001433338](https://cdn.jsdelivr.net/gh/TokeyTuT/my-image-storage@main/img/image-20260426001433338.png)
