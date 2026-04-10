>   D![image-20260314184815984](https://p.ipic.vip/b6vkf2.png)
>





## DDL —— Data Definition Language

DDL 可以看作是是为我们的数据打**“地基”**，凡是涉及**定义**某种东西的结构、存在或不存在的操作，都属于DDL

*   对数据库 —— 建立数据库、分配码表（utf-8 、 gbk……）、删掉数据库
*   对表 —— 设计表头、删掉整个表



### 操作数据库

#### CREATE

创建数据库

```mysql
# 创建数据库
CREATE DATABASE 数据库名称;

# 当数据库不存在时，创建数据库
CREATE DATABASE IF NOT EXISTS 数据库名称;

# 创建数据库并制定码表 默认 utf-8
CREATE DATABASE 数据库名称 character set（缩写为charset） ‘gbk’;
```

#### SHOW

```mysql
# 显示已有数据库 ，注意 database后面有个 s
SHOW DATABASES  
```

#### USE

用于切换数据库

```mysql
# 使用指定数据库
USE 数据库名称;
```

#### DROP

```mysql
# 删除数据库
# 实际上工程应用中不要删除数据库！
DROP 删除数据库的名称;
```

#### ALTER

修改数据库的码表

```mysql
ALTER DATABASE 数据库名称 CHARSET ‘utf-8’
```



`select database()` 查看当前用的是哪个数据库



### 操作数据表



#### CREATE

建表

```mysql
CREATE TABLE 表名(
	字段名 1 数据类型 [约束],
    字段名 2 数据类型 [约束],
    字段名 3 数据类型 [约束]
);

CREATE TABLE Users(
	id INT PRIMARY KEY,  	-- 整数类型，设为主键 （唯一标识）
	username VERCHAR(50),	-- 可变字符类型，最长 50 个字符
	age INT,				-- 整数类型
	created_at TIMESTAMP	-- 时间戳类型,DATESTAMP
);
```

#### ALTER

修改表结构 —— 比如需要给学生表加一个表头、或者把姓”名字“字段改长点。

以**Student**为例：

```mysql
ALTER TABLE Student ADD major VARCHAR(50);	-- 添加列

ALTER TABLE Student MODIFY name VARCHAR(50)；-- 修改属性

ALTER TABLE Student RENAME COLUMN gpa TO score;	-- 重命名列

ALTER TABLE Student DROP COLUMN name; 	-- 删除列
```

#### DROP

删除表

```mysql
DROP TABLE Student;
```

**提示：** 实际开发中，通常会用 `DROP TABLE IF EXISTS 表名;`，防止因为表不存在而导致脚本运行报错。



####  TRUNCATE

清空表

```mysql
TRUNCATE TABLE Student
```





### DESC

查看表结构

```mysql
desc 表名
```



此外 *desc*，还是一个降序的关键词，详细见下



### MySQL 中的数据类型

*   整数：tinyint、smallint、mediumint、int、bigint
*   小数：decimal、double、float
*   字符串：varchar、char、text
*   日期时间：date、time、datetime

**注意**：

*   **`DECIMAL(M, D)`**: **精度固定**。比如 `DECIMAL(10, 2)` 表示总共 10 位，小数点后 2 位。这是存 GPA 或金钱的最安全选择。
*   不定长*varchar*是不会补‘ ’、定长 *char*是会自动对齐‘ ’，补长度
*   *text* ——  存长篇大论（如博客文章）。它不在表的主记录里存，而是存在外面，性能略低。
*   关于日期时间
    -   **`DATE`**: 只有年月日（`2026-03-15`）。
    -   **`TIME`**: 只有时间（`18:30:00`）。
    -   **`DATETIME`**: 年月日时分秒。
    -   **`TIMESTAMP`**: 带时区的时间戳，范围到 2038 年。

 

### SQL 中的数据约束

数据约束可以看作是对数据的**强制规则**

常见约束：

#### ① 非空约束 (`NOT NULL`)

-   **作用：** 强制这一列必须填东西，不能留白。
-   **场景：** 学生的姓名、账号密码。
-   **代码：** `name VARCHAR(50) NOT NULL`

#### ② 唯一约束 (`UNIQUE`)

-   **作用：** 这一列的值不能重复，但可以为空（除非同时也设了 `NOT NULL`）。
-   **场景：** 手机号、身份证号、邮箱。
-   **代码：** `email VARCHAR(100) UNIQUE`

#### ③ 主键约束 (`PRIMARY KEY`)

-   **作用：** **`NOT NULL` + `UNIQUE` 的组合拳**。它是一行数据的唯一身份标识，一张表只能有一个主键。
-   **场景：** 学号、订单号。
-   **代码：** `id INT PRIMARY KEY`

#### ④ 默认约束 (`DEFAULT`)

-   **作用：** 如果用户没填，数据库就自动填上你设定的默认值。
-   **场景：** 注册时间（默认当前）、性别（默认“未知”）。
-   **代码：** `status TINYINT DEFAULT 0`

#### ⑤ 外键约束 (`FOREIGN KEY`)

-   **作用：** 建立表与表之间的联系，确保引用的数据在另一张表里确实存在。
-   **场景：** “成绩表”里的“学号”必须在“学生表”里能找到。
-   **代码：** `FOREIGN KEY (stu_id) REFERENCES Students(id)`





## DML —— Data Manipulation Language

如果说 DDL 是在操作表结构，那么 DML 就是在操作表里面每一行数据，它的作用就是增(**INSERT**)、删(**DELETE**)、改(**UPDATE**)



### INSERT

*   **标准写法（指定列名）：** 这种写法最稳妥，即使表结构增加了新列（只要新列有**默认值**），你的代码也不会报错。

    ```mysql
    INSERT INTO Students (name, age, gpa) VALUES ('张三', 20, 3.8);
    ```
* **一次插多行：** 在数据科学中，为了提高效率，我们经常批量插入。

    ```mysql
    INSERT INTO Students (name, age, gpa) VALUES 
    ('李四', 21, 3.5),
    ('王五', 22, 3.9),
    ('赵六', 20, 3.6);
    ```

### UPDATE

⚠️注意：这里是数据库最容易出 BUG 的地方

如果你执行 `UPDATE Students SET age = 18;`，全校学生的年龄都会变成 18 岁。所以，`UPDATE` 几乎永远要带着 **`WHERE`** 子句。

-   **修改特定数据：**

    ```mysql
    UPDATE Students 
    SET gpa = 4.0, age = 21 
    WHERE name = '张三'; -- 只有张三被修改了
    ```



### DELETE

同样，**`DELETE` 也必须死死盯住 `WHERE`**。 —— 主键自增序列不清零

-   **删除特定行：**

    ```mysql
    DELETE FROM Students [WHERE id = 1];
    ```

    如果不加 where 条件，默认删除所有表数据

注意：

*   DELETE`：像是在 Excel 里**选中一行按退格键**。它是一条条删，如果你在 Java 里开启了事务，删错了还能 Rollback（回滚）回来。`

*   `TRUNCATE`：像是**直接格式化这张表**。它是 DDL 级别，速度极快，删完就真没了。

    ```mysql
    DELETE FROM Users;
    # 从删除前最后一个主键开始，比如删除前主键为 10，下一次插入从 11 开始
    INSERT INTO Users (xxx,xxx,xxx);
    TRUNCATE Users;
    # 直接从主键 1 开始，相当于直接把表撕了重新写
    INSERT INTO Users (xxx,xxx,xxx);
    ```

    

### TRUNCATE

清空表数据，主键自增序列清零



### 查看表数据

*   **查看所有数据（慎用）：** 如果表非常大，这条命令会让屏幕刷屏很久。

```mysql
SELECT * FROM 表名;
```

*   **只看前几行（最推荐）：** 在 macOS 开发时，这是最常用的。用 `LIMIT` 限制返回数量。

```mysql
SELECT * FROM 表名 LIMIT 10;
```

*   **只看特定的列：**

```mysql
SELECT id, name, email FROM 表名;
```



## 备份数据表

1.   如果备份表不存在，那么我们直接 CREATE TABLE 备份的表名 `SELECT FROM 原表名 [where 过滤条件]`
2.   如果备份表存在，我们直接`INSERT INTO 备份表名 SELECT * FROM 原表名 [where 过滤条件]`





## DQL —— Data Query Language

DQL 只有一个核心方法 ***SELECT*** —— 当时它的组合千变万化





### 单表查询

总的格式：

```mysql
select
	[distinct] 列名 [as 别名],列名 [as 别名] ...
from
	数据表名
where
	组前筛选
group by
	分组字段
having 
	组后筛选
order by 
	排序的列 1 [asc | desc],排序的列 2
limit
	起始索引,数据条数;
```



#### 简单查询

* 查询指定类型 —— 如果要查询所有的列，有一个语法糖 `select * form 表名`

    ```mysql
    select pid,pname,…… from 表名
    ```

* 别名查询 —— 在显示表的时候按照起的别名显示列名，as 可以省略

    ```mysql
    select
    	pname as 商品名,
    	price as 价格
    from 
    	表名
    ```

    最终显示效果如下：
    ![image-20260316163003475](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260316163003475.png)==**请注意：这里只是临时显示成别名，实际不会改变表的每一列抬头名。**==

* 如果我们要给商品进行数学操作，操作过后要把有一步 ”as …… “操作，列的抬头会显示异常，比如这里如果不 as price，抬头就会显示成 `price + 10`

![image-20260316163311243](https://p.ipic.vip/1kc5zp.png)

#### 条件查询

`SELECT 列名 FROM 表名 WHERE 筛选条件`

![image-20260316163904629](https://p.ipic.vip/u9034c.png)

注意： 

*   between…and…两边都是闭区间
*   <>  和 != 相同



#### 排序查询

`select 列名 from 表名 order by 排序列 1[asc | desc],排序列 2 [asc | desc]…;`

注意 ***order by***语法要写在最后，但是在 *limit* 前面

*   *asc*  —— *ascending* 升序，不写默认升序
*   desc —— *descending* 降序
*   排序规则按照指定的列序，如果排序列 1 顺序后，有值相同的，那么在按照规则二排序



#### 聚合函数

聚合函数实际上是以**列**为进行操作的

语法 ： `SELECT [聚合函数] FROM 表名`

![image-20260316165940862](https://p.ipic.vip/o57z2j.png)

**细节**：

*   如果 *count(col)* 对象统计条数的时候有 *null* 会跳过不计数，也就是不会统计到真正的条目数
    *   ![image-20260316170602323](https://p.ipic.vip/d4r3fx.png)



#### 分组查询

先分组、再聚合



![image-20260316183616054](https://p.ipic.vip/b6x2ds.png)



例子：

![image-20260316184343586](https://p.ipic.vip/q86rqo.png)



#### 组后筛选

组后筛选就是在 group by 语句（分组之后）进行筛选，常用关建字 *having*

*   和 *where* 的区别：
    *   *where* 用于组前筛，*having* 用于组后筛选
    *   *having* 后面可以接聚合函数



#### 去重查询

把相同的数据去除掉，只保留一份

*distinct*关键字

```mysql
select
	distinct 字段 1,字段 2……
from xxx
```

**注意**：*distinct* 后面接的字段是看做一个整体，只有这一个**整体不一样才会去重**

去重思路 2 —— 通过分组去重 —— 最常用，大数据适合

```mysql
select 
	字段 1,字段 2……
from 
	xxx
group by
	字段 1,字段 2…… （注意要一一对应）;
```



#### 分页查询

考虑这样一个场景，当我们预览淘宝网页时，搜索一个商品，结果会有很多，但是对于服务器还是客户端的浏览器来说，不可能一次性全部加载所有的商品价格和图像，否则这个会造成两者压力很大，所以通常前端会设计一个“**翻页查找**”的功能，一页一页的查找，每次只用加载一页的数据，这个实际上就是就体现了**分页查询**的思想。

分页查询利用关键字 **limit** ，语法 ***limit 起始索引 数据条数***

*   **起始索引**：在 SQL 中，每条数据都有一个索引，索引从 0 开始

```mysql
select * limit 0,3 	-- 0~2，第一页
select * limit 3,3 	-- 3~5，第二页
……
```

*   每页的起始索引 = （每页的页数 - 1）* 数据条数

*   数据总条数  = count(主键列)
*   总页数 =（数据总条数 + 每页数据条数 - 1）// 每页数据条数



总体的步骤可以由下面这一个例子体现：

![image-20260316203512644](https://p.ipic.vip/rrt1xm.png)



### 多表查询

在实际开发中，通常需要用到多张表 —— 用户表、商品表、订单表……

多表关系：一对一、多对多、一对多



*   一对多 —— 一个部门对应多个员工：
    *   A 表一行对应 B 表多行 —— 教师表对应学生
    *   B 表一行对应 A 表一行
*   多对多 —— 学生和选课：
    *   A 表一行对应 B 表多行
    *   B 表一行对应 A 表多行
*   一对一 —— 一家公司只能对一一个法人：
    *   A 表一行对应 B 表一行
    *   B 表一行对应 A 表一行

#### 建表

*   一对多如何建表？

    >   在多的一方新建一**外键列**，去关联一的一方的**主键列**
    >
    >   在多表关系中有外键列的表叫做**外表/从表**，有主键列的表叫做**内表/主表**
    >
    >   ==外表的外键列不能出现主表没有的主键==

*   多对多如何建表？

    >   多对多建表：我们要用一个中间表充当外表，其余两个充当主表
    >
    >   ![image-20260316205628988](https://p.ipic.vip/ttac54.png)

*   对于一对一的表 —— 我们通常只要将两个表合二唯一即可

#### 外键和外键约束

![image-20260316205902274](https://p.ipic.vip/b8knec.png)

特点 & 缺点

![image-20260316210010309](https://p.ipic.vip/ewfquy.png)

在实际开发中，在研发中很少使用外键约束，在实际上线时才会加上外键约束



![image-20260316210110531](https://p.ipic.vip/lzl59x.png)

##### 添加外键约束

*   方式一，建表时添加：

    >   格式：`constraint [外键约束名] foreign key(外键列名) references (主键列名)`
    >
    >
    >   删除外键约束：`drop table 表名 foreign key (外键约束名)`

*   方式二，建表后添加：

    >   格式：`alter table 表名 add [外键约束名] forgein key(外键列名) references(主键列名)`
    >
    >   注意，建表后，添加约束时，一定要考虑要加入的外键列内的数据时候都在主表中主键存在！！！



#### 内连接

我们可以把内连接看作两个表的**交集**

![image-20260316214325583](https://p.ipic.vip/smb7dd.png)

*   格式 1  —— 隐式内连接：`select * from 表 1，表 2 where 关联条件`
*   格式 2 —— 显式连接： `select * from 表1 inner join 表 2 on 关联条件` —— 推荐

![image-20260316214639690](https://p.ipic.vip/2kg06u.png)

#### 左外连接、右外连接

![image-20260316215319402](https://p.ipic.vip/u23oh1.png)

#### 满外连接

![image-20260316215436260](https://p.ipic.vip/4gdn2y.png)

注意 union 本身后面自带了 *distinct*，所以会去重，如果不想去重，那么只要 ***union all***



#### 子查询

![image-20260316220008032](https://p.ipic.vip/navkgp.png)



#### when case

如果我们想要在查询的时候添加一列数据，那么使用 when case 是很方便的语法

![image-20260316220512116](https://p.ipic.vip/j4e1c1.png)





## 窗口函数

MySQL 在 8.0 以上版本支持了窗口函数

窗口语法可以这样理解，就是把整个表按组分成多个窗口，再通过窗口函数对这个窗口进行操作：排序，求和……



结构：

```mysql
函数名（列名） OVER PARTITION BY 分组列 ORDER BY 排序窗口 窗口范围语句
```

*   **`PARTITION BY`**：类似于 `GROUP BY`，将数据分区（比如按部门、按年份），不写默认对整个表操作

    **`ORDER BY`**：决定了窗口内数据的计算顺序（对排名函数至关重要）。



#### 实际案例演示

假设有一张 `sales` 表：

| **user_id** | **sale_date** | **amount** |
| ----------- | ------------- | ---------- |
| A           | 2026-01-01    | 100        |
| A           | 2026-01-02    | 150        |
| B           | 2026-01-01    | 200        |

```mysql
SELECT 
    user_id, 
    sale_date, 
    amount,
    SUM(amount) OVER (PARTITION BY user_id ORDER BY sale_date) as cumulative_amount
FROM sales;
```

**结果分析：**

对于用户 A，第一行显示 100，第二行显示 250（100+150）。如果用 `GROUP BY`，你只能得到 A 的总数 250，而无法看到每一天的明细。



####  常见的窗口函数

##### 1. 排名函数 (Ranking Functions)

这是窗口函数最经典的应用场景，用于解决“各部门薪资前三名”或“学生成绩排名”等问题。

-   **`ROW_NUMBER()`**（最常用）：
    -   **特点**：唯一且连续。即使数值相同，排名也**不重复**（1, 2, 3, 4）。
    -   **场景**：去重、取每个分组的第一条记录。
-   **`RANK()`**：
    -   **特点**：跳跃排序。数值相同时排名相同，下一位会“**跳号**”（1, 1, 3, 4）。
    -   **场景**：传统的竞赛排名。
-   **`DENSE_RANK()`**：
    -   **特点**：连续排序。数值相同时排名相同，下一位**不跳号**（1, 1, 2, 3）。
    -   **场景**：希望排名连续的业务统计。

------

##### 2. 偏移函数 (Value/Lead-Lag Functions)

用于获取“前一行”或“后一行”的数据，是进行**环比、同比分析**的核心工具。

-   **`LAG(column, n)`**：
    -   **作用**：获取当前行之**前**第 $n$ 行的数据。
    -   **场景**：计算今日销售额与昨日的差值（环比）。
-   **`LEAD(column, n)`**：
    -   **作用**：获取当前行之**后**第 $n$ 行的数据。
    -   **场景**：预测或查看下一阶段的目标值。

------

##### 3. 聚合窗口函数 (Aggregate Window Functions)

将传统的聚合函数与 `OVER()` 结合，实现累加或计算占比。

-   **`SUM() OVER()`**：
    -   **场景**：计算**累计流水**（Running Total）。例如：展示每天销售额的同时，计算截止到当天的总销售额。
-   **`AVG() OVER()`**：
    -   **场景**：计算**移动平均**或**对比均值**。例如：计算当前员工薪资与部门平均薪资的差额。
-   **`COUNT() OVER()`**：
    -   **场景**：在明细行中直接显示该分组的总人数。





## 日期函数

| **分类**     | **函数名**        | **语法示例**                                                 | **实际输出 (假设当前 2026-03-22)** | **说明**                 |
| ------------ | ----------------- | ------------------------------------------------------------ | ---------------------------------- | ------------------------ |
| **获取当前** | `NOW()`           | `SELECT NOW();`                                              | `2026-03-22 18:10:00`              | 返回当前日期 + 时间      |
|              | `CURDATE()`       | `SELECT CURDATE();`                                          | `2026-03-22`                       | 只返回当前日期           |
|              | `CURTIME()`       | `SELECT CURTIME();`                                          | `18:10:00`                         | 只返回当前时间           |
| **成分提取** | `YEAR()`          | `YEAR('2026-03-22')`                                         | `2026`                             | 提取年份                 |
|              | `MONTH()`         | `MONTH('2026-03-22')`                                        | `3`                                | 提取月份 (1-12)          |
|              | `DAY()`           | `DAY('2026-03-22')`                                          | `22`                               | 提取天数                 |
|              | `DATE()`          | `DATE(NOW())`                                                | `2026-03-22`                       | 丢弃时间部分，只留日期   |
| **日期加减** | `DATE_ADD()`      | `DATE_ADD('2026-03-22', INTERVAL 1 DAY)`                     | `2026-03-23`                       | **最推荐**的加法方式     |
|              | `DATE_SUB()`      | `DATE_SUB('2026-03-22', INTERVAL 1 MONTH)`                   | `2026-02-22`                       | 减法，也可以用加负数代替 |
|              | `LAST_DAY()`      | `LAST_DAY('2024-02-01')`                                     | `2024-02-29`                       | 返回该月最后一天的日期   |
| **差值计算** | `DATEDIFF()`      | `DATEDIFF('2026-03-25', '2026-03-22')`                       | `3`                                | 计算天数差 (前减后)      |
|              | `TIMESTAMPDIFF()` | `TIMESTAMPDIFF(HOUR, '2026-03-22 10:00', '2026-03-22 12:00')` | `2`                                | 灵活计算秒/分/时/天差    |
| **格式转换** | `DATE_FORMAT()`   | `DATE_FORMAT(NOW(), '%Y年%m月')`                             | `2026年03月`                       | 将日期转为漂亮字符串     |
|              | `STR_TO_DATE()`   | `STR_TO_DATE('22-03-2026', '%d-%m-%Y')`                      | `2026-03-22`                       | 将字符串解析为标准日期   |

