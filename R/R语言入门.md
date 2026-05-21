# R语言入门

## 介绍

R 语言（R Programming Language）是一种专为**统计计算**、**数据分析**和**图形绘制**而设计的开源编程语言和软件环境。自 20 世纪 90 年代诞生以来，它已成为数据科学家、统计学家和学术研究人员的首选工具之一。R 语言是一门**解释性语言**

R 与 Python：

>   *   **R**：如果你侧重于**纯统计分析**、**学术研究**或**复杂绘图**，R 通常更直观。它的语法是为“分析数据”而设计的，而非“开发软件”。
>
>   *   **Python**：如果你需要将模型集成到大型软件系统中，或者进行大规模的深度学习开发，Python 的通用性更强。



## 常见方法

### 平均值

*   使用 mean 方法即可，传入参数可以是一维数组，也可以是一个矩阵

### 正态分布

对于正态分布$\mathbf X \sim N(\mu, \sigma^2)$

如果我们想要用 R 计算指定的面积，我们可以用到 `pnorm` 方法:

```R
# lower.tail = TRUE 计算左尾面积，FALSE 计算右尾面积
pnorm(1.54,mean=0,sd=1,lower.tail=FALSE) # P(Z > 1.54)

# P(0 < Z < 1)
pnorm(1,mean=0,sd=1，lower.tail=TRUE) - pnorm(0,mean=0,sd=1,lower.tail=TRUE)
 
d1 = pnorm(c(0,1),mean=0,sd=1)
d1[2] - d1[1]
# P(1 < Z < 2.43)
d2 = pnorm(c(1,2.43),mean=0,sd=1)
d2[2] - d2[1]
```

其中：

*   mean: 表示平均数  $\mu$
*   sd:表示标准差 $\sigma$
*   lower.tail:表示计算左侧面积还是右侧面积 —— TRUE 计算左尾面积，FLASE计算右尾面积

相反，如果我们想有$P(Z < a)$ ，想求a的值，我们可以用到 qnorm 方法：

```R
# if P(Z < a) = 0.8790 find value of a
qnorm(0.8790,mean=0,sd=1,lower.tail=TRUE)


# if P(Z > a) = 0.3783
qnorm(0.3783,mean=0,sd=1,lower.tail=FALSE)

# P(a < Z < 1) = P(0 <  Z < 1) - P(a < Z) = 0.3333
d1 = pnorm(c(0,1),mean=0,sd=1)
tmp = d1[2] - d1[1] - 0.3333
qnorm(tmp,mean=0,sd=1,lower.tail=FALSE)
```

>   注：这里的示例用的都是$\mathbf X \sim N(0, 1)$，如果要传入别的正态分布，改变mean和sd的参数即可



## 数组

*   ==R中的索引都是从1开始访问的==
*   对于一维数组，R需要在数组初始化前加一个标识符*c*
```R
a = c(1,2,3,4)
```

*   对于二维数组，R需要在初始化前加一个标识符matrix
```R
data = matrix(c(1,2,3,4,5,6,7,8),2,4)
```

>   *   参数一需要传入一个一维数组，代表所有需要传入的数据
>
>   *   参数二、三代表了这个矩阵的形状，(row,colomn)
>
>   *   这个矩阵按列优先开始填充数据,上述矩阵应该为:$\begin{bmatrix}1 &5\\2 & 6\\3&7\\4&8\end{bmatrix}$
>
>       如果我们想要访问，它的方法和Pandas类似：
>
>       ```R
>       # R 的索引访问和切片和 Pandas 相同
>       data = matrix(c(1,2,3,4,5,6,7,8),4,2)
>       data[2,3] 
>       data[1,] # 第一行所有数据
>       data[,1] # 第一列所有数据
>       ```
