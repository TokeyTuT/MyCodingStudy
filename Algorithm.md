-   如果答案和题目有单调性，考虑二分答案 —— 枚举






# 注释区

[^1]: 这里的二叉搜索树和正常定义略有不同
[^2]: 这是官方题解，不会超时，我自己手写的在下面，但是超时了。
[^3]: 笔记中的二进制位数范围规定为4位
[^4]:   `0 ^ n = 0`  、 `n ^ n = 0 `



# 算法基本概念
算法五要素：
* 有穷性
* 确切性
* 输入
* 输出
* 可行性

算法设计原则：
*   正确性
*   可读性
*   健壮性
*   高效率和低存储量

# 一些提示

关于力扣平台刷题技巧

有时候一些刷表题（最典型的就是预处理质数）我们需要预处理一些数据，使得所有测试用例只跑一遍代码即可，加快代码速度，下面的语法是符合力扣 oj 评判的。

**C++**

```c++
static int init = [](){
    //编写预处理代码：比如说预处理前 1000 个质数
    //……
    
    return 0；
}();//最后的括号不能省
class Solution{
	//……
}
```

**Java**

```java
class Solution{
    //static int[] target = new int[X];
	static{
		//编写预处理代码
    };
}
```



# 基础算法/基础数论

## 一、模运算

模运算通常用于算法试题中得到特别大的数据时对结果取模，通常有一个·、标准写法:`int res = (a + MOD)%MOD`加上MOD再取模就是为了防止出现负数模。

*   加减的模运算  —— $(a ± b + MOD) % MOD$

*   乘法 —— $a * b % MOD$

*   除法

    *   关于除法，除法比较特殊，要用到乘法逆元运算，建议直接记公式

        >   a / b  取模之后为  —— $a * qpow(b, MOD - 2, MOD) % MOD$，其中 *qpow*代表 9^MOD-2^,最后一个参数 MOD 代表计算快速幂时每次需要模的数，**并且（MOD 是质数且 b 不是 MOD 的倍数）**



## 二、快速幂

如何快速计算 *pow(a,b)* ? 传统的方法就是一直乘，时间复杂度是*O(b)*，如果位数一多，显然会变慢，有没有算法能把计算幂的速度优化到*O(log n)* 呢？

<img src="https://pic.leetcode.cn/1728623430-RNGDEK-lc50-3-c.png" alt="lc50-3-c.png" style="zoom: 25%;" />

```c++
class Solution {
public:
    double myPow(double x, int N) {
        double ans = 1;
        long long n = N;
        //如果是指数是负数，可以转换
        if(n < 0){
            n = - n;
            x = 1 / x;
        }
        while(n){
            //从高到底枚举 n 的每个比特位
            if(n & 1){
                ans *= x;
            }
            x *= x;
            n>>=1;
        }
        return ans;
    }
};
```

注：请注意，如果 n 很大，主要要对每一步取模

力扣***[3855. 给定范围内 K 位数字之和](https://leetcode.cn/problems/sum-of-k-digit-numbers-in-a-range/description/)***



## 三、GCD / LCM

### 最大公约数

*   定义：两个数 \(a,b\) 的最大公约数是能同时整除它们的最大正整数，记为 \(\gcd(a,b)\)。

*   核心算法：欧几里得算法（辗转相除法）


>   公式：
    >
    >   \(\gcd(a,b)=\gcd(b,a\bmod b)\)
    >
    >   终止条件：
    >
    >   \(\gcd(a,0)=a\)
    >
    >   示例：
    >
    >   \(\gcd(12,18)=\gcd(18,12)=\gcd(12,6)=\gcd(6,0)=6\)

*   算法实现

```C++
template<typename T>
T gcd (T a,T b){
    if(b == 0) return a;
    else return gcd(b,a % b);
}
```

### 最小公倍数

-   公式：\(\text{lcm}(a,b)=\frac{a\times b}{\gcd(a,b)}\)

-   注意：计算时先算 GCD 再乘除，避免溢出

-   实现

```C++
int lcm(int a,int b){
	return a*b / gcd(a,b);
}    
```

## 四、取整函数写法

对于一个数 $x = \frac a b$  其中，a 、b均为正整数

*   如果我们对$x$向下取整，显然$\lfloor \frac a b \rfloor $直接就是`a/b` *(cpp)*
*   如果我们对$x$向上取整,$\lceil \frac a b \rceil$ 通常用 ⌊a-1/b⌋+1 *(cpp)* `(a-1)/b + 1`

## 五、四舍五入的写法

我们需要用到 *cmath*库中的*round*方法，具体方法如下。

*   我们要从*double*、*float*类型的数据直接转到 *int*类型，直接用`round(target)`即可
*   我们要指定四舍五入小数点后几位（这里以后三位为例），我们可以 `round(target * 1000) / 1000.0` 即可

*注释*：如果我们要指定打印小数点后几位，我们可以调用*iomanip*这个库，具体写法:

​				`cout << setprecision(3) << round(res * 1000) / 1000.0 << endl;`

#  位

## 一、二进制

### 基础

对于C++、Java等语言，一般有`int`，`long`这些类型，分别代表的二进制位数有32位，64位二进制数。



对于无符号整数：

*   32位能表示 0~2^32^-1 的整数范围
*   64位能表示 0～2^64^-1的整数范围

但是，我们所说的`int`、`long`等数据类型都是有符号整数类型，如果想要无符号数据类型 ，要在数据前面加一个`unsigned`关键字*（对于C++而言）*

那么什么叫做有符号整数呢？

顾名思义，其实就是带有负号的，他的范围类型包含了负数。



对于符号整数类型：

*   32位能表示 - 2^31^~2^31^-1 的整数范围
*   64位能表示 - 2^63^~2^63^-1 的整数范围

**为什么最高次项会少一位呢？**



### 十进制负数的二进制表示方法[^3]

对于一个十进制负数 `- a`，将它转为二进制负数的方法遵循以下这几步：

1.   对`- a`**取绝对值** 得到 a，把 a 用二进制表示出来
2.   对 a 这个二进制进行**减1**的操作，得到一个新的二进制
3.   讲这个新的二进制进行**按位取反**的操作，就是这个负数的二进制表示方法

比如：计算 -5 的二进制

>   1.   -5的绝对为 5，二进制表示为 `0011`
>   2.   对这个二进制减1 得到 `0010`
>   3.   对这个新的二进制按位取反，得到 `1101`

对比 5 的二进制 0011 我们发现，负数的标识是第一个前缀是否为0或者1。我们牺牲了一个二进制位数，取而代之的换来负数的表示。这里我们也可以解释的通，为什么有符号型整数表示的数最高位次少了1，就是因为我们把前缀贡献给了负数标识。

反过来 二进制负数转十进制，只要对这个二进制**按位取反**，然后再**加1**就行了

>   1.   1101 (按位取反)—>0010 *（前缀为1，代表是负数）*
>   2.   0010 + 1 ==  0011 —> 5 ——> -5



## 二、位运算

### 1. 按位取反 ——   “`~`”

所谓的按位取反，就是在二进制每位进行*取反*的操作：

>   *   1 变为 0
>   *   0 变为 1

通常，对于一个负数 a，我们只要`int b = ~ a + 1` 就可以得到 a的绝对值

但是，我们发现一个问题：负数的最小值，也就是 -2^31^对应正数无法用二进制表示出来，因为  INT_MAX = 2^31^-1。因此对INT_MIN进行上述操作还是它自己。

>   这样理解也行 -8 对应二进制为 1000 –>(按位取反) 0111–>(加一） —>1000 （还是他自己）

### 2. 加

与十进制类似，对于二进制，我们同样遵循 ***进位*** 这个操作，对于溢出位数的 1 我们直接舍去就行

（1） 正数 + 正数

>   对于 2 + 3
>
>   ![image-20251220184256561](https://p.ipic.vip/w9ydcu.png)
>
>    **0101**对应的数为 5 没问题

（2）负数 + 正数

>   ![image-20251220185104534](https://p.ipic.vip/uebb7o.png)

（3）负数 + 负数

>   ![image-20251220185512476](https://p.ipic.vip/9qdgfq.png)

通过这三个例子我们发现，无论是负数，还是正数运算，我们都只要遵循同一套运算法则就可以了，所以这也是为什么前人设计如此复杂的负数转变机制，目的就是为了让 + 这个最最基础的运算效率尽可能拉到最高，因为位运算是计算机最底层的东西，这个运算效率影响到整个计算机运算体系。

### 3. 或、与、异或运算*（ |  &  ^）*

1.   或运算

     ```c++
     int a = 0b1001;
     int b = 0b0010;
     PrintBinary(a | b);  // 0b1011 只要有一个为1就保存
     ```

2.   与运算

     ```c++
     int c = 0b0011;
     int d = 0b1101;
     PrinyBinaryu(a & b); // 0b0001 当两个同时为1时才保存
     ```

3.   异或运算

     ```c++
     int e = 0b1011;
     int f = 0b0110;
     PrintBinary(e ^ f); // 0b1101 相同为0（无论是否为1） 不同为1
     ```

*特别注意*： 

`|` 、`&` 与`|｜` 、`&&`   都可以连接`bool`类型，结果类似，但是过程有区别。

*   `｜｜` 连接两个`bool`类型时，如果第一个为`true`那么`||`后面的条件不会被执行，直接把`true`返回给变量，`&&`同理，当第一个`false`时也不会执行后面的判断了
*   而`|` 、`&`执行判断的时候，时并行的，也就是都会执行，不会直接跳过。



### 4、左移运算符和右移运算符 (>> 、>>> 、<< )

```c++
int a = 0b0000000000000000000000000011;
int b = a << 2;  //0b0000000000000000000000001100; 向左边移动两位
int c = a << 3;  //0b0000000000000000000000011000; 向左边移动三位
```

右移动同理,但是注意：

*   对于非负数，`>>、>>>` 没有区别
*   对于负数，`>>` 代表向右移动的时候用**左边前缀用‘1’填充**，`>>>`（无符号右移）代表右移动的时候**左边前缀用 ‘0’ 填充** 

这里有一个对于非负数的二进制左右移动运算规律:

​	对于左移运算符`a << i` 代表 a 乘2的i次方

​	对于右移运算符`a >> i` 代表 a 除2的i次方



### 二进制打印函数

上面我们写了一个`PrintBinaey()`函数，我们这里来实现一下它

#### 原理

>   每一次我们让 1 右移 i 位，然后将原数与右移的数进行与运算，在这种操作过后，如果当前位数为 1 那么与运算后就是`0b00……0100……0`，如果当前位数为0 ，进行与运算过后就是`0b00……00`,就是0。那么我们可以根据这个判断是否打印1。

**注意**： 这里我们不能写`num & (1 << i) == 1 ？0:1`因为如果该位数为1 实际上与运算之后是`0b00……0100……0` 而不是 1 ，我们只能从0这个角度判断。

```c++
void PrintBinary(int a){
  cout<<"0b";
  for(int i =31;i>=0;i--){ //long类型就遍历64次
    cout<<（(num & (1 << i) ）== 0 ？0:1);
  }
  cout<<endl;
}
```



## ==三、经典算法 — Brian Kernighan算法==

### 理解

Brian Kernighan算法是一种经典位运算算法，目的是快速取得二进制数中最右侧的“1”。

算法简单明了：

*   首先对目标值取反
*   然后再对取反后的值+1
*   最后对目标值和操作后的值进行与运算

*注* ：前两步实际上就是`target` 的相反数的运算

### 实现


```c++
int GetRightOne(int a){
  return a & (-a);   //a & (~a + 1)
}//注意这里a不能为INT_MIN 不然会溢出

//举例 求 6最右边的二进制1
	//6:  0110
	//~: 	1001

	//+1: 1010
	//6:  0110
	//-6: 1010
	//& -> 0010
```
## 四、异或运算

异或运算有很多境界的操作，所以这里我们重点再理解

### 异或运算的性质

1.   异或运算可以看作是一种**无进位相加**

     >   比如说：
     >
     >   1 1 0 1 0 1 0 0 ^ 0 1 0 1 0 1 1 1 
     >
     >   
     >
     >   1 1 0 1 0 1 0 0
     >
     >   0 1 0 1 0 1 1 1
     >
     >   ---
     >
     >   1 0 0 0 0 0 1 1

2.   异或运算同样满足**交换律、结合律**

     >   比如说 `(a ^ b) ^ c ^ d` 和`(a ^ c) ^ d ^ b` 是等效的，我们同样可以用性质一来理解这个交换律，结合率
     >
     >   因为异或运算是一种无进位运算，也就意味着：
     >
     >   *   如果这个位数上总和如果是偶数个 1 ，那么我们就舍去这个1。
     >   *   如果这个位数上总和如果是奇数个 1 ，那么我们就保留这个1。

3.   `0 ^ n = 0`  、 `n ^ n = 0 `

4.   如果一个数组`[a,b,c,……]`总的异或为`X`，数组部分元素如中`[a,d,f……]`总的异或为`Y`，**那么剩下元素的总的异或为`X ^ Y` **

*注释*：我们最常用的是**性质4**



----



### 交换两个数字

#### 原理

>   设`a = x` ,` b = y`
>
>   那么我们知道 如果我们进行 `a^=b`
>
>   a的值就被修改为了`x^y`, b的值不变
>
>   此时，如果我们将b和修改后的a异或一下也就是`b^=a`,相当于`y^(x^y)` 根据性质4，我们可以推出此时` b = y`
>
>   最后我们让修改后的 a和交换完成的b异或一下，就完成了交换

#### 实现


```c++
void swap(int a,int b){
	cout<<a<<"  "<<b<<endl;
	//a == b 的时候同样适用
  a^=b;
  b^=a;
  a^=b;
  cout<<a<<"  "<<b<<endl;
}
```



### 不使用比较和条件判断的情况下返回两个数的最大值

#### 原理

既然不能使用比较，我们可以考虑两个数相加，分别带两个乘数，乘数要么是1，要么是0，这样就可以规避条件判断。

`return ReturnA * a + ReturnB * B`  。

我们的期望是当a > b 的时候 `ReturnA = 1`，`ReturnB = 0`反之亦然。

实际上，我们只需要知道一个`ReturnX`的值就行了，剩下那个一定和`ReturnX`相反，**我们只要将`ReturnX ^ 1`就能得到`ReturnY`了**

我们封装一个`flip`函数，用于计算某个数和1异或的结果

```c++
int flip(int a){
  return (a ^ 1);
}
```

我们很容易想到，如果要比较大小，我们最简单的方法就是两个数作差我们记录`int c = a - b` 我们只要**判断 `c`的正负号就可以了**。

前面学过了，对于有符号整数类型，第一个前缀代表了这个数的正负，于是，我们可以设计算法取到某个数的第一个前缀。使用右移运算符就可以了。

```c++
/*负数前缀是 1 右移31位后，和1异或就是0
非负数前缀是0 右移31位后，和1异或就是1*/
int sign(int x){
  return flip(x >>> 31); //无符号右移 然后和1异或
}
```

**注意**：

*   和1异或之后，1代表`x`为非负数
*   和1异或之后，0代表`x`为负数

通过`sign`函数，我们可以得到`c`的符号。

于是乎，我们就得到了`ReturnA`和`ReturnB`的结果

#### 完整代码


```c++
int flip(int a){
  return (a ^ 1);
}
//负数返回 0 正数返回 1
int sign(int x){
  return flip(x >>> 31); //无符号右移 然后和1异或
}

int getMax(int a,int b){
  int c = a - b; //a > b --> c = 1 
  int ReturnA = sign(c);
  int ReturnB = flip(ReturnA);
  return ReturnA * a + ReturnB * B;
}
```

#### 改进

但是，上述的比较有溢出风险，当`a = INT_MAX`,`b = -1`的时候就溢出了，很有可能会返回错误结果

我们需要设计算法，规避这个溢出问题。

溢出的根本就是 a 很有可能正数，但b是个负数(反过来也是一样，也有可能是`INT_MIN`那一头) ，两者相减，就有可能造成溢出，于是，我们需要设发先判断a，b的符号，如果 a非负，b负数，我们就没有必要作差了。

```c++
void getMAx(int a,int b){
  //核心思想 如果a b异号 我们没有必要管c是否溢出了，直接让c的乘数为0就行了
  int c = a - b; //c有可能溢出，但是先算着
  int signA = sign(a);
  int signB = sign(b);
  int signC = sign(c); 
  //a b同号 -> signC = 1;
  //a b异号 -> signC = 0;
  int diffAB = signA ^ signB //检查a b是不是同号的
  //a b同号 -> diffAB = 0;
  //a b异号 -> diffAB = 1;
  int sameAB = flip(diffB); 
   //a b同号 -> sameAB = 1 -> 一定不会溢出了
  //a b异号 -> sameAB = 0 -> c无所谓会不会溢出了
  int ReturnA = sameAB * signC + diffAB * signA; 
  int ReturnB = sign(ReturnA);
  return ReturnA * a + ReturnB * B;
}
```



### ==丢失的数字==

这题虽然简单，但是可以作为一个以后优化算法的小技巧

力扣***[268. 丢失的数字](https://leetcode.cn/problems/missing-number/)*** *（做到O(1)的时间复杂度）*

>   给定一个包含 `[0, n]` 中 `n` 个数的数组 `nums` ，找出 `[0, n]` 这个范围内没有出现在数组中的那个数。
>
>    
>
>   **示例 1：**
>
>   **输入：**nums = [3,0,1]
>
>   **输出：**2
>
>   **解释：**`n = 3`，因为有 3 个数字，所以所有的数字都在范围 `[0,3]` 内。2 是丢失的数字，因为它没有出现在 `nums` 中。
>
>   **示例 2：**
>
>   **输入：**nums = [0,1]
>
>   **输出：**2
>
>   **解释：**`n = 2`，因为有 2 个数字，所以所有的数字都在范围 `[0,2]` 内。2 是丢失的数字，因为它没有出现在 `nums` 中。
>
>   **示例 3：**
>
>   **输入：**nums = [9,6,4,2,3,5,7,0,1]
>
>   **输出：**8
>
>   **解释：**`n = 9`，因为有 9 个数字，所以所有的数字都在范围 `[0,9]` 内。8 是丢失的数字，因为它没有出现在 `nums` 中。
>
>   **提示：**
>
>   -   `n == nums.length`
>   -   1 <= n <= 10^4^
>   -   `0 <= nums[i] <= n`
>   -   `nums` 中的所有数字都 **独一无二**

#### 理解

异或运算的性质4直接秒杀了，而且空间复杂度是常数级别的

#### 实现



```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int eorSum = 0;
        int temp = 0;
        for(int i = 0 ;i<n;i++){
            xorSum^=i;
            temp^= nums[i];
        }
        eorSum^=n;
        return xorSum^temp;
    }
};
```



### 找到数组中出现次数为奇数次的数 I

>   给定一个可以出现重复数字的数组`nums`,其中有一个数字出现了奇数次，其余的数都出现了偶数次，请你用O(1)的时间复杂度返回这个出现奇数次的数字。

#### 分析

维护一个整数`eor = 0` ,根据性质 3[^4]我们可以发现一个规律，如果一个相同数异或偶数次，那么结果一定是 0 ，如果异或奇数次，那么结果一定是它本身。

因此我们直接异或这个数组所有数字，结果就是那个出现奇数次的答案。

#### 实现



```c++
int singleNumber(vector<int>& nums) {
        int eor = 0;
        for(int num:nums){
            eor^= num;
        }
        return eor;
}
```



### Brian Kernighan算法的应用 — 找到数组中出现次数为奇数次的数 III

力扣***[260. 只出现一次的数字 III](https://leetcode.cn/problems/single-number-iii/)***

>   给你一个整数数组 `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。你可以按 **任意顺序** 返回答案。
>
>   你必须设计并实现线性时间复杂度的算法且仅使用常量额外空间来解决此问题。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,2,1,3,2,5]
>   输出：[3,5]
>   解释：[5, 3] 也是有效的答案。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [-1,0]
>   输出：[-1,0]
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：nums = [0,1]
>   输出：[1,0]
>   ```
>
>    
>
>   **提示：**
>
>   -   2 <= nums.length <= 3 * 10^4^
>   -   -2^31^ <= nums[i] <= 2^31^ - 1
>   -   除两个只出现一次的整数外，`nums` 中的其他数字都出现两次



#### 分析

上面分析了求唯一奇数次的数，这里变成了两个，也就是说，上题的`eor = a`,这里变为了`eor = a ^ b`;

由于 a 、 b肯定是两个不同的数，两个二进制数一定至少会有一位不一样。根据异或运算的最基本理解，：==**eor的二进制表示的一定至少会有一个位数为1**==。我们将最右边第一个1的位置标记为K:`000…10000`

在这个位数上，a、b一定不一样，要么0、1要么1、0。我们可以根据这个性质分组，其他的数次数是偶数所以不用管。

再一次遍历：位置K上为1 的我就求异或和 （或者为0求异或和）



#### 实现

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
         //位运算
        int eor1 = 0;
        for(int num:nums){
            eor1^= num;
        }
        //Brian Kernighan算法
        int rightOne = eor1 & (~eor1+1);
        int eor2 = 0;
        for(int num:nums){
            if((num & rightOne)==0){
                eor2 ^= num;
            }
        }
        return {eor2,eor1^eor2};
    }
};
```



### 找的数组中出现次数为奇数的次数 II

力扣***[137. 只出现一次的数字 II](https://leetcode.cn/problems/single-number-ii/)***

>   给你一个整数数组 `nums` ，除某个元素仅出现 **一次** 外，其余每个元素都恰出现 **三次 。**请你找出并返回那个只出现了一次的元素。
>
>   你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [2,2,3,2]
>   输出：3
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [0,1,0,1,0,1,99]
>   输出：99
>   ```
>
>    
>
>   **提示：**
>
>   -   1 <= nums.length <= 3 * 10^4^
>   -   -2^31^ <= nums[i] <= 2^31^ - 1
>   -   `nums` 中，除某个元素仅出现 **一次** 外，其余每个元素都恰出现 **三次**

这里的我们给出更通性的解法：

数组中除去某个出现次数少于m次外，其余元素都出现m次

#### 分析

>   如果数x `00……1101`出现了m次 也就是说 对于x的二进制表示，第一位为1累加和为m，第二位为0不用管，第三位为1累加和为m……对于数y`00……1001`出现了少于m次，如果我们同样对每个二进制每个下标进行记录，存放到cnt[i]中，最后遍历完所有数，`cnt[i]%m！=0` 也就是说，那个目标答案在这个位数上为1，我们可以根据这个性质求到它。

#### 实现

```c++
int getTarget(vector<int>& nums,int m){
	int cnt[32]{};
  for(int num:nums){
    for(int i = 0;i<32;i++){
      cnt[i] += ((num >> i)&1); //右移到最右边和1求与 如果为1结果就是1 不是1结果为0
    }
  }
  int res = 0;
  for(int i = 0;i<32;i++){
    if(cnt[i]%m!=0){
      res = res | (1 << i);
    }
  }
  return res;
}
```



---



# 差分数组 / 前缀和

## 一维前缀和

一维前缀和经典例题：
洛谷(P3131 [USACO16JAN] Subsequences Summing to Sevens S)[https://www.luogu.com.cn/problem/P3131]  ——同余原理
## 二维前缀和

对于一个矩阵 *grid*，如果我们想要快速求以 *(r1,c2)* 为左上顶点，*(r2,c2)* 为右下顶点的长方形 S，求出这个长方形 S 内所有元素的和。如何快速计算？
> 传统方法是遍历这个长方形，时间复杂度是*O(mn)*的，有没有更快的解法呢？


借鉴一维前缀和的解法 —— 初始化二维前缀和：
> ![lc304-c.png](https://pic.leetcode.cn/1765887873-gHCBKd-lc304-c.png)

如何访问某个长方形的总和呢？
	和上面初始化二维数组前缀和的方法类似，根据容斥原理，可以简单推出：$sum[r2 + 1][c2 + 1] - sum[r2 + 1][c1] - sum[r1][c2 + 1] + sum[r1][c1]$	

测试链接[304. 二维区域和检索 - 矩阵不可变](https://leetcode.cn/problems/range-sum-query-2d-immutable/description/)

## 一维差分
考虑下面这个场景：
力扣***[拼车](https://leetcode.cn/problems/car-pooling/description/)***

更一般地，考虑下面这个场景
> 如果给出数组`operators`，其中`operators[i] = [l,r,num]`,每次我都对闭区间[l,r]内加上 num，最终我们如何快速得到经过这些操作之后的数组呢？仅限使用*O(n)*的算法。

定义一个 *diff* 数组，数组大小开到和 *nums* 一致，对于每次操作,我们都让 *diff[l] += num*、*diff[r + 1] -=num*，最终我们完成初始化 diff 数组后，我们再一次遍历 *diff* 数组，记录 *diff[i]* 数组当前的前缀和*currSum*，再让 *nums[i] += currSum* 即可。


# 排序算法

## 一、选择排序

### 概念

选择排序是**每轮从未排序区间中找到最小值（或最大值），将其与未排序区间的第一个元素交换**，重复该过程直到数组有序。

### 实现



```c++
void SelectSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0;i < n;i++) {
        int min_idx = i;
        int mn = arr[i];
        for (int j = i + 1;j < n;j++) {
            if (mn > arr[j]) {
                min_idx = j;
                mn = arr[j];
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}
```

### 复杂度

* 时间复杂度O(n^2^)
* 空间复杂度O(1)



## 二、冒泡排序

### 概念

冒泡排序是一种基础排序算法，核心逻辑是**相邻元素两两比较，将较大元素逐步 “冒泡” 到数组末尾**，重复该过程直到数组有序。

### 实现



```c++
void BubbleSort(std::vector<int>& arr, int pattern) {
    int n = arr.size();
    if (pattern == 0) {		//从小到大
        for (int i = 0;i < n - 1;i++) { // n-1 防止下面arr[i+1]越界
            for (int j = 0;j < n - i - 1;j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    if (pattern == 1) { 	//从大到小
        for (int i = 0;i < n - 1;i++) {
            for (int j = 0;j < n - i - 1;j++) {
                if (arr[j] < arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

```

### 复杂度

* 时间复杂度O(n^2^)
* 空间复杂度O(1)

## 三、插入排序

### 概念

直接插入排序是**将未排序元素逐个插入到已排序序列的合适位置**，适用于小规模数据或基本有序的数组。

### 实现



```c++
void InsertSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1;i < n;i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
```



### 优化 折半插入排序

所谓的折半插入排序，就是在**“向前看”**这个过程中用二分查找查找大于等于它的数。



```c++
void InsertSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1;i < n;i++) {
        int temp = arr[i];
        int left = 0, right = i;
        while (left < right) {  //[left,right)
            int mid = left + (right - left) / 2; //防止溢出
            if (arr[mid] >= temp) right = mid;
            else  left = mid + 1;
        }
     		//也可以用库函数
     		//int idx = std::upper_bound(arr.begin(),arr.end(),temp)-arr.begin();
        //left就是我们要插入的位置
        int j;
        for (j = i;j > left;j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}
```

### 复杂度

* 时间复杂度O(n^2^)
* 空间复杂度O(1)

## 四、希尔排序

### 理解

希尔排序（Shell Sort）是 **插入排序的改进版**，核心思想是「分组插入排序」—— 通过设定「增量序列」将数组分成多个子数组，对每个子数组执行插入排序；逐步缩小增量，直到增量为 1（此时退化为普通插入排序，但数组已基本有序，效率大幅提升）。

这么说还是太抽象了，建议观看***[数据结构合集 - 希尔排序(算法过程, 效率, 稳定性分析)](https://www.bilibili.com/video/BV1bm42137UZ/?spm_id_from=333.337.search-card.all.click)***

### 实现

 

```c++
void ShellSort(std::vector<int>& arr) {
    int n = arr.size();
    int gap = n / 2;
    while (gap) {
        for (int i = gap;i < n;i++) {
            int temp = arr[i];
            int j = i - gap;
            //向左边的组类看
            while (j >= 0 && arr[j] > temp) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j+gap] = temp;
        }
        gap /= 2;
    }
}
```

*注*：希尔排序的分组方法不仅仅只有一直二分，还有别的分组方法，这些时间复杂度都不一样，至于哪种方法最优，目前尚未找出最好的分组方法。



# 滑动窗口

## *[算法题单]()*



## 一、定长滑动窗口



## 二、不定长滑动窗口

### 越短越合法 

**一般要写 ans += right - left + 1。**

>内层循环结束后，[left,right] 这个子数组是满足题目要求的。由于子数组越短，越能满足题目要求，所以除了 [left,right]，还有 [left+1,right],[left+2,right],…,[right,right] 都是满足要求的。也就是说，当右端点固定在 right 时，左端点在 left,left+1,left+2,…,right 的所有子数组都是满足要求的，这一共有 right−left+1 个。

### 越长越合法
**一般要写 ans += left。**
> 内层循环结束后，[left,right] 这个子数组是不满足题目要求的，但在退出循环之前的最后一轮循环，[left−1,right] 是满足题目要求的。由于子数组越长，越能满足题目要求，所以除了 [left−1,right]，还有 [left−2,right],[left−3,right],…,[0,right] 都是满足要求的。也就是说，当右端点固定在 right 时，左端点在 0,1,2,…,left−1 的所有子数组都是满足要求的，这一共有 left 个。

我们关注的是 left−1 的合法性，而不是 left。


### ==恰好合法== —— 正难则反的思想

> 例如，要计算有多少个元素和恰好等于 k 的子数组，可以把问题变成
计算有多少个元素和 ≥k 的子数组。
计算有多少个元素和 >k，也就是 ≥k+1 的子数组。
答案就是元素和 ≥k 的子数组个数，减去元素和 ≥k+1 的子数组个数。这里把 > 转换成 ≥，从而可以把滑窗逻辑封装成一个函数 solve，然后用 solve(k)−solve(k+1) 计算，无需编写两份滑窗代码。

总结：「恰好」可以拆分成两个「至少」，也就是两个「越长越合法」的滑窗问题。

注：也可以把问题变成 ≤k 减去 ≤k−1，即两个「至多」。可根据题目选择合适的变形方式。

* [K 个不同整数的子数组](https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/description/) —— 滑窗并不难，难在如何想到



## 延时删除策略

力扣***[3835. 开销小于等于 K 的子数组数目 ](https://leetcode.cn/problems/count-subarrays-with-cost-less-than-or-equal-to-k/)***—— 单调队列也可以解决







---

# 二分查找



## 左闭右开写法

```c++
int lower_bound(vector<int>& nums,int target){
	int left = 0,right = nums.size();
  //循环不变量
  //nums[left-1]<target, nums[left]可能等于target
  //nums[right]>=target
  while(left<right){
		int mid = left + (right - left) / 2; //防止加法溢出
    if(nums[mid]>=target){ //左边有可能还有等于targrt的数 我们还要缩小范围
      right = mid;
    }
    else{ 
      left = mid + 1;
    }
  }
  //循环结束时left = right
  //此时nums[left-1]<target 而nums[left]=nums[right]
  return left;
}
```

### 理解

理解开闭究竟是一个什么东西

*   闭区间内是可能含有答案的区间，这里已经有`left < nums[mid]`，`mid`对应的下标一定不是答案区间内，  而`left+1`可能是目标边界。所以这里 `left` 要+1。

    *   比如，这里有 {1,2,3,3,4,4,5,6}  我要找 $>=$ 4 的第一个元素，那么我`mid=3` 下标对应的值是 3，显然不是目标区间，但是`mid + 1` 下标对应的元素恰好符合目标。

    

*   开区间内就是一定不包含答案的区间，但是我们可以发现我们这里已经有小于等于 `target`，为什么还要`mid=right` 呢？ 万一`nums[mid] == target`，不应该直接返回`mid`就行吗，不会错过答案吗？

    *   不会，我们这里`right = mid` 是为了防止前面还有值等于`target`的数。
    *   比如 {1,4,4,4,5} ，目标下界为4。我第一次二分`mid=2`,下标对应的值为4，但是我们发现，这个下下标并不是第一个个大于等于4的数。左边有可能还会有目标下界，所以我们要把`right = mid`，也不用担心会错过答案，我们等待`left` 移过来就可以了。

## 库函数写法

```c++
#include<algorithm>
#include<ranges>
#include<vector>
using namespace std;
int main(){
	vector<int> vec;
  int target = 100;
  int start = ranges::lower_bound(vec,target) - vec.begin();
}
```



### *注*

`std::ranges::lower_bound(vector,target)`  是c++20才引入的方法，对于蓝桥杯这样的oi比赛，我们只能使用旧版的库 ：`std::lower_bound(vec.begin(),vec.end(),target)` 。 

此外： `upper_bound` 方法，`lower_bound` 是查找第一个大于等于，`upper_bound` 是查找第一个大于的数。



## 其他类型的转化

| 需求  |             写法              | 如果不存在  |
| :---: | :---------------------------: | :---------: |
| $>=x$ |   `lower_bound(arr,target)`   | `return n`  |
| $>x$  |  `lower_bound(arr,target+1)`  | `return n`  |
| $<x$  |  `lower_bound(arr,target)-1`  | `return -1` |
| $<=x$ | `lower_bound(arr,target+1)-1` | `return -1` |

### 记法 

这么多转化肯定不能硬记，我们可以通过集合来记。

*   $>=x$ 与$<x$ 构成一个全集，所以我们只要在 $>=x$ 的答案上 $-1$ 就是 $<x$ 的答案。
*   $>x$  相当于查找 $>=x+1$  。
*   同理，$>x$ 与 $<=x$ 又构成一个全集，和第一条类似。



## 附

这里的二分查找都是找到第一个符合边界条件的数

## 二分答案 ——

> **“如果我们想枚举答案，并且发现答案和题目之间的条件存在某种单调关系，就用二分答案，把复杂度降到*log(n)* 级别”**


所谓的二分答案，实际上就是已知答案在某个区间，要我们枚举这个区间去求答案的时候，原本用*O(U)*的时间复杂度利用二分查找降低到*O(log  U)*的时间复杂度。

### 求最小 —— 使结果不超过最小阈值的最小除数

力扣***[1283. 使结果不超过阈值的最小除数](https://leetcode.cn/problems/find-the-smallest-divisor-given-a-threshold/)***

>   给你一个整数数组 `nums` 和一个正整数 `threshold` ，你需要选择一个正整数作为除数，然后将数组里每个数都除以它，并对除法结果求和。
>
>   请你找出能够使上述结果小于等于阈值 `threshold` 的除数中 **最小** 的那个。
>
>   每个数除以除数后都向上取整，比方说 7/3 = 3 ， 10/2 = 5 。
>
>   题目保证一定有解。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,2,5,9], threshold = 6
>   输出：5
>   解释：如果除数为 1 ，我们可以得到和为 17 （1+2+5+9）。
>   如果除数为 4 ，我们可以得到和为 7 (1+1+2+3) 。如果除数为 5 ，和为 5 (1+1+1+2)。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [2,3,5,7,11], threshold = 11
>   输出：3
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：nums = [19], threshold = 5
>   输出：4
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 5 * 10^4`
>   -   `1 <= nums[i] <= 10^6`
>   -   `nums.length <= threshold <= 10^6`



#### 分析

对于每个除数 *m*，设最终相除之后的和为 *s*，根据题意，很同意得出：
$$
s=\sum \lceil\frac{nums[i]}{m}\rceil
$$
很显然，*m*越大，s 越小，*m* 越小，s 越大，具有单调关系。

最坏情况是除数 *m*为 *nums*中最大的数，所以我们得到 m 的范围为 $[1,max(nums)]$



##### 实现

``` c++
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        threshold-=nums.size();
        auto check = [&](int m) -> bool {
            int sum = 0;
            for (int x : nums) {
                sum += (x - 1) / m;
                if (sum > threshold) { // 提前退出循环
                    return false;
                }
            }
            return true;
        };

        int left = 1, right = ranges::max(nums) + 1;
        while (left < right) { // [left,right)
            int mid = left + (right - left) / 2;
            if(check(mid)){
                right = mid; // 贪心一点，mid 左边是不是还有更小的数符合要求呢？
            }
            else{
                left = mid + 1;
            }
        }
        return right;
    }
};
```





### 求最大 —— H 指数II  ~~（这什么名字）~~

力扣***[275. H 指数 II](https://leetcode.cn/problems/h-index-ii/)***

>   给你一个整数数组 `citations` ，其中 `citations[i]` 表示研究者的第 `i` 篇论文被引用的次数，`citations` 已经按照 **非降序排列** 。计算并返回该研究者的 h 指数。
>
>   [h 指数的定义](https://baike.baidu.com/item/h-index/3991452?fr=aladdin)：h 代表“高引用次数”（high citations），一名科研人员的 `h` 指数是指他（她）的 （`n` 篇论文中）**至少** 有 `h` 篇论文分别被引用了**至少** `h` 次。
>
>   请你设计并实现对数时间复杂度的算法解决此问题。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：citations = [0,1,3,5,6]
>   输出：3
>   解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 0, 1, 3, 5, 6 次。
>        由于研究者有3篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：citations = [1,2,100]
>   输出：2
>   ```
>
>    
>
>   **提示：**
>
>   -   `n == citations.length`
>   -   `1 <= n <= 105`

#### 分析

显然我们看得出来 *h* 的范围是属于$[1,n]$，当 *h*越大，我们答案的符合要求的答案越少。这里有一个前提：

>   如果至少有2 篇论文的引用次数≥2，那么也必然至少有 1 篇论文的引用次数≥1
>
>   如果没有 4 篇论文的引用次数≥ 4，那么也必然没有 5 篇论文的引用次数≥5

#### 实现

注意点都在注解中了



**强调**：

*   二分答案的区间内不一定包含答案，比如说本题也允许 h 指数为0。最终 *left == right ==1*，返回的`return left - 1` = 0 也符合要求。

*   ==⚠**注意**：我们二分的是答案，是**引用次数**，不是 *citations* 的下标。==

``` c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        //引用次数，而不是下标，应该是idx + 1
        int left = 1,right = n + 1;
        while(left < right){
            int mid = (right + left) / 2;
            // citations[n - mid] >= h 代表这个人的论文有 n - mid 篇论文引用都超过 h 次
            // 既然 mid 符合，那么我贪心 mid 右边是否还存在符合答案的呢？
            if(citations[n - mid] >= mid){ //mid 代表的h，引用次数而不是下标！！！所以不用 n - mid + 1
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        //left == right left 是第一个不满足条件的值，所以 left - 1 一定是满足条件的值
        return left - 1;
    }
};
```





# 单调栈

单调栈的核心思想就是维护栈中的元素保持单调性

原理讲解：***[单调栈【基础算法精讲 26】](https://leetcode.cn/link/?target=https%3A%2F%2Fwww.bilibili.com%2Fvideo%2FBV1VN411J7S7%2F)***

## 每日温度

力扣***[739. 每日温度](https://leetcode.cn/problems/daily-temperatures/)***

>   给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。
>
>    
>
>   **示例 1:**
>
>   ```
>   输入: temperatures = [73,74,75,71,69,72,76,73]
>   输出: [1,1,4,2,1,1,0,0]
>   ```
>
>   **示例 2:**
>
>   ```
>   输入: temperatures = [30,40,50,60]
>   输出: [1,1,1,0]
>   ```
>
>   **示例 3:**
>
>   ```
>   输入: temperatures = [30,60,90]
>   输出: [1,1,0]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= temperatures.length <= 10^5`
>   -   `30 <= temperatures[i] <= 100`

### 分析

遍历*temperatures*中的每个元素*t*，再维护一个栈*st*，储存每个元素的下标，对于遍历到的每个元素*t*，我们将它和栈顶每个元素下标对应的值比较，如果栈顶元素下标对应的值小于*t*，说明 *t* 就是大于栈顶的第一个元素。

### 实现

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        int m = temperatures.size();
        vector<int> res(m);
        for(int i = 0;i < m;i++){
            int t = temperatures[i];
            while(!st.empty() && t > temperatures[st.top()]){
                int j = st.top();
                st.pop();
                res[j] = i - j;
            } 
            st.push(i);
        }
        return res;   
    }
};
```



## 一些好题

力扣***[654. 最大二叉树](https://leetcode.cn/problems/maximum-binary-tree/)*** —— 考虑单调栈*O(n)*的做法

力扣***[3676. 碗子数组的数目](https://leetcode.cn/problems/count-bowl-subarrays/description/)***





---

# 单调队列








# 二叉树

## *[算法题单](https://leetcode.cn/discuss/post/3142882/fen-xiang-gun-ti-dan-lian-biao-er-cha-sh-6srp/)*

---



## 一、前序遍历

* 前序遍历从上到下。上方的数据传到下方，返回值没有什么意义，但有时候需要一个全局变量或在函数中传入一个参数来维护答案。 



***如力扣[112. 路径总和](https://leetcode.cn/problems/path-sum/)***

>给你二叉树的根节点 `root` 和一个表示目标和的整数 `targetSum` 。判断该树中是否存在 **根节点到叶子节点** 的路径，这条路径上所有节点值相加等于目标和 `targetSum` 。如果存在，返回 `true` ；否则，返回 `false` 。
>
>**叶子节点** 是指没有子节点的节点。



```c++

bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr) return false;
        targetSum-=root->val;
        if(root->left==nullptr&&root->right==nullptr){
            return targetSum==0;
				}
        return hasPathSum(root->left,targetSum)||
          hasPathSum(root->right,targetSum);
}
```

---

## 二、后序遍历

*   后序遍历从下到上。也就是说，上方的根节点可以接受下方传过来的数据，我们可以在根节点处理左子树，右子树传上来的数据。



***如力扣 [951. 翻转等价的二叉树](https://leetcode.cn/problems/flip-equivalent-binary-trees/description/)***

>我们可以为二叉树 **T** 定义一个 **翻转操作** ，如下所示：选择任意节点，然后交换它的左子树和右子树。
>
>只要经过一定次数的翻转操作后 ，能使 **X** 等于 **Y**，我们就称二叉树 **X** *翻转 等价* 于二叉树 **Y**。
>
>这些树由根节点 `root1` 和 `root2` 给出。如果两个二叉树是否是*翻转 等价* 的树，则返回 `true` ，否则返回 `false` 。



```c++
bool flipEquiv(TreeNode* root1, TreeNode* root2) {
      auto dfs=[&](auto&&dfs,TreeNode*node1,TreeNode*node2)->bool{
          if(node1==nullptr&&node2==nullptr) return true;
          else if(node1==nullptr||node2==nullptr) return false;
          // 如果不反转
          bool f1=dfs(dfs,node1->left,node2->left);
          bool f2=dfs(dfs,node1->right,node2->right);

          //如果反转
          bool f3=dfs(dfs,node1->left,node2->right);
          bool f4=dfs(dfs,node1->right,node2->left);

          return node1->val==node2->val && ((f1&&f2)||(f3&&f4));
      };
      return dfs(dfs,root1,root2);
}
```

---

### 后序遍历的一个应用 --- ***删点***



如力扣*** [1325. 删除给定值的叶子节点](https://leetcode.cn/problems/delete-leaves-with-a-given-value/description/)***

>给你一棵以 `root` 为根的二叉树和一个整数 `target` ，请你删除所有值为 `target` 的 **叶子节点** 。
>
>注意，一旦删除值为 `target` 的叶子节点，它的父节点就可能变成叶子节点；如果新叶子节点的值恰好也是 `target` ，那么这个节点也应该被删除。
>
>也就是说，你需要重复此过程直到不能继续删除。



```C++
TreeNode* removeLeafNodes(TreeNode* root, int target) {
      if(root==nullptr) return nullptr;
      root->left=removeLeafNodes(root->left,target);
      root->right=removeLeafNodes(root->right,target);
      if(root->left==nullptr&&root->right==nullptr&&root->val==target){
          return nullptr;
      }
      return root;
  }
```

*我们发现，我们每次递归上来的的节点由root接收了，如果删除了就返回了一个nullptr，这种情况下，我们只能用后序遍历，如果我们用前序遍历，我们无法做到重新连接左右子树。*



## 三、二叉树的直径

不多解释，直接看下面这道题吧，可以对二叉树的直径有更好的理解。

### 示例一

力扣***[543. 二叉树的直径](https://leetcode.cn/problems/diameter-of-binary-tree/description/)***

>   给你一棵二叉树的根节点，返回该树的 **直径** 。
>
>   二叉树的 **直径** 是指树中任意两个节点之间最长路径的 **长度** 。这条路径可能经过也可能不经过根节点 `root` 
>
>   两节点之间路径的 **长度** 由它们之间边数表示。
>
>   **示例1:**
>
>   ![diamtree](https://assets.leetcode.com/uploads/2021/03/06/diamtree.jpg)
>
>   >   输入：root = [1,2,3,4,5]
>   >   输出：3
>   >   解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        //保存左 和 右 在每个根结点计算 看看当前值和维护的最大值比较
        int mx=0;
        auto dfs=[&](this auto&&dfs,TreeNode*node)->int{
            if(node==nullptr) return 0;
            int left=dfs(node->left);
            int right=dfs(node->right);
            mx=max(mx,left+right);
            return max(left,right)+1;
        };
        dfs(root);
        return mx;
    }
};
```

*   当然，这只是一个最直接的例子，要是他这么简单~~，那就没有必要提了~~



### 示例二

​    力扣***[2385. 感染二叉树需要的总时间](https://leetcode.cn/problems/amount-of-time-for-binary-tree-to-be-infected/)***



>   给你一棵二叉树的根节点 `root` ，二叉树中节点的值 **互不相同** 。另给你一个整数 `start` 。在第 `0` 分钟，**感染** 将会从值为 `start` 的节点开始爆发。
>
>   每分钟，如果节点满足以下全部条件，就会被感染：
>
>   -   节点与一个已感染节点相邻。
>   -   节点此前还没有感染。
>
>   返回感染整棵树需要的*分钟数*。
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2022/06/25/image-20220625231744-1.png)
>
>   输入：root = [1,5,3,null,4,10,6,9,2], start = 3
>   输出：4
>   解释：节点按以下过程被感染：
>   - 第 0 分钟：节点 3
>   - 第 1 分钟：节点 1、10、6
>   - 第 2 分钟：节点5
>   - 第 3 分钟：节点 4
>   - 第 4 分钟：节点 9 和 2
>   感染整棵树需要 4 分钟，所以返回 4 。 




``` C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        // 实际上不就是找这个start节点最远的路程吗 还是直径问题
      	// 可以分为两块 一个是start->本侧的叶子节点 
      	// 还有一个是 start->根节点->另一侧的叶子节点
        int mx = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<int, bool> {
            if (node == nullptr)
                return {0, false};
            auto [l_h, l_b] = dfs(node->left);
            auto [r_h, r_b] = dfs(node->right);
            if (node->val == start) {
                mx=max(l_h,r_h); 
              	//可以放心重置 上方已经记录了在start往下走的长度 接下来往根节点走
                return {1,true}; 
            }
            if(l_b||r_b){  //左边或者右边已经遍历了start
              	//看看当前节点到是不是符合start->node->node下的叶子节点直径最长
                mx=max(mx,l_h+r_h); 
              
                if(l_b) return {l_h+1,true};
                else return {r_h+1,true};
            }
            else return {max(l_h,r_h)+1,false}; //两边还没出现，那我就把最高的那一边返回给上面
            
        };
        dfs(root);
        return mx;
    }
};
```



*注*：我们用了一个技巧，那就是返回值为`pair<int,bool>` ==同时带回两个数据==，`int`代表当前路径长度，`bool`代表这条路径上是否已经遍历了`start`，这种返回两个参数的技巧很常用，请务必记住有这种方法。



## 四、最近公共祖先（LCA）

#### 对于求解LCA问题，我们有一个模版

力扣***[235. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/)***

>   给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
>
>   [百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)
>
>   输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
>   输出：3
>   解释：节点 5 和节点 1 的最近公共祖先是节点 3 。





```c++
class Solution{
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
      if(root==NULL||root==p||root==q) return root; //如果找到了p，q 就返回节点本身
    
      TreeNode*left=lowestCommonAncestor(root->left,p,q);
      TreeNode*right=lowestCommonAncestor(root->right,p,q);
    	//发现左右都不为空 说明是LCA
      if(left&&right) return root;
     	// 如果有一个不为空 说明要么是LCA 要么就是找到了p或q
      return left?left:right;
    	//直接返回不为空的那个即可 如果两个都为空 还是返回nullptr哦
	}
};
```



#### 示例

力扣***[2096. 从二叉树一个节点到另一个节点每一步的方向](https://leetcode.cn/problems/step-by-step-directions-from-a-binary-tree-node-to-another/)***

>   给你一棵 **二叉树** 的根节点 `root` ，这棵二叉树总共有 `n` 个节点。每个节点的值为 `1` 到 `n` 中的一个整数，且互不相同。给你一个整数 `startValue` ，表示起点节点 `s` 的值，和另一个不同的整数 `destValue` ，表示终点节点 `t` 的值。
>
>   请找到从节点 `s` 到节点 `t` 的 **最短路径** ，并以字符串的形式返回每一步的方向。每一步用 **大写** 字母 `'L'` ，`'R'` 和 `'U'` 分别表示一种方向：
>
>   -   `'L'` 表示从一个节点前往它的 **左孩子** 节点。
>   -   `'R'` 表示从一个节点前往它的 **右孩子** 节点。
>   -   `'U'` 表示从一个节点前往它的 **父** 节点。
>
>   请你返回从 `s` 到 `t` **最短路径** 每一步的方向。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/11/15/eg1.png)
>
>   ```
>   输入：root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
>   输出："UURL"
>   解释：最短路径为：3 → 1 → 5 → 2 → 6 。
>   ```
>
>   **示例 2：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/11/15/eg2.png)
>
>   ```
>   输入：root = [2,1], startValue = 2, destValue = 1
>   输出："L"
>   解释：最短路径为：2 → 1 。
>   ```
>
>    
>
>   **提示：**
>
>   -   树中节点数目为 `n` 。
>   -   `2 <= n <= 105`
>   -   `1 <= Node.val <= n`
>   -   树中所有节点的值 **互不相同** 。
>   -   `1 <= startValue, destValue <= n`
>   -   `startValue != destValue`

##### 分析：

*   注意到从 `startValue` 到`destValue`是一定会经历他们的最近公共祖先的。
*   `start` 到 `lca`一定是***向上***的，即“ U ”。
*   `lca` 到 `dest`一定是***向下***的，只有可能是“ L ”或者是“ R ”。

我们可以根据上面三条分析分别写三个dfs，得到答案。





```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        //找到最近公共祖先
        auto searchacl=[&](this auto&&searchacl,TreeNode*node)->TreeNode*{
            if(node==nullptr||node->val==startValue||node->val==destValue){
                return node;
            }
            TreeNode*left=searchacl(node->left);
            TreeNode*right=searchacl(node->right);
            if(left&&right) return node;
            return left?left:right;
        };
        string start="";
        //start到最近公共祖先的路程
        auto dfs1=[&](this auto&&dfs1,TreeNode*node)->bool{
            if(node==nullptr) return false;
            bool left=dfs1(node->left);
            bool right=dfs1(node->right);
            if(node->val==startValue) return true;
            if(left||right){
                 start+="U";
                 return true;
            }
            else{
                return false;
            }
        };
        //最近公共祖先到dest的路程
        auto dfs2=[&](this auto&&dfs2,TreeNode*node)->bool{
            if(node==nullptr)   return false;  
            if(node->val==destValue) return true;
            start+='L';
            if(dfs2(node->left)) return true;
            start.back()='R';
            if(dfs2(node->right)) return true;
            start.pop_back();
            return false;
        };
        TreeNode*acl=searchacl(root);
        //两个路程相拼接就是答案
        dfs1(acl);
        dfs2(acl);
        return start;
    }
};
```



   *注*：我的代码并不是最优解，但我认为我的是最好理解的，对于刚学LCA的自己来说只能写出这种水平的代码了。如果想要更精简更快的代码可以见题解

## 五、二叉搜索树（BST）

### 理解 

*   二叉搜索树，由于他左小右大的规律，如果我们使用中序遍历，我们可以发现，使用中序遍历之后，把他展开成排列，我们可以得到一个升序的序列。
*   同时，如果我们在BST中搜索一个数值：  
    平均时间复杂度为`O(log n)`；
    最坏情况时间复杂度为`O(n)`  ，二叉搜索树被排列成一个链表。
*   注意： 中序遍历有的也可以有返回值～

---

### 误区

一看到BST 我们就只想到中序遍历，这是不合理的，中序遍历只能是BST的一个顺序性质，BST最重要的还是它本身左小右大的特性。见下面的 示例二 不能被固化思维！！！



### **示例一**

力扣 ***[530. 二叉搜索树的最小绝对差](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/)***

>给你一个二叉搜索树的根节点 `root` ，返回 **树中任意两不同节点值之间的最小差值** 。
>
>差值是一个正数，其数值等于两值之差的绝对值。
>
> 
>
>**示例 1**
>
>![img](https://assets.leetcode.com/uploads/2021/02/05/bst1.jpg)
>
>输入：root = [4,2,6,1,3]
>输出：1
>
>**示例 2: **
>
输入：root = [1,0,48,null,null,12,49]
输出：1
>
>提示：
>
>*   树中节点的数目范围是 [2, 10^4^]
>*   0 <= Node.val <= 10^5^





```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int mn=INT_MAX;
        int pre=INT_MIN/2;  //防止减法溢出
        auto dfs=[&](this auto&&dfs,TreeNode*node)->void{
            //最小两个差值一定是顺序序列中相邻的数
            if(node==nullptr) return;
            dfs(node->left); //左
          	//中
            mn=min(mn,node->val-pre); 
            pre=node->val;
            dfs(node->right); //右
        };
        dfs(root);
        return mn;
    }
};
```

 这是二叉搜索树最简单的一个应用。

### **==示例二==**

***一碰到“ 二叉搜索树 ”，并不是应该去想“中序遍历 ”去实现，而是应该优先思考==值的大小关系==。***

力扣 ***[938. 二叉搜索树的范围和](https://leetcode.cn/problems/range-sum-of-bst/)***

>给定二叉搜索树的根结点 `root`，返回值位于范围 *`[low, high]`* 之间的所有结点的值的和。
>
>**示例 1:**
>
>![img](https://assets.leetcode.com/uploads/2020/11/05/bst1.jpg)
>
>> 输入：root = [10,5,15,3,7,null,18], low = 7, high = 15
>> 输出：32
>
>**示例 2：**
>
>> 输入：root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
>> 输出：23
>
>提示：
>
>> 树中节点数目在范围 [1, 2 * 10^4^] 内
>> 1 <= Node.val <= 10^5^
>> 1 <= low <= high <= 10^5^
>> 所有 Node.val 互不相同

 

***写法一：***

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (root == nullptr)
            return 0;
        int x = root->val;
        if (x > high) { // 右子树一定小于high 左子树可能在[low,high]
            return rangeSumBST(root->left, low, high);
        }
        if (x < low) { // 左子树一定小于low 右子树可能在[low,high]
            return rangeSumBST(root->right, low, high);
        }
        return x + rangeSumBST(root->left, low, high) +
               rangeSumBST(root->right, low, high);
    }
};
```

***写法二：***

```c++
class Solution {
public:
    int rangeSumBST(TreeNode *root, int low, int high) {
        if (root == nullptr) {
            return 0;
        }
        int x = root->val;
        int sum = low <= x && x <= high ? x : 0;
        if (x > low) { // 左子树可能有节点值在范围内
            sum += rangeSumBST(root->left, low, high);
        }
        if (x < high) { // 右子树可能有节点值在范围内
            sum += rangeSumBST(root->right, low, high);
        }
        return sum;
    }
}; 
```

##### 反思

我陷入了误区，我陷入了***中序遍历*** 的~~陷阱~~ ，这道题是根据当前值是否在范围内进行递归，而我已看到bst就想到中序遍历思维固化了。 

下次遇到中序遍历时，我应该想： 能不能用当前节点的值来决定搜索策略？（以当前值为重点）

### **示例三**

*典型的中序遍历*

力扣***[501. 二叉搜索树中的众数](https://leetcode.cn/problems/find-mode-in-binary-search-tree/description/)***

>给你一个含重复值的二叉搜索树[^1]（BST）的根节点 `root` ，找出并返回 BST 中的所有 [众数](https://baike.baidu.com/item/众数/44796)（即，出现频率最高的元素）。
>
>如果树中有不止一个众数，可以按 **任意顺序** 返回。
>
>假定 BST 满足如下定义：
>
>-   结点左子树中所含节点的值 **小于等于** 当前节点的值
>-   结点右子树中所含节点的值 **大于等于** 当前节点的值
>-   左子树和右子树都是二叉搜索树


#### 思路

中序遍历

> 为什么要中序遍历呢？ 
> 因为中序遍历是有序的，问题可以转化为求有序序列中频率最大的元素

#### 技巧

我们先让cnt++，然后再判断`cnt `> `max_cnt` 这里如果大于，我们直接清除 `res` 即可，在保存一次`node->val` 即可。

如果不清楚可以创建一个有序数列安线形顺序模拟一遍。



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        
        vector<int> res;
        if(root==nullptr) return res;

        int pre=root->val;
        int cnt=0,max_cnt=0;
        auto dfs=[&](this auto&&dfs,TreeNode*node)->void{
            if(node==nullptr) return;
            //左中右
            dfs(node->left);
            if(node->val==pre) cnt++;
            else cnt=1;
            if(cnt==max_cnt) res.push_back(node->val);
            if(cnt>max_cnt){
                res.clear();
                res.push_back(node->val);
                max_cnt=cnt;
            }
            pre=node->val;
            dfs(node->right);
        };
        dfs(root);
        return res;
    }
};
```



### 示例四

BST与二分查找的结合

力扣**[2476. 二叉搜索树最近节点的查询](https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/description/)**

*注*： 这里就不给解答了，直接点链接做吧。



### 示例五

BST中序遍历其实有时候也可以有返回值

力扣***[285. 二叉搜索树的中序遍历的后继](https://leetcode.cn/problems/inorder-successor-in-bst/description/)***



>   给定一棵二叉搜索树和其中的一个节点 `p` ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 `null` 。
>
>   节点 `p` 的后继是值比 `p.val` 大的节点中键值最小的节点。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_1.PNG)
>
>   ```
>   输入：root = [2,1,3], p = 1
>   输出：2
>   解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
>   ```
>
>   **示例 2：**
>
>   ![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_2.PNG)
>
>   ```
>   输入：root = [5,3,6,2,4,null,null,1], p = 6
>   输出：null
>   解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
>   ```
>
>    
>
>   **提示：**
>
>   -   树中节点的数目在范围 `[1, 104]` 内。
>   -   `-105 <= Node.val <= 105`
>   -   树中各节点的值均保证唯一。

#### 解法一

我们很容易看出来，这题其实返回`p`的下一个节点，中序遍历就行。

显然，我们不用遍历整颗树，为了节省递归开销，加一个返回值指示是否找到答案。

*   如果返回值不是`nullptr` 说明我们已经找到答案，向上传递答案即可。
*   如果返回值是`nullptr`，说明还要探索答案，继续遍历，*注意*：这里不能直接返回`nullptr`,直接返回相当于直接停止接下来的遍历了。



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        bool flag=false;
        auto dfs=[&](this auto&&dfs,TreeNode*node)->TreeNode*{
            if(node==NULL) return NULL;
            TreeNode* left = dfs(node->left);
            if(left) return left;
            if(flag){
                flag=false;
                return node;
            }
            if(node==p) flag=true;
            return dfs(node->right);
        };
        return dfs(root);
    }
};
```



#### 解法二

更好的方法是迭代法。

我们可以枚举所有大于`p->val`的节点。

根据BST的性质，我们可以不断缩小范围，迭代更新`res`



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        //迭代法
        TreeNode* res = NULL;
        while(root){
            if(root->val>p->val){
                res=root;
                root=root->left;
            }
            else{
                root=root->right;
            }
        }
        return res;
    }
};
```

#### 进阶

力扣***[501. 二叉搜索树的中序的后继 II](https://leetcode.cn/problems/inorder-successor-in-bst-ii/description/)*** *（会员题）*



>   给定一棵二叉搜索树和其中的一个节点 `node` ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 `null` 。
>
>   一个节点 `node` 的中序后继是键值比 `node.val` 大所有的节点中键值最小的那个。
>
>   你可以直接访问结点，但无法直接访问树。每个节点都会有其父节点的引用。节点 `Node` 定义如下：
>
>   ```
>   class Node {
>       public int val;
>       public Node left;
>       public Node right;
>       public Node parent;
>   }
>   ```
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_1.PNG)
>
>   ```
>   输入：tree = [2,1,3], node = 1
>   输出：2
>   解析：1 的中序后继结点是 2 。注意节点和返回值都是 Node 类型的。
>   ```
>
>   **示例 2：**
>
>   ![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_2.PNG)
>
>   ```
>   输入：tree = [5,3,6,2,4,null,null,1], node = 6
>   输出：null
>   解析：该结点没有中序后继，因此返回 null 。
>   ```
>
>    
>
>   **提示：**
>
>   -   树中节点的数目在范围 [1, 10^4^] 内。
>   -   `-105 <= Node.val <= 105`
>   -   树中各结点的值均保证唯一。

##### 算法
* 如果节点有右子节点，那么它的后继者在树的下部。向右走一步，然后尽可能地向左走。返回你最终停留的节点。
* 节点没有右子节点，因此它的后继者在树的上部。向上走，直到节点是其父节点的_左_子节点。答案是父节点。
* 可以手动模拟一遍。



```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        if(node->right){
            node=node->right;
            while(node->left) node=node->left;
            return node;
        }
        while(node->parent&&node->parent->right==node){
            node=node->parent;
        }
        return node -> parent;
    }
};
```





## 六、创建二叉树



### 示例一

力扣***[108. 将有序数组转换为二叉搜索树](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/)***

> 给你一个整数数组 `nums` ，其中元素已经按 **升序** 排列，请你将其转换为一棵 平衡 二叉搜索树。
>
> 
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2021/02/18/btree1.jpg)
>
> > 输入：nums = [-10,-3,0,5,9]
> > 输出：[0,-3,9,-10,null,5]
> > 解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：
>
> 
>
> **示例 2：**
>
> ![img](https://assets.leetcode.com/uploads/2021/02/18/btree.jpg)
>
> > 输入：nums = [1,3]
> > 输出：[3,1]
> > 解释：[1,null,3] 和 [3,1] 都是高度平衡二叉搜索树。
>
> 
>
> 提示：
>
> * 1 <= nums.length <= 10^4^
> * -10^4^ <= nums[i] <= 10^4^
> * nums 按 严格递增 顺序排列





*左开右闭写法*

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        auto creat=[&](this auto&&dfs,int left,int right) -> TreeNode*{
            if(left==right) return nullptr; // [left,right) 
            int m = left + (right - left) / 2;
            return new TreeNode(nums[m],dfs(left,m),dfs(m+1,right));
        };
        return creat(0,nums.size());
    }
};
```



### 示例二

力扣***[1008. 前序遍历构造二叉搜索树](https://leetcode.cn/problems/construct-binary-search-tree-from-preorder-traversal/)***



> 给你一棵二叉搜索树，请你返回一棵 **平衡后** 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，请你返回任意一种。
>
> 如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 `1` ，我们就称这棵二叉搜索树是 **平衡的** 。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2021/08/10/balance1-tree.jpg)
>
> 
> >输入：root = [1,null,2,null,3,null,4,null,null]
> >输出：[2,1,3,null,null,null,4]
> >解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。
> 
>
> **示例 2：**
>
> ![img](https://assets.leetcode.com/uploads/2021/08/10/balanced2-tree.jpg)
>
> > 输入: root = [2,1,3]
> > 输出: [2,1,3]
> 
>
>
>  
>**提示：**
> 
>- 树节点的数目在 `[1, 10^4^]` 范围内。
> - 1 <= Node.val <= 10^5^



#### 理解

对于先序遍历得到的数组区间`[left,right)`，第一个元素一定是二叉树的根节点，根据BST的性质，找到在`[left,right)` 中第一个比`preorder[left]` 大的元素一定是这个根节点的左孩子，我们可以根据这个性质拆分区间。





```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        auto dfs=[&](this auto&& dfs,int left,int right)->TreeNode*{ //[left,right)
            if(left==right) return nullptr;
            TreeNode* node = new TreeNode(preorder[left]);
            //在这个区间内找到比left更大的，作为右根节点
            int bigger;
            for(bigger = left+1;bigger<right;bigger++){
                if(preorder[bigger]>preorder[left]) break;
            }
            node->left = dfs(left+1,bigger);
            node->right = dfs(bigger,right);
            return node;
        };
        return dfs(0,preorder.size());
    }
};
```



### 示例三

力扣***[2196. 根据描述创建二叉树](https://leetcode.cn/problems/create-binary-tree-from-descriptions/)***

> 给你一个二维整数数组 `descriptions` ，其中 `descriptions[i] = [parenti, childi, isLefti]` 表示 `parenti` 是 `childi` 在 **二叉树** 中的 **父节点**，二叉树中各节点的值 **互不相同** 。此外：
>
> - 如果 `isLefti == 1` ，那么 `childi` 就是 `parenti` 的左子节点。
> - 如果 `isLefti == 0` ，那么 `childi` 就是 `parenti` 的右子节点。
>
> 请你根据 `descriptions` 的描述来构造二叉树并返回其 **根节点** 。
>
> 测试用例会保证可以构造出 **有效** 的二叉树。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2022/02/09/example1drawio.png)
>
> > 输入：descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
> > 输出：[50,20,80,15,17,19]
> > 解释：根节点是值为 50 的节点，因为它没有父节点。
> > 结果二叉树如上图所示。
> 
> 
>**示例 2：**
> 
>![img](https://assets.leetcode.com/uploads/2022/02/09/example2drawio.png)
> 
>> 输入：descriptions = [[1,2,1],[2,3,0],[3,4,1]]
> > 输出：[1,2,null,null,3,4]
> > 解释：根节点是值为 1 的节点，因为它没有父节点。 
> > 结果二叉树如上图所示。 
> 
> 
> 
>
>  **提示：**
>
> - `1 <= descriptions.length <= 104`
>- `descriptions[i].length == 3`
> - `1 <= parenti, childi <= 105`
> - `0 <= isLefti <= 1`
> - `descriptions` 所描述的二叉树是一棵有效二叉树



#### 难点

* 建树并不难，如何建完树找根节点返回呢？

解答：我们可以维护一个哈希表`isRoot`，每一次建立子孩子的时候把他的父节点打上标记`true`，子孩子打上`false`。这样，根节点一定是`true`，因为他没有父亲节点给它重置成`false`，建树结束后，我们只要遍历一遍`isRoot` 检查每个节点的真假就行。

#### 方法一

[^2]

```c++

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, bool> isRoot;   // 数值对应的节点是否为根节点的哈希表
        unordered_map<int, TreeNode*> nodes;   // 数值与对应节点的哈希表
        for (const auto& d: descriptions) {
            int p = d[0];
            int c = d[1];
            bool left = d[2];
            if (!isRoot.count(p)) {
                isRoot[p] = true;
            }
            isRoot[c] = false;
            // 创建或更新节点
            if (!nodes.count(p)) {
                nodes[p] = new TreeNode(p);
            }
            if (!nodes.count(c)) {
                nodes[c] = new TreeNode(c);
            }
            if (left) {
                nodes[p]->left = nodes[c];
            } else {
                nodes[p]->right = nodes[c];
            }
        }
        // 寻找根节点
        int root = -1;
        for (const auto& [val, r]: isRoot) {
            if (r) {
                root = val;
                break;
            }
        }
        return nodes[root];
    }
};
```


#### 方法二

上面那种方法实际上是官方题解，我直接想到的是直接用一个哈希表，key对应的值`pair<TreeNode*,TreeNode*>`前一个代表了自己节点，后一个代表了自己的父亲节点，由于根节点一定没有父节点，所以最后我只要检查哪个节点`umap[node->val].second==nullptr` 即可。 但这种TLE了 ~~（苦笑）~~。

 *（超时了）*

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int,pair<TreeNode*,TreeNode*>> umap;
        TreeNode* root=nullptr;
        for(auto d:descriptions){
            TreeNode* parent = umap[d[0]].first;
            TreeNode* child = umap[d[1]].first;
            if(!parent){
                root = parent = new TreeNode(d[0]);
            }
            if(!child){
                parent = new TreeNode(d[1]);
            }
            if(d[2]==0){
                parent->right = child;
            }
            else parent->left = child;
            umap[d[0]].first = parent;
            umap[d[1]] = {child,parent};
        }
        while(umap[root->val].second){
            root = umap[root->val].second;
        }
        return root;
    }
};
```



### ==示例四==

力扣***[105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)***

很经典的的一道题

>给定两个整数数组 `preorder` 和 `inorder` ，其中 `preorder` 是二叉树的**先序遍历**， `inorder` 是同一棵树的**中序遍历**，请构造二叉树并返回其根节点。
>
> 
>
>**示例 1:**
>
>![img](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)
>
>> 输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
>> 输出: [3,9,20,null,null,15,7]
>
>
>**示例 2:**
>
>> 输入: preorder = [-1], inorder = [-1]
>> 输出: [-1]
>
>**提示:**
>
>- `1 <= preorder.length <= 3000`
>- `inorder.length == preorder.length`
>- `-3000 <= preorder[i], inorder[i] <= 3000`
>- `preorder` 和 `inorder` 均 **无重复** 元素
>- `inorder` 均出现在 `preorder`
>- `preorder` **保证** 为二叉树的前序遍历序列
>- `inorder` **保证** 为二叉树的中序遍历序列



#### 理解

<img src="https://pic.leetcode.cn/1707907886-ICkiSC-lc105-c.png" alt="1707907886-ICkiSC-lc105-c" style="zoom: 50%;" />



#### 方法一



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty())
            return nullptr;
        int val = preorder[0];
        int left_sz =
            find(inorder.begin(), inorder.end(), val) - inorder.begin();
        vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_sz);
        vector<int> pre2(preorder.begin() + 1 + left_sz, preorder.end());
        vector<int> in1(inorder.begin(), inorder.begin() + left_sz);
        vector<int> in2(inorder.begin() + left_sz + 1, inorder.end());
        TreeNode* left = buildTree(pre1, in1);
        TreeNode* right = buildTree(pre2, in2);
        return new TreeNode(val, left, right);
    }
};
```

* 时间复杂度 O(n^2^)
* 空间复杂度O(n）



#### 方法二

###### 问题

上述方法明显有两个开销最大：

* 时间开销：每次从`inorder`数组中查找`val` ，时间复杂度为O(n)
* 空间开销：每次复制数组的`vector`空间开销

###### 解决方法

* 我们可以对`inorder`数组进行预处理，放入哈希表中，这样每次查找复杂度就是O(1)了。
* 对于每次递归，我们并不需要真正传入一个数组，只要对下标进行操作就行了。

*注*：这里对下标处理时依旧遵循要**左闭右开**原则



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        unordered_map<int, int> index;
        for (int i = 0; i < n; i++) {
            index[inorder[i]] = i;
        }
        auto dfs = [&](this auto&& dfs, int pre_l, int pre_r, int in_l,
                       int in_r) -> TreeNode* {
            // 同样左闭右开
            if (pre_l == pre_r)
                return nullptr;
            int left_sz = index[preorder[pre_l]] - in_l; //这里的大小不用+1，因为我们找的是该节点。相当于已经+1了
            TreeNode* left =
                dfs(pre_l + 1, pre_l + left_sz + 1, in_l, in_l + left_sz);
            TreeNode* right =
                dfs(pre_l + left_sz + 1, pre_r, in_l + left_sz + 1, in_r);
            return new TreeNode(preorder[pre_l], left, right);
        };
        return dfs(0, n, 0, n);
    }
};
```

* 时间复杂度O(n)
* 空间复杂度O(n)

#### 推广

力扣***[106. 从中序与后序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)***

力扣***[889. 根据前序和后序遍历构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)*** （~~还是做错了😭~~）



## 七、插入、删除节点

### 示例一

力扣***[701. 二叉搜索树中的插入操作](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)***

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode*r=root;
        TreeNode*node=new TreeNode(val);
        while(true){
            if(root->val>val){ //向左走
                if(root->left){
                    root=root->left;
                }
                else {
                    root->left=node;
                    break;
                }
            }
            else if(root->val<val){
                if(root->right){
                    root=root->right;
                }
                else {
                    root->right=node;
                    break;
                }
            }
        }
        return r;
    }
};
```





### 示例二

力扣***[450. 删除二叉搜索树中的节点](https://leetcode.cn/problems/delete-node-in-a-bst/)***

题目不过多赘述

#### 分析

显然删除每个位置的节点有难有易，因此要分类讨论。

1. 删除节点为叶子节点

	* 直接删除
2. 删除节点左右有一个不存在

	* 父节点直接连到存在的那个子节点
3. 删除节点左右均存在

	* 由于这个节点的右子树上的节点值一定大于当前节点值，既然我们要删掉当前节点值，那么我们必须要用一个新值替代这个节点值。
	* 这个新值应该**均小于右子树上的值**，又大于左子树上的值。
	* 不难想到，我们交换当前节点和右子树上最小的节点，即右子树的最左边叶子节点就行了。
	* 交换这两个值，然后再**删除右子树最左边叶子节点**，返回当前节点给上面就行了。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
      if(root==NULL) return root;
      if(root->val==key){
        //情况一 叶子节点
        if(!root->left&&!root->right){
            delete root;
            return nullptr;
        }
        //情况二 左为空右不为空
        else if(!root->left&&root->right){
            auto temp_right=root->right;
            delete root;
            return temp_right;
        }
        //情况三 左不为空右为空
        else if(root->left&&!root->right){
            auto temp_left=root->left;
            delete root;
            return temp_left;
        }
        //情况四 左右均不为空
        else{
            TreeNode* node=root->right;
            while(node->left!=NULL) node=node->left;
            node->left=root->left;
            auto temp_right=root->right;
            delete root;
            return temp_right;
        }
    }
    root->left=deleteNode(root->left,key);
    root->right=deleteNode(root->right,key);
    return root;
    }
};
```



### ==示例三==

力扣***[776. 拆分二叉搜索树](https://leetcode.cn/problems/split-bst/)*** *(1810)*

>给你一棵二叉搜索树（BST）的根结点 `root` 和一个整数 `target` 。请将该树按要求拆分为两个子树：其中第一个子树结点的值都必须小于等于给定的目标值；另一个子树结点的值都必须大于目标值；树中并非一定要存在值为 `target` 的结点。
>
>除此之外，树中大部分结构都需要保留，也就是说原始树中父节点 `p` 的任意子节点 `c` ，假如拆分后它们仍在同一个子树中，那么结点 `p` 应仍为 `c` 的父结点。
>
>按顺序返回 *两个子树的根结点的数组* 。
>
> 
>
>**示例 1：**
>
>![img](https://assets.leetcode.com/uploads/2021/06/13/split-tree.jpg)
>
>> 输入：root = [4,2,6,1,3,5,7], target = 2
>> 输出：[[2,1],[4,3,6,null,null,5,7]]
>
>
>**示例 2:**
>
>> 输入: root = [1], target = 1
>> 输出: [[1],[]]
>
>
>
>**提示：**
> 
>- 二叉搜索树节点个数在 `[1, 50]` 范围内
>- `0 <= Node.val, target <= 1000`



#### 分析

**由局部到整体**

记函数返回值`vector<TreeNode*> p` p[0]为小的那个树，p[1]为大树，`{less, more}`。

* 遍历节点，当当前节点的值小于等于`target`时，说明这个节点理应属于less树。
* 但是我们的右子树上可能有满足`node->val>target`的节点，所以我们还要继续递归右子树。
* 递归右子树返回两个节点`{less,more}`。
* 已知的是当前节点属于less树，所以我们要让当前节点的右孩子指向右子树传回的子less树根节点。
* 最后返回当前节点，和右子树的more子树节点。

大于`target`的情况与上述同理，略。





```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> splitBST(TreeNode* root, int target) { //{less树, more树}
        if(root==nullptr) return {nullptr,nullptr};
        if(root->val<=target){
            // 该节点是less树上的节点
            auto p = splitBST(root->right,target); //右边可能有比target大的
            root->right = p[0]; //指向右边的less树
            return {root,p[1]};
        }
        else{ //该节点时more树上的节点
            auto p = splitBST(root->left,target);
            root->left = p[1];
            return {p[0],root};
        }
    }
};
```



## 八、层序遍历（BFS）

### 实现 

二叉树BFS一般通过队列实现。我们可以理解下图：

![102二叉树的层序遍历](https://file1.kamacoder.com/i/algo/102%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.gif)

```c++
vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = que.size();
        vector<int> vec;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}
```



### 示例一

力扣***[993. 二叉树的堂兄弟节点](https://leetcode.cn/problems/cousins-in-binary-tree/)***

> 在二叉树中，根节点位于深度 `0` 处，每个深度为 `k` 的节点的子节点位于深度 `k+1` 处。
>
> 如果二叉树的两个节点深度相同，但 **父节点不同** ，则它们是一对*堂兄弟节点*。
>
> 我们给出了具有唯一值的二叉树的根节点 `root` ，以及树中两个不同节点的值 `x` 和 `y` 。
>
> 只有与值 `x` 和 `y` 对应的节点是堂兄弟节点时，才返回 `true` 。否则，返回 `false`。
>
>  
>
> **示例 1：
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2019/02/16/q1248-01.png)**
>
> ```
> 输入：root = [1,2,3,4], x = 4, y = 3
> 输出：false
> ```
>
> **示例 2：
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2019/02/16/q1248-02.png)**
>
> ```
> 输入：root = [1,2,3,null,4,null,5], x = 5, y = 4
> 输出：true
> ```
>
> **示例 3：**
>
> **![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2019/02/16/q1248-03.png)**
>
> ```
> 输入：root = [1,2,3,null,4], x = 2, y = 3
> 输出：false
> ```
>
>  
>
> **提示：**
>
> - 二叉树的节点数介于 `2` 到 `100` 之间。
> - 每个节点的值都是唯一的、范围为 `1` 到 `100` 的整数。



#### 思路

* 在每一层路径下遍历一个父节点之后加一个哨兵节点，如果该层出现了x，y，只要该层结束后判断x，y在该层得到的path数组是否相邻。

* 实际上也不需要开一个数组，我们要的只是目标值下标，只要加一个计数器记录当前层已经遍历的下标就行了





```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        TreeNode*dummy=new TreeNode(-1);
        queue<TreeNode*> q;
        if(root) q.push(root);
        while(!q.empty()){
            int n=q.size();
            int cnt=0;
            int idx_x=-1,idx_y=-1;
            while(n--){
                TreeNode*node=q.front();
                q.pop();
                cnt++;
                if(node->val==x) idx_x = cnt;
                if(node->val==y) idx_y = cnt;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
                q.push(dummy); //站位 表示在两个父节点之间
            }
            if(idx_x!=-1&&idx_y!=-1){
                if(abs(idx_x-idx_y)==1) return false;  //不能是邻居
                else return true;
            }
            else if(idx_x==-1&&idx_y==-1) continue;
            //不在同一层的情况
            else return false;
        }
        return false;
    }
};
```

### 示例二

力扣***[1609. 奇偶树](https://leetcode.cn/problems/even-odd-tree/)***

> 如果一棵二叉树满足下述几个条件，则可以称为 **奇偶树** ：
>
> - 二叉树根节点所在层下标为 `0` ，根的子节点所在层下标为 `1` ，根的孙节点所在层下标为 `2` ，依此类推。
> - **偶数下标** 层上的所有节点的值都是 **奇** 整数，从左到右按顺序 **严格递增**
> - **奇数下标** 层上的所有节点的值都是 **偶** 整数，从左到右按顺序 **严格递减**
>
> 给你二叉树的根节点，如果二叉树为 **奇偶树** ，则返回 `true` ，否则返回 `false` 。
>
>  
>
> **示例 1：**
>
> **![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/10/04/sample_1_1966.png)**
>
> ```
> 输入：root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
> 输出：true
> 解释：每一层的节点值分别是：
> 0 层：[1]
> 1 层：[10,4]
> 2 层：[3,7,9]
> 3 层：[12,8,6,2]
> 由于 0 层和 2 层上的节点值都是奇数且严格递增，而 1 层和 3 层上的节点值都是偶数且严格递减，因此这是一棵奇偶树。
> ```
>
> **示例 2：**
>
> **![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/10/04/sample_2_1966.png)**
>
> ```
> 输入：root = [5,4,2,3,3,7]
> 输出：false
> 解释：每一层的节点值分别是：
> 0 层：[5]
> 1 层：[4,2]
> 2 层：[3,3,7]
> 2 层上的节点值不满足严格递增的条件，所以这不是一棵奇偶树。
> ```
>
> **示例 3：**
>
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/10/04/sample_1_333_1966.png)
>
> ```
> 输入：root = [5,9,1,3,5,7]
> 输出：false
> 解释：1 层上的节点值应为偶数。
> ```
>
> **示例 4：**
>
> ```
> 输入：root = [1]
> 输出：true
> ```
>
> **示例 5：**
>
> ```
> 输入：root = [11,8,6,1,3,9,11,30,20,18,16,12,10,4,2,17]
> 输出：true
> ```
>
>  
>
> **提示：**
>
> - 树中节点数在范围 [1, 10^5^] 内
> - 1 <= Node.val <= 10^6^

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        int cnt = 0;
        queue<TreeNode*> q;
        if(root) q.push(root);
        while(!q.empty()){
            int n = q.size();
            bool flag=(cnt%2==0?true:false) ; //偶数为true,奇数为false
            int pre=flag?INT_MIN:INT_MAX;
            while(n--){
                TreeNode*node=q.front();
                q.pop();
                int val=node->val;
                if(val%2!=flag) return false; //偶数层取模必须为1 true 奇数层必须为0 false
                if(flag){  //偶数 严格递增
                    if(pre>=val) return false;
                }
                else { //奇数 严格递减
                    if(pre<=val) return false;
                }
                pre = val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            cnt++;
        }
        return true;
    }
};
```

*我们可以在遍历的时候就处理～*



### 示例三

力扣***[662. 二叉树最大宽度](https://leetcode.cn/problems/maximum-width-of-binary-tree/)***



> 给你一棵二叉树的根节点 `root` ，返回树的 **最大宽度** 。
>
> 树的 **最大宽度** 是所有层中最大的 **宽度** 。
>
> 每一层的 **宽度** 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。将这个二叉树视作与满二叉树结构相同，两端点间会出现一些延伸到这一层的 `null` 节点，这些 `null` 节点也计入长度。
>
> 题目数据保证答案将会在 **32 位** 带符号整数范围内。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2021/05/03/width1-tree.jpg)
>
> ```
> 输入：root = [1,3,2,5,3,null,9]
> 输出：4
> 解释：最大宽度出现在树的第 3 层，宽度为 4 (5,3,null,9) 。
> ```
>
> **示例 2：**
>
> ![img](https://assets.leetcode.com/uploads/2022/03/14/maximum-width-of-binary-tree-v3.jpg)
>
> ```
> 输入：root = [1,3,2,5,null,null,9,6,null,7]
> 输出：7
> 解释：最大宽度出现在树的第 4 层，宽度为 7 (6,null,null,null,null,null,7) 。
> ```
>
> **示例 3：**
>
> ![img](https://assets.leetcode.com/uploads/2021/05/03/width3-tree.jpg)
>
> ```
> 输入：root = [1,3,2,5]
> 输出：2
> 解释：最大宽度出现在树的第 2 层，宽度为 2 (3,2) 。
> ```
>
>  
>
> **提示：**
>
> - 树中节点的数目范围是 `[1, 3000]`
> - `-100 <= Node.val <= 100`

*这题并不是看起来那么简单，要灵活运用二叉树的性质*



```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        unsigned long long res=1;
        queue<pair<TreeNode*,unsigned long long>> q;
        if(root){
            q.push({root,1L});
        }
        while(!q.empty()){
            int n = q.size();
            res = max(res,q.back().second-q.front().second+1);
            while(n--){
                auto [node,idx] = q.front();
                q.pop();
                if(node->left) q.push({node->left,idx*2});
                if(node->right) q.push({node->right,idx*2+1});
            }
        }
        return res;
    }
};
```









## 附题

### 附题一

力扣***[863. 二叉树中所有距离为 K 的结点](https://leetcode.cn/problems/all-nodes-distance-k-in-binary-tree/)***

> 给你一棵二叉树的根节点 `root` ，返回树的 **最大宽度** 。
>
> 树的 **最大宽度** 是所有层中最大的 **宽度** 。
>
> 每一层的 **宽度** 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。将这个二叉树视作与满二叉树结构相同，两端点间会出现一些延伸到这一层的 `null` 节点，这些 `null` 节点也计入长度。
>
> 题目数据保证答案将会在 **32 位** 带符号整数范围内。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2021/05/03/width1-tree.jpg)
>
> ```
> 输入：root = [1,3,2,5,3,null,9]
> 输出：4
> 解释：最大宽度出现在树的第 3 层，宽度为 4 (5,3,null,9) 。
> ```
>
> **示例 2：**
>
> ![img](https://assets.leetcode.com/uploads/2022/03/14/maximum-width-of-binary-tree-v3.jpg)
>
> ```
> 输入：root = [1,3,2,5,null,null,9,6,null,7]
> 输出：7
> 解释：最大宽度出现在树的第 4 层，宽度为 7 (6,null,null,null,null,null,7) 。
> ```
>
> **示例 3：**
>
> ![img](https://assets.leetcode.com/uploads/2021/05/03/width3-tree.jpg)
>
> ```
> 输入：root = [1,3,2,5]
> 输出：2
> 解释：最大宽度出现在树的第 2 层，宽度为 2 (3,2) 。
> ```
>
>  
>
> **提示：**
>
> - 树中节点的数目范围是 `[1, 3000]`
> - `-100 <= Node.val <= 100`





####  分析

![image.png](https://pic.leetcode-cn.com/c22d16e0246d36bf8ab8eda83fb138b36eb7f78de19e60baf00c989817c93777-image.png)

![c22d16e0246d36bf8ab8eda83fb138b36eb7f78de19e60baf00c989817c93777-image](https://pic.leetcode-cn.com/3592d875064a80da2b9e605d3eaba4b2f8689512c2db246985094c83892c194b-image.png)

* 首先记录这个二叉树每个节点的父节点
* 然后，我们可以建一个图，`target`为根节点，以`target`左孩子，右孩子，父节点创立一个三叉树。
* 最后，题目变成了求以`target`为根节点的三叉树距离根节点距离为k的节点数目



#### 实现

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    unordered_map<int, TreeNode*> umap; // 存该键值对应节点的父节点
    vector<int> res;
    void findParents(TreeNode* node) {
        if (node->left) {
            umap[node->left->val] = node;
            findParents(node->left);
        }
        if(node->right){
            umap[node->right->val]=node;
            findParents(node->right);
        }
    }
    void findRes(TreeNode*node,TreeNode*prev,int depth,int k){
        if(node==NULL) return;
        if(depth==k){
            res.push_back(node->val);
            return;
        }
        if(node->left!=prev){
            findRes(node->left,node,depth+1,k);
        }
        if(node->right!=prev){
            findRes(node->right,node,depth+1,k);
        }
        if(umap[node->val]!=prev){
            findRes(umap[node->val],node,depth+1,k);
        }
    }

public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        findParents(root);
        findRes(target,NULL,0,k);
        return res;
    }
};
```



#### 注意

这里的之所以还要传入一个参`prev` ，目的是为了防止我们重复递归。

> 比如 我们当前遍历到node节点了，node节点又是由他左子女节点得来的，我们再进行`findRes(node->left,node,depth+1,k)`这个递归的时候就会进入死循环，导致爆栈。



# 图论

~~图论是离散数学的一个板块，但是我们学校不给我们专业开离散数学这门课，我感觉离散数学还是挺重要的，其他很多算法都和离散数学系系相关~~



## 深度优先搜索 

### 理解

深度优先搜索，也叫DFS，我们前面在二叉树章节中已经了解过了，在一棵二叉树中，从根节点出发，到这个根节点的子孩子的算法，就可以看作是一种深度优先搜索。

> 下面这个视频很好的解释了图论中的深度优先搜索：
>
> ​	***[深度优先搜索理论基础 ](https://www.bilibili.com/video/BV1hFA8eKE6C)***



### DFS搜索过程

我们可以这样简单理解：DFS就是一种“不到黄河不回头”的一种搜索算法。

* 如果当前节点是终点（或目标点），记录这条路径。
* 然后，回溯到上一个状态，往下一个方向再次搜索。
* 如果遇到了重复搜索的节点，同样回溯到上一个状态，往下一个方向搜索。
* 上一个状态所有方向搜索完毕后，再次回到上上个状态，往像一个方向搜索。



### 例题

我们以这道例题演示DFS在图论中的作用

> 【题目描述】
>
> > 给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。请编写一个程序，找出并返回所有从节点 1 到节点 n 的路径。每条路径应以节点编号的列表形式表示。
>
> 【输入描述】
>
> > 第一行包含两个整数 N，M，表示图中拥有 N 个节点，M 条边
> >
> > 后续 M 行，每行包含两个整数 s 和 t，表示图中的 s 节点与 t 节点中有一条路径
>
> 【输出描述】
>
> > 输出所有的可达路径，路径中所有节点的后面跟一个空格，每条路径独占一行，存在多条路径，路径输出的顺序可任意。
> >
> > 如果不存在任何一条路径，则输出 -1。
> >
> > 注意输出的序列中，最后一个节点后面没有空格！ 例如正确的答案是 `1 3 5`,而不是 `1 3 5`， 5后面没有空格！
>
> 【输入示例】
>
> ```text
> 5 5
> 1 3
> 3 5
> 1 2
> 2 4
> 4 5
> ```
>
> 【输出示例】
>
> ```text
> 1 3 5
> 1 2 4 5  
> ```
>
> 【输出提示】
>
> ![](https://file1.kamacoder.com/i/algo/20240514103953.png)
>
> 用例解释：
>
> 有五个节点，其中的从 1 到达 5 的路径有两个，分别是 1 -> 3 -> 5 和 1 -> 2 -> 4 -> 5。
>
> 因为拥有多条路径，所以输出结果为：
>
> ```text
> 1 3 5
> 1 2 4 5
> ```
>
> 或
>
> ```text
> 1 2 4 5
> 1 3 5
> ```
>
> 都算正确。
>
> 数据范围：
>
> - 图中不存在自环
> - 图中不存在平行边
> - 1 <= N <= 100
> - 1 <= M <= 500



```c++
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 1节点到终点的路径

void dfs (const vector<vector<int>>& graph, int x, int n) {
    // 当前遍历的节点x 到达节点n 
    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) { // 遍历节点x链接的所有节点
        if (graph[x][i] == 1) { // 找到 x链接的节点
            path.push_back(i); // 遍历到的节点加入到路径中来
            dfs(graph, i, n); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
}

int main() {
    int n, m, s, t;
    cin >> n >> m;

    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));

    while (m--) {
        cin >> s >> t;
        // 使用邻接矩阵 表示无线图，1 表示 s 与 t 是相连的
        graph[s][t] = 1;
    }

    path.push_back(1); // 无论什么路径已经是从0节点出发
    dfs(graph, 1, n); // 开始遍历

    // 输出结果
    if (result.size() == 0) cout << -1 << endl;
    for (const vector<int> &pa : result) {
        for (int i = 0; i < pa.size() - 1; i++) {
            cout << pa[i] << " ";
        }
        cout << pa[pa.size() - 1]  << endl;
    }
}
```

---



## 广度优先搜索 





## 岛屿数量问题中的 DFS与BFS

力扣***[200. 岛屿数量](https://leetcode.cn/problems/number-of-islands/)***



> 给你一个由 `'1'`（陆地）和 `'0'`（水）组成的的二维网格，请你计算网格中岛屿的数量。
>
> 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
>
> 此外，你可以假设该网格的四条边均被水包围。
>
>  
>
> **示例 1：**
>
> ```
> 输入：grid = [
>   ['1','1','1','1','0'],
>   ['1','1','0','1','0'],
>   ['1','1','0','0','0'],
>   ['0','0','0','0','0']
> ]
> 输出：1
> ```
>
> **示例 2：**
>
> ```
> 输入：grid = [
>   ['1','1','0','0','0'],
>   ['1','1','0','0','0'],
>   ['0','0','1','0','0'],
>   ['0','0','0','1','1']
> ]
> 输出：3
> ```
>
>  
>
> **提示：**
>
> - `m == grid.length`
> - `n == grid[i].length`
> - `1 <= m, n <= 300`
> - `grid[i][j]` 的值为 `'0'` 或 `'1'`



### DFS、BFS解法



```c++
class Solution {
private:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x,
             int y) {
        if (grid[x][y] == '0' || visited[x][y] == true)
            return;
        for (int i = 0; i < 4; i++) { // 遍历四个方向
            int next_x = x + dir[i][0];
            int next_y = y + dir[i][1];
            if (next_x < 0 || next_y < 0 || next_x == grid.size() ||
                next_y == grid[0].size()) {
                continue;
            }
            visited[x][y] = true;
            dfs(grid, visited, next_x, next_y);
            // 一般有回溯 但是岛屿问题不需要回溯
        }
    }

    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x,
             int y) {
        queue<pair<int, int>> que;
        que.push({x, y});
        while (!que.empty()) {
            auto [_x, _y] = que.front();
            que.pop();
            for (int i = 0; i < 4; i++) {
                int next_x = _x + dir[i][0];
                int next_y = _y + dir[i][1];
                if (next_x < 0 || next_y < 0 || next_x == grid.size() ||
                    next_y == grid[0].size()) {
                    continue;
                }
                if (visited[next_x][next_y] || grid[next_x][next_y] == '0')
                    continue;
                visited[next_x][next_y] = true;
                que.push({next_x, next_y});
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int res=0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && visited[i][j] == false) {
                    res++;
                    dfs(grid, visited, i, j);
                    // bfs(grid, visited, i, j);
                }
            }
        }
        return res;
    }
};
```



### 简化代码

```c++
class Solution {
private:
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int countIslands(vector<vector<int>>& grid, int k) {
         int m = grid.size(), n = grid[0].size();
         auto dfs = [&](this auto&&dfs,int i,int j)->void{
            grid[i][j]=0; //标记已访问
            for(auto [dx,dy] :DIRS){
                int x = i+dx;
                int y = j+dy;
                if(0<=x&&x<m&&0<=y&&y<n&&grid[x][y]){
                    res+=dfs(x,y);
                }
            }
         };
         int cnt = 0;
         for(int i = 0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]){
                    cnt++;
                    dfs(i,j);
                }
            }
         }
         return cnt;
    }
};
```



### 岛屿问题——示例

力扣***[LCS 03. 主题空间](https://leetcode.cn/problems/YesdPw/)***

> 以扣会友」线下活动所在场地由若干主题空间与走廊组成，场地的地图记作由一维字符串型数组 `grid`，字符串中仅包含 `"0"～"5"` 这 6 个字符。地图上每一个字符代表面积为 1 的区域，其中 `"0"` 表示走廊，其他字符表示主题空间。相同且连续（连续指上、下、左、右四个方向连接）的字符组成同一个主题空间。
>
> 假如整个 `grid` 区域的外侧均为走廊。请问，不与走廊直接相邻的主题空间的最大面积是多少？如果不存在这样的空间请返回 `0`。
>
> 
>
> **示例 1：**
>
> > 输入：`grid = ["110","231","221"]`
> >
> > 输出：`1`
> >
> > 解释：4 个主题空间中，只有 1 个不与走廊相邻，面积为 1。![image.png](https://pic.leetcode.cn/1613708145-rscctN-image.png)
>
> 
>
> **示例 2：**
>
> > 输入：`grid = ["11111100000","21243101111","21224101221","11111101111"]`
> >
> > 输出：`3`
> >
> > 解释：8 个主题空间中，有 5 个不与走廊相邻，面积分别为 3、1、1、1、2，最大面积为 3。![image.png](https://pic.leetcode.cn/1613707985-KJyiXJ-image.png)
>
> **提示：**
>
> - `1 <= grid.length <= 500`
> - `1 <= grid[i].length <= 500`
> - `grid[i][j]` 仅可能为 `"0"～"5"`



#### 理解

实际上，这道题翻译过来就是：*不与0和边界相连的最大面积连通块*

我们只要对`nextX`,`nextY`进行判定就行了





```c++
class Solution {
private:
    int DIRS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

public:
    int largestArea(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        bool flag = true;
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            int res = 1;
            char c = grid[i][j];
            grid[i][j] = '#';
            for (auto [dx, dy] : DIRS) {
                int x = i + dx;
                int y = j + dy;
                if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0') {
                    flag = false;
                    continue;
                }
                if (grid[x][y] != c)
                    continue;
                res += dfs(dfs, x, y);
            }
            return res;
        };
        int mx = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != '#' && grid[i][j] != '0') {
                    flag = true;
                    int cnt = dfs(dfs, i, j);
                    if (flag)
                        mx = max(mx, cnt);
                }
            }
        }
        return mx;
    }
};
```



###  ==岛屿问题中的误区==

在岛屿问题的dfs中，如果我们要使用返回值指示某个条件，一定要注意返回值的返回时机，不能提前返回，见下题

力扣***[1254. 统计封闭岛屿的数目](https://leetcode.cn/problems/number-of-closed-islands/)***

> 二维矩阵 `grid` 由 `0` （土地）和 `1` （水）组成。岛是由最大的4个方向连通的 `0` 组成的群，封闭岛是一个 `完全` 由1包围（左、上、右、下）的岛。
>
> 请返回 *封闭岛屿* 的数目。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2019/10/31/sample_3_1610.png)
>
> ```
> 输入：grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
> 输出：2
> 解释：
> 灰色区域的岛屿是封闭岛屿，因为这座岛屿完全被水域包围（即被 1 区域包围）。
> ```
>
> **示例 2：**
>
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2019/11/07/sample_4_1610.png)
>
> ```
> 输入：grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
> 输出：1
> ```
>
> **示例 3：**
>
> ```
> 输入：grid = [[1,1,1,1,1,1,1],
>              [1,0,0,0,0,0,1],
>              [1,0,1,1,1,0,1],
>              [1,0,1,0,1,0,1],
>              [1,0,1,1,1,0,1],
>              [1,0,0,0,0,0,1],
>              [1,1,1,1,1,1,1]]
> 输出：2
> ```
>
>  
>
> **提示：**
>
> - `1 <= grid.length, grid[0].length <= 100`
> - `0 <= grid[i][j] <=1`

##### 分析

显然，这道题目只要一个变量指示我们是否遍历到了边界还是海洋，如果是边界，我们就应该改变这个`flag`，用全局变量很容易实现，如果我们用返回值的话，那么这里就有一个误区，看下面这段代码。



```c++
class Solution {
private:
    int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto dfs = [&](auto&& dfs, int i, int j) -> bool {
            grid[i][j] = 1;
            for (auto [dx, dy] : DIRS) {
                int x = i + dx;
                int y = j + dy;
                if(x<0||y<0||x==m||y==n){
                    return false;
                }
                if(grid[x][y]==1) continue;
                if(!dfs(dfs,x,y)) return false;
            }
            return true;
        };
        int res = 0;
        for(int i = 0;i < m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==0){
                    if(dfs(dfs,i,j)) res++;
                }
            }
        }
        return res;
    }
};
```

这段代码虽然能通过近一半的示例，但是不可能AC，因为这里一遇到边界就提前返回了，

在14 和 17行中，不能提前return false 不然其他方向的遍历会被中断，无法正确标记所有连通的的0，也会导致 是 否是封闭岛屿的判断错误

正确代码



```c++
class Solution {
private:
    int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto dfs = [&](auto&& dfs, int i, int j) -> bool {
            bool flag = true;
            grid[i][j] = 1;
            for (auto [dx, dy] : DIRS) {
                int x = i + dx;
                int y = j + dy;
                if(x<0||y<0||x==m||y==n){
                    flag = false; 
                    continue;
                }
                if(grid[x][y]==1) continue;
                if(!dfs(dfs,x,y)) flag = false;
            }
            return flag; //全部结束后再返回
        };
        int res = 0;
        for(int i = 0;i < m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==0){
                    if(dfs(dfs,i,j)) res++;
                }
            }
        }
        return res;
    }
};
```





## 值得重复复习的例题


###  岛屿问题与DP的结合

力扣***[2684. 矩阵中移动的最大次数](https://leetcode.cn/problems/maximum-number-of-moves-in-a-grid/)***

> 给你一个下标从 **0** 开始、大小为 `m x n` 的矩阵 `grid` ，矩阵由若干 **正** 整数组成。
>
> 你可以从矩阵第一列中的 **任一** 单元格出发，按以下方式遍历 `grid` ：
>
> - 从单元格 `(row, col)` 可以移动到 `(row - 1, col + 1)`、`(row, col + 1)` 和 `(row + 1, col + 1)` 三个单元格中任一满足值 **严格** 大于当前单元格的单元格。
>
> 返回你在矩阵中能够 **移动** 的 **最大** 次数。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2023/04/11/yetgriddrawio-10.png)
>
> ```
> 输入：grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
> 输出：3
> 解释：可以从单元格 (0, 0) 开始并且按下面的路径移动：
> - (0, 0) -> (0, 1).
> - (0, 1) -> (1, 2).
> - (1, 2) -> (2, 3).
> 可以证明这是能够移动的最大次数。
> ```
>
> **示例 2：**
>
> ```
> 输入：grid = [[3,2,4],[2,1,9],[1,1,7]]
> 输出：0
> 解释：从第一列的任一单元格开始都无法移动。
> ```
>
>  
>
> **提示：**
>
> - `m == grid.length`
> - `n == grid[i].length`
> - `2 <= m, n <= 1000`
> - 4 <= m * n <= 10^5^
> - 1 <= `grid[i][j]`<= 10^6^

#### 分析 

如果这题正常写，不挂缓存，在力扣上810个示例会挂TLE，那我们只能挂缓存，记录每个格子最远路径是多少

```c++
class Solution {
private:
    int DIRS[3][2] = {{-1,1},{0,1},{1,1}};
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size(),n = grid[0].size();
        vector<vector<int>> dp(m,vector<int>(n,-1));
        auto dfs = [&](auto&& dfs,int i,int j)->int{
            int& res =dp[i][j];
            if(res!=-1) return res;
            res=0;
            //必须要挂缓存 不然过不了
            for(auto [dx,dy]:DIRS){
                int x = i + dx;
                int y = j + dy;
                if(x<0||y<0||x>=m||y>=n){
                    continue;
                }
                if(grid[x][y]>grid[i][j]){
                    res=max(dfs(dfs,x,y)+1,res);
                }
            }  
            return res;
        };
        int ans=0;
        for(int i=0;i<m;i++){
            ans = max(ans,dfs(dfs,i,0));
        }
        return ans;
    }
};
```



### ==网格图有效路径==

力扣***[1391. 检查网格中是否存在有效路径](https://leetcode.cn/problems/check-if-there-is-a-valid-path-in-a-grid/)***  ~~这道题又挂了😅~~ 

> 给你一个 *m* x *n* 的网格 `grid`。网格里的每个单元都代表一条街道。`grid[i][j]` 的街道可以是：
>
> - **1** 表示连接左单元格和右单元格的街道。
> - **2** 表示连接上单元格和下单元格的街道。
> - **3** 表示连接左单元格和下单元格的街道。
> - **4** 表示连接右单元格和下单元格的街道。
> - **5** 表示连接左单元格和上单元格的街道。
> - **6** 表示连接右单元格和上单元格的街道。
>
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/03/21/main.png)
>
> 你最开始从左上角的单元格 `(0,0)` 开始出发，网格中的「有效路径」是指从左上方的单元格 `(0,0)` 开始、一直到右下方的 `(m-1,n-1)` 结束的路径。**该路径必须只沿着街道走**。
>
> **注意：**你 **不能** 变更街道。
>
> 如果网格中存在有效的路径，则返回 `true`，否则返回 `false` 。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/03/21/e1.png)
>
> ```
> 输入：grid = [[2,4,3],[6,5,2]]
> 输出：true
> 解释：如图所示，你可以从 (0, 0) 开始，访问网格中的所有单元格并到达 (m - 1, n - 1) 。
> ```
>
> **示例 2：**
>
> ![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/03/21/e2.png)
>
> ```
> 输入：grid = [[1,2,1],[1,2,1]]
> 输出：false
> 解释：如图所示，单元格 (0, 0) 上的街道没有与任何其他单元格上的街道相连，你只会停在 (0, 0) 处。
> ```
>
> **示例 3：**
>
> ```
> 输入：grid = [[1,1,2]]
> 输出：false
> 解释：你会停在 (0, 1)，而且无法到达 (0, 2) 。
> ```
>
> **示例 4：**
>
> ```
> 输入：grid = [[1,1,1,1,1,1,3]]
> 输出：true
> ```
>
> **示例 5：**
>
> ```
> 输入：grid = [[2],[2],[2],[2],[2],[2],[6]]
> 输出：true
> ```
>
>  
>
> **提示：**
>
> - `m == grid.length`
> - `n == grid[i].length`
> - `1 <= m, n <= 300`
> - `1 <= grid[i][j] <= 6`



#### 理解

这道题用传统的岛屿问题是不可能解决的，如果要硬套，那么我们只能写几百行`if else……` 然后嵌套dfs，但是是这种方法，很容易翻车，而且不好调试。

我们需要一个量，用于知道上一次*我们是从什么方向进入当前格子的*，比如说，当前我们在的格子是`street1` ,那么我们上一次只能从左边或右边进入当前这个位置，我们一共有6种格子，4个方向，我们可以用一个二维数组很好解决这个问题。

> **规定： 0代表向下、1代表向右、2代表向上、3代表向左**
>
> 
>
> 引入一个二维数组`pipe[i][j]`，下标 i 代表的当前格子的类型，下标 j 代表当前格子是由哪一个数值代表的方向， `pipe[i][j]`代表的数值表示这个格子从下标 j 代表方向进入的情况下，从哪一个方向出去，如果下标 j 进入时不能出去，那么这个值就是 -1如下图：
>
> * `pipe[3][2] = 3`
> * `pipe[5][3] = -1`
>
> 
>
> ![image.png](https://pic.leetcode-cn.com/7c804303caa225af4c51286c17653ee4f7f0ffff869d05fc364a645ab7683d8a-image.png)

#### 实现



```c++
class Solution {
private:
    // 0：向下 1：向右 2：向上 3：向左 -1：不可走
    int m,n; //容量
    int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int pipe[7][4] = {{-1, -1, -1, -1},//初始化pipe数组 下标0初始化为-1 方便直接访问
                      {-1, 1, -1, 3}, 
                      {0, -1, 2, -1},
                      {-1, 0, 3, -1},  
                      {-1, -1, 1, 0}, 
                      {3, 2, -1, -1},
                      {1, -1, -1, 2}};

    bool dfs(int i,int j,int dir,vector<vector<int>>& grid){  //dir代表了我从里进来的
        if(i==m-1&&j==n-1) return true;
        grid[i][j]=0;
        int x = i + DIRS[dir][0];
        int y = j + DIRS[dir][1];
        if(x<0||y<0||x>=m||y>=n||grid[x][y]==0) return false;
        int id = grid[x][y];
        if(pipe[id][dir]!=-1)  return dfs(x,y,pipe[id][dir],grid);
        else return false;
    }
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int startId = grid[0][0];
        for(int i=0;i<4;i++){ //因为有两个可能方向不为-1，所以要遍历四个方向试试
            if(pipe[startId][i]!=-1){
                if(dfs(0,0,pipe[startId][i],grid)) return true;
            }
        }
        return false;
    }
};
```

#### 反思

这种用`dir` 传入上一次的方向很常用，这是一种很好的方法，下面有几道类似思想的习题：

*   力扣***[LCP 63. 弹珠游戏](https://leetcode.cn/problems/EXvqDp/)***
*   力扣***[2061. 扫地机器人清扫过的空间个数](https://leetcode.cn/problems/number-of-spaces-cleaning-robot-cleaned/)***



### 扫雷游戏

这是道很有意思的题目～

力扣***[529. 扫雷游戏](https://leetcode.cn/problems/minesweeper/)***

> - `'M'` 代表一个 **未挖出的** 地雷，
> - `'E'` 代表一个 **未挖出的** 空方块，
> - `'B'` 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的 **已挖出的** 空白方块，
> - **数字**（`'1'` 到 `'8'`）表示有多少地雷与这块 **已挖出的** 方块相邻，
> - `'X'` 则表示一个 **已挖出的** 地雷。
>
> 给你一个整数数组 `click` ，其中 `click = [clickr, clickc]` 表示在所有 **未挖出的** 方块（`'M'` 或者 `'E'`）中的下一个点击位置（`clickr` 是行下标，`clickc` 是列下标）。
>
> 根据以下规则，返回相应位置被点击后对应的盘面：
>
> 1. 如果一个地雷（`'M'`）被挖出，游戏就结束了- 把它改为 `'X'` 。
> 2. 如果一个 **没有相邻地雷** 的空方块（`'E'`）被挖出，修改它为（`'B'`），并且所有和其相邻的 **未挖出** 方块都应该被递归地揭露。
> 3. 如果一个 **至少与一个地雷相邻** 的空方块（`'E'`）被挖出，修改它为数字（`'1'` 到 `'8'` ），表示相邻地雷的数量。
> 4. 如果在此次点击中，若无更多方块可被揭露，则返回盘面。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2023/08/09/untitled.jpeg)
>
> ```
> 输入：board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
> 输出：[["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
> ```
>
> **示例 2：**
>
> ![img](https://assets.leetcode.com/uploads/2023/08/09/untitled-2.jpeg)
>
> ```
> 输入：board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
> 输出：[["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
> ```
>
>  
>
> **提示：**
>
> - `m == board.length`
> - `n == board[i].length`
> - `1 <= m, n <= 50`
> - `board[i][j]` 为 `'M'`、`'E'`、`'B'` 或数字 `'1'` 到 `'8'` 中的一个
> - `click.length == 2`
> - `0 <= clickr < m`
> - `0 <= clickc < n`
> - `board[clickr][clickc]` 为 `'M'` 或 `'E'`

#### 理解

这一题我们要明白一个道理：为什么示例一会有一个格子为“ E ” 而不是“B”。

因为这里有一个规则二：

>  如果一个 **没有相邻地雷** 的空方块（`'E'`）被挖出，修改它为（`'B'`）

注意这里要不能与地雷相邻才能递归。同时，我们要知道，我们`click`这个点每次递归修改时是四面八方的，也就是九宫格，而不十字递归。

和正常的DFS不一样的是，我们需要对每次DFS前判断这个格子附近是否有雷，所以我们应该首先遍历九宫格，看看有没有雷，然后再遍历九宫格，这次遍历中可以DFS。

#### 实现

```c++
#include<iostream>
#include<vector>
using namespace std;

/*
* 'M' 代表一个 未挖出的 地雷，
* 'E' 代表一个 未挖出的 空方块，
* 'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的 已挖出的 空白方块，
* 数字（'1' 到 '8'）表示有多少地雷与这块 已挖出的 方块相邻，
* 'X' 则表示一个 已挖出的 地雷。
*/

/*
* 根据以下规则，返回相应位置被点击后对应的盘面：
    * 如果一个地雷（'M'）被挖出，游戏就结束了--把它改为 'X' 。
    * 如果一个 没有相邻地雷 的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的 未挖出 方块都应该被递归地揭露。
    * 如果一个 至少与一个地雷相邻 的空方块（'E'）被挖出，修改它为数字（'1' 到 '8' ），表示相邻地雷的数量。
    * 如果在此次点击中，若无更多方块可被揭露，则返回盘面。
*/

int DIRS[8][2] = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j) {
    int cnt = 0;
    visited[i][j] = true;
    for (auto [dx, dy] : DIRS) { //第一次遍历 找找周围有几个雷
        int x = i + dx;
        int y = j + dy;
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y]) {
            continue;
        }
        if (board[x][y] == 'M') cnt++;
    }
    if (cnt != 0) { //数字 停止扩散
        board[i][j] = '0' + cnt;
        return;
    }
    board[i][j] = 'B';
    for (auto [dx, dy] : DIRS) {
        int x = i + dx;
        int y = j + dy;
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visited[x][y] || board[x][y] != 'E') {
            //注意 这里有雷和数字都不应该再遍历了
            continue;
        }
        dfs(board, visited, x, y);
    }
}

int main() {
    //init
    int m, n;
    cin >> m >> n;
    vector<vector<char>> board(m, vector<char>(n));
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            cin >> board[i][j];
        }
    }
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<int> clicks(2);
    cin >> clicks[0] >> clicks[1];

    int click_r = clicks[0], click_c = clicks[1];
    if (board[click_r][click_c] == 'M') {
        board[click_r][click_c] = 'X';
    }
    else {
        dfs(board, visited, click_r, click_c);
    }

    for (auto b : board) {
        for (char d : b) {
            cout << d << "  ";
        }
        cout << endl;
    }
    return 0;
}
```



### 最大人工岛

> 给你一个大小为 `n x n` 二进制矩阵 `grid` 。**最多** 只能将一格 `0` 变成 `1` 。
>
> 返回执行此操作后，`grid` 中最大的岛屿面积是多少？
>
> **岛屿** 由一组上、下、左、右四个方向相连的 `1` 形成。
>
>  
>
> **示例 1:**
>
> ```
> 输入: grid = [[1, 0], [0, 1]]
> 输出: 3
> 解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。
> ```
>
> **示例 2:**
>
> ```
> 输入: grid = [[1, 1], [1, 0]]
> 输出: 4
> 解释: 将一格0变成1，岛屿的面积扩大为 4。
> ```
>
> **示例 3:**
>
> ```
> 输入: grid = [[1, 1], [1, 1]]
> 输出: 4
> 解释: 没有0可以让我们变成1，面积依然为 4。
> ```
>
>  
>
> **提示：**
>
> - `n == grid.length`
> - `n == grid[i].length`
> - `1 <= n <= 500`
> - `grid[i][j]` 为 `0` 或 `1`



#### 核心思路

* 首先遍历每个岛屿求他们的面积，然后给每个岛屿编号，把面积和编号存入哈希表中。
* 然后再遍历水域，看看水域上下左右是否有不同岛屿就行了，把他们依次累加。

#### 实现



```c++
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        // 核心思路
        // 首先计算每个岛屿的大小，给每个岛屿编号，用哈希表存储keys：id，val：area
        // 然后遍历整个岛屿的水域
        // 如果水域的上下左右有不同的岛屿，那么我们直接相加他们的面积再加1
        unordered_map<int, int> landId_area;
        int DIRS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = grid.size(), n = grid[0].size();
        auto dfs = [&](auto&& dfs, int i, int j, int id) -> int {
            grid[i][j] = id;
            int res = 1;
            for (auto [dx, dy] : DIRS) {
                int x = i + dx;
                int y = j + dy;
                if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] != 1 ||
                    grid[x][y] == id) {
                    continue;
                }
                res += dfs(dfs, x, y, id);
            }
            return res;
        };
        int id = 1;
        int mx_area = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    id++;
                    int temp =  dfs(dfs, i, j, id);
                    landId_area[id] = temp;
                    mx_area = max(mx_area,temp);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int sum = 1;
                    unordered_set<int> isSumed; //这个哈希集合用于指示上下左右是否有重复了id
                    for (auto [dx, dy] : DIRS) {
                        int x = i + dx;
                        int y = j + dy;
                        if (x < 0 || y < 0 || x >= m || y >= n ||
                            grid[x][y] == 0) {
                            continue;
                        }
                        if(!isSumed.contains(grid[x][y])) {
                            sum += landId_area[grid[x][y]];
                            isSumed.insert(grid[x][y]);
                        }
                    }
                    res = max(res, sum);
                }
            }
        }
        if(res == 0) { //特判一下没有岛或者全是岛的情况
            res = mx_area == 0?1:mx_area;
        }
        return res;
    }
};
```



# 回溯



## 理解

所谓回溯法，也可以叫做回溯搜索法，它是一种搜索的方式。

回溯是递归的副产品，只要有递归就会有回溯。

>   说我现在有一串字符串，我要从这个字符串中随机选n个字符组成一个新串，问我们一共有多少种新串。

显然，但n = 2 ，3 ，4 时我们只要多写几个for循环就行了，但是当n为参数或者特别大时，嵌套这么多层for循环显然是不切实际的，于是，递归（回溯）登场了



---

## 从一道经典回溯出发



力扣***[17. 电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/)***

>   给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。答案可以按 **任意顺序** 返回。
>
>   给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
>
>   ![img](https://pic.leetcode.cn/1752723054-mfIHZs-image.png)
>
>   
>
>   
>
>   **示例 1：**
>
>   ```
>   输入：digits = "23"
>   输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：digits = "2"
>   输出：["a","b","c"]
>   ```
>
>   
>
>   **提示：**
>
>   -   `1 <= digits.length <= 4`
>   -   `digits[i]` 是范围 `['2', '9']` 的一个数字



### 分析

显然我们并不确定`digitals`的长度，我们需要回溯法来帮忙，我们可以把问题拆分成一个个子问题，如下图：

![17. 电话号码的字母组合](https://file1.kamacoder.com/i/algo/20201123200304469.png)



### 实现



```c++
class Solution {
private:
    vector<string> ref = {"",    "",    "abc",  "def", "ghi",
                  "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        if(n == 0) return {};
        vector<string> res;
        string path;
        auto dfs = [&](auto&&dfs,int i)->void{
            if(i == n){
                res.push_back(path);
                return;
            }
            for(char c :ref[digits[i]-'0']){
                path.push_back(c);
                dfs(dfs,i + 1);
                //回溯
                path.pop_back(); 
            }
        };

        dfs(dfs,0);
        return res;
    }
};
```



另一种写法



```c++
class Solution {
    static constexpr string MAPPING[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
    vector<string> letterCombinations(string digits) {
        int n = digits.length();
        if (n == 0) {
            return {};
        }

        vector<string> ans;
        string path(n, 0); // 注意 path 长度一开始就是 n，不是空串

        // lambda 递归
        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == n) {
                ans.emplace_back(path);
                return;
            }
            for (char c : MAPPING[digits[i] - '0']) {
                path[i] = c; 
                dfs(i + 1);
            }
        };

        dfs(0);
        return ans;
    }
};
```

*注*：这里直接覆盖其实就是隐藏的回溯



### 复杂度

回溯只是用来代替for循环的，显然和for循环的时间复杂度是一样的

*   时间复杂**O(4^N^**)
*   空间复杂度**O(N)**



## 一、子集型的回溯

一般来说 这种题目一般**没有重复元素***而且不考虑**顺序**这种题目一般有两种做法

*   **选与不选**
*   **枚举选哪个**

### 例题

力扣***[78. 子集](https://leetcode.cn/problems/subsets/)***

>   给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。
>
>   解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,2,3]
>   输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [0]
>   输出：[[],[0]]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 10`
>   -   `-10 <= nums[i] <= 10`
>   -   `nums` 中的所有元素 **互不相同**

 

#### 选与不选的角度

对于每个下标，当我遍历到这个下标的时候，我都有两种情况： 选和不选，我们只要分别递归这两种情况即可。



```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == n) { // 子集构造完毕
                ans.emplace_back(path);
                return;
            }

            // 不选 nums[i]
            dfs(i + 1);

            // 选 nums[i]
            path.push_back(nums[i]);
            dfs(i + 1);
            path.pop_back(); // 恢复现场
        };

        dfs(0);
        return ans;
    }
};
```



*   时间复杂度**O(N*2^N^)**   ,，其中 n 为 nums 的长度。有 2 ^n^ 个子集，所以搜索树有 2^n^个叶子，每个叶子复制 path 需要 O(n) 的时间，一共需要 O(n2 n) 时间。

    

*   空间复杂度**O(N)**



#### 枚举选哪个

对每个下标 i 我们从这个下标开始往后枚举，分别代表这次选哪个



```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        int n = nums.size();
        auto dfs = [&](auto&&dfs,int i)->void{
            res.push_back(path);
            for(int j = i;j<n;j++){
                path.push_back(nums[j]);
                dfs(dfs,j+1);
                path.pop_back();
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```



### 示例一 一一 暴力之中的优化

力扣***[2212. Maximum Points in an Archery Competition](https://leetcode.cn/problems/maximum-points-in-an-archery-competition/)***



>   Alice and Bob are opponents in an archery competition. The competition has set the following rules:
>
>   1.  Alice first shoots `numArrows` arrows and then Bob shoots `numArrows` arrows.
>   2.  The points are then calculated as follows:
>       1.  The target has integer scoring sections ranging from `0` to `11` **inclusive**.
>       2.  For **each** section of the target with score `k` (in between `0` to `11`), say Alice and Bob have shot `ak` and `bk` arrows on that section respectively. If `ak >= bk`, then Alice takes `k` points. If `ak < bk`, then Bob takes `k` points.
>       3.  However, if `ak == bk == 0`, then **nobody** takes `k` points.
>
>   -   For example, if Alice and Bob both shot `2` arrows on the section with score `11`, then Alice takes `11` points. On the other hand, if Alice shot `0` arrows on the section with score `11` and Bob shot `2` arrows on that same section, then Bob takes `11` points.
>
>   You are given the integer `numArrows` and an integer array `aliceArrows` of size `12`, which represents the number of arrows Alice shot on each scoring section from `0` to `11`. Now, Bob wants to **maximize** the total number of points he can obtain.
>
>   Return *the array* `bobArrows` *which represents the number of arrows Bob shot on **each** scoring section from* `0` *to* `11`. The sum of the values in `bobArrows` should equal `numArrows`.
>
>   If there are multiple ways for Bob to earn the maximum total points, return **any** one of them.
>
>    
>
>   **Example 1:**
>
>   ![img](https://p.ipic.vip/atk73j.jpg)
>
>   ```
>   Input: numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
>   Output: [0,0,0,0,1,1,0,0,1,2,3,1]
>   Explanation: The table above shows how the competition is scored. 
>   Bob earns a total point of 4 + 5 + 8 + 9 + 10 + 11 = 47.
>   It can be shown that Bob cannot obtain a score higher than 47 points.
>   ```
>
>   **Example 2:**
>
>   ![img](https://p.ipic.vip/f4s3h2.jpg)
>
>   ```
>   Input: numArrows = 3, aliceArrows = [0,0,1,0,0,0,0,0,0,0,0,2]
>   Output: [0,0,0,0,0,0,0,0,1,1,1,0]
>   Explanation: The table above shows how the competition is scored.
>   Bob earns a total point of 8 + 9 + 10 = 27.
>   It can be shown that Bob cannot obtain a score higher than 27 points.
>   ```
>
>    
>
>   **Constraints:**
>
>   -   `1 <= numArrows <= 105`
>   -   `aliceArrows.length == bobArrows.length == 12`
>   -   `0 <= aliceArrows[i], bobArrows[i] <= numArrows`
>   -   `sum(aliceArrows[i]) == numArrows`



#### 纯暴力

最简单直观的方法：对每个下标都进行箭矢0~numArrows的判断



```c++
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        //回溯暴力
        vector<int> res;
        int max_score = 0;
        int n = aliceArrows.size();
        int arrows=0;
        vector<int> path(n,0);
        auto dfs = [&](auto&&dfs,int i)->void{
            if(arrows==numArrows){
                int tempSum = 0;
                for(int j=0;j<n;j++){
                    if(path[j]>aliceArrows[j]){
                        tempSum+=j;
                    }
                }
                if(max_score<tempSum){
                    max_score = tempSum;
                    res = path;
                }
                return;
            }
            for(int j = i;j<n;j++){
                path[j]++;
                arrows++;
                dfs(dfs,j); //可以重复选 我就从自己开始
                // 回溯
                arrows--;
                path[j]--;
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```



*   时间复杂度O(2^N^)
*   空间复杂度O(N)

那么显然，这种方法显然是过不了的，因为它对每个下标都进行了从0～numArrows的判断，但我们能从上面的代码一步步优化



#### 优化思路

显然，上述代码最大的开销是每次对每个下标都进行了对arrow从0～11的判断，我们能否不用一次一次累加，直接转到某个特定的数？

我们可以用一点点贪心的思想，对于这个下标分数，我们也有两种情况：

*   一是我们选择这个下标作为累加分数，换句话来说，也就是我这一分我可以选择恰好赢过Alice，
*   二是我们可以选择不赢Alice，我一根箭也不浪费在这个下标上。

*   对于多余的箭矢，我们全部存放在下标0上

#### 优化实现

```c++
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        vector<int> res;
        int max_score = 0;
        int n = aliceArrows.size();
        int arrows=0;
        vector<int> path(n,0);
        int path_score = 0;
        auto dfs = [&](auto&&dfs,int i)->void{
            if(arrows<=numArrows&&path_score>max_score){
                path[0] = numArrows - arrows; //把多余的箭放在第一个下标
                res = path;
                max_score = path_score;
            }
            if(arrows>numArrows) return;
            for(int j = i;j<n;j++){
                path[j] = aliceArrows[j]+1;
                path_score+=j;
                arrows +=(aliceArrows[j]+1);
                dfs(dfs,j+1);
                // 回溯
                arrows-=(aliceArrows[j]+1);
                path_score-=j;
                path[j] = 0;
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```



#### BUG

上面的代码在力扣上提交会在第58个用例的时候WA。如下

<img src="https://p.ipic.vip/9w3239.png" alt="image-20251220155747233" style="zoom: 50%;" />

发现只有下标0的箭矢挂了。

而且奇怪的是，这里不多反而少了4根箭，为什么呢？

这里挂的原因就是，第一次我们从0开始的时候，根据上面的贪心原则，我们会把path[0]弄成4，然后以下标0位已选了条件开始，继续dfs，相当于这时候总箭矢为85了，我们没有对path[0]进行回溯操作，因为我们每次对下标0是覆盖操作，最后一次覆盖，也就是遍历到分数11的时候，剩下了17根箭。

之所以这个用例挂了，是因为在这个情况下:`dfs(dfs,0)`，*从0开始选了4根箭使恰好大于Alice的贪心策略这个刚好符合答案*。

#### 修改

我们只要规避掉0这个下标就行了，让0只充当一个“工具人”的作用，也就是只用来代元，而不做实质上的选择。



```c++
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        vector<int> res;
        int max_score = 0;
        int n = aliceArrows.size();
        int arrows=0;
        vector<int> path(n,0);
        int path_score = 0;
        auto dfs = [&](auto&&dfs,int i)->void{
            if(arrows<=numArrows&&path_score>max_score){
                path[0] = numArrows - arrows; //把多余的箭放在第一个下标
                res = path;
                max_score = path_score;
                path[0] = 0;
            }
            if(arrows>numArrows) return;
            for(int j = i;j<n;j++){
                path[j] = aliceArrows[j]+1;
                path_score+=j;
                arrows +=(aliceArrows[j]+1);
                dfs(dfs,j+1);
                // 回溯
                arrows-=(aliceArrows[j]+1);
                path_score-=j;
                path[j] = 0;
            }
        };
        dfs(dfs,1); //下标0是一个替元的操作，不需要考虑
        return res;
    }
};
```



*   时间复杂度O(N^2^)
*   空间复杂度O(N)，存放path数组的开销



### 示例二 一一 回溯的简单应用

力扣***[1255. Maximum Score Words Formed by Letters](https://leetcode.cn/problems/maximum-score-words-formed-by-letters/)***

>   Given a list of `words`, list of single `letters` (might be repeating) and `score` of every character.
>
>   Return the maximum score of **any** valid set of words formed by using the given letters (`words[i]` cannot be used two or more times).
>
>   It is not necessary to use all characters in `letters` and each letter can only be used once. Score of letters `'a'`, `'b'`, `'c'`, ... ,`'z'` is given by `score[0]`, `score[1]`, ... , `score[25]` respectively.
>
>    
>
>   **Example 1:**
>
>   ```
>   Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
>   Output: 23
>   Explanation:
>   Score  a=1, c=9, d=5, g=3, o=2
>   Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5) with a score of 23.
>   Words "dad" and "dog" only get a score of 21.
>   ```
>
>   **Example 2:**
>
>   ```
>   Input: words = ["xxxz","ax","bx","cx"], letters = ["z","a","b","c","x","x","x"], score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
>   Output: 27
>   Explanation:
>   Score  a=4, b=4, c=4, x=5, z=10
>   Given letters, we can form the words "ax" (4+5), "bx" (4+5) and "cx" (4+5) with a score of 27.
>   Word "xxxz" only get a score of 25.
>   ```
>
>   **Example 3:**
>
>   ```
>   Input: words = ["leetcode"], letters = ["l","e","t","c","o","d"], score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
>   Output: 0
>   Explanation:
>   Letter "e" can only be used once.
>   ```
>
>    
>
>   **Constraints:**
>
>   -   `1 <= words.length <= 14`
>   -   `1 <= words[i].length <= 15`
>   -   `1 <= letters.length <= 100`
>   -   `letters[i].length == 1`
>   -   `score.length == 26`
>   -   `0 <= score[i] <= 10`
>   -   `words[i]`, `letters[i]` contains only lower case English letters.



#### 分析

简单枚举`word[i]`即可，每次有两个状态：取和不取。



```c++
class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters,vector<int>& score) {
        unordered_map<char, int> umap;
        for (char letter : letters) {
            umap[letter]++;
        }
        int n = words.size();
        int s = 0;
        int maxScore = 0;
        auto dfs = [&](auto&& dfs, int i) {
            if (i == n) {
                maxScore = max(maxScore, s);
                return;
            }
            // 不选
            dfs(dfs, i + 1);
            // 选
            bool flag = true;
            string word = words[i];
            for (char ch : word) {
                if (umap[ch]-- == 0) {
                    flag = false; //库存不够了
                }
                s += score[ch - 'a'];
            }
            if(flag){
                dfs(dfs,i+1);
            }
            //回溯
            for(char ch:word){
                umap[ch]++;
                s-=score[ch-'a'];
            }
        };
        dfs(dfs,0);
        return maxScore;
    }
};
```



## 二、分割型回溯

所谓的分割型回溯，本质上还是子集型的回溯，我们不妨看看下面这道题

### 示例一



力扣***[131. 分割回文串](https://leetcode.cn/problems/palindrome-partitioning/)***

>   给你一个字符串 `s`，请你将 `s` 分割成一些 子串，使每个子串都是 **回文串** 。返回 `s` 所有可能的分割方案。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：s = "aab"
>   输出：[["a","a","b"],["aa","b"]]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：s = "a"
>   输出：[["a"]]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= s.length <= 16`
>   -   `s` 仅由小写英文字母组成



#### 分析

如果我们把当前遍历到的下标当作“刀”，在这个下标对应字母的后面“切一刀”。每次**遍历我们都可以选择“切和不切“**,这根本上就是子集型的回溯。

#### 实现

##### 写法一



```c++
class Solution {
    bool is_palindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> ans;
        vector<string> path;

        // 考虑 i 后面的逗号怎么选
        // start 表示当前这段回文子串的开始位置
        auto dfs = [&](this auto&& dfs, int i, int start) {
            if (i == n) { // s 分割完毕
                ans.emplace_back(path);
                return;
            }

            // 不分割，不选 i 和 i+1 之间的逗号
            if (i < n - 1) { // i=n-1 时只能分割
                // 考虑 i+1 后面的逗号怎么选
                dfs(i + 1, start);
            }

            // 分割，选 i 和 i+1 之间的逗号（把 s[i] 作为子串的最后一个字符）
            if (is_palindrome(s, start, i)) {
                path.emplace_back(s.substr(start, i - start + 1));
                // 考虑 i+1 后面的逗号怎么选
                // start=i+1 表示下一个子串从 i+1 开始
                dfs(i + 1, i + 1);
                path.pop_back(); // 恢复现场
            }
        };

        dfs(0, 0);
        return ans;
    }
};
```



##### 写法二

```c++
class Solution {
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> ans;
        vector<string> path;

        // 考虑 s[i] ~ s[n-1] 怎么分割
        auto dfs = [&](this auto&& dfs, int i) {
            if (i == n) { // s 分割完毕
                ans.emplace_back(path);
                return;
            }
            for (int j = i; j < n; j++) { // 枚举子串的结束位置
                if (isPalindrome(s, i, j)) {
                    path.push_back(s.substr(i, j - i + 1)); // 分割！
                    // 考虑剩余的 s[j+1] ~ s[n-1] 怎么分割
                    dfs(j + 1);
                    path.pop_back(); // 恢复现场
                }
            }
        };

        dfs(0);
        return ans;
    }
};
```





### 示例二

力扣***[93. 复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/)***

>   **有效 IP 地址** 正好由四个整数（每个整数位于 `0` 到 `255` 之间组成，且不能含有前导 `0`），整数之间用 `'.'` 分隔。
>
>   -   例如：`"0.1.2.201"` 和` "192.168.1.1"` 是 **有效** IP 地址，但是 `"0.011.255.245"`、`"192.168.1.312"` 和 `"192.168@1.1"` 是 **无效** IP 地址。
>
>   给定一个只包含数字的字符串 `s` ，用以表示一个 IP 地址，返回所有可能的**有效 IP 地址**，这些地址可以通过在 `s` 中插入 `'.'` 来形成。你 **不能** 重新排序或删除 `s` 中的任何数字。你可以按 **任何** 顺序返回答案。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：s = "25525511135"
>   输出：["255.255.11.135","255.255.111.35"]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：s = "0000"
>   输出：["0.0.0.0"]
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：s = "101023"
>   输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= s.length <= 20`
>   -   `s` 仅由数字组成

#### 实现



```c++
class Solution {
private:
    bool check(string temp){
        int n = temp.size();
        if(n > 3 || n==0) return false;
        if(n>1 &&temp[0] == '0') return false;
        int t = stoi(temp);
        if(t > 255) return false;
        return true;
    }
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.size();
        vector<string> res;
        if(n<4 || n > 12) return res;
        int point = 0;
        auto dfs = [&](auto&&dfs,int i,int start,string path){
            if(point == 3){
                string temp = s.substr(start,s.size()-start);
                if(check(temp)){
                    path+=temp;
                    res.push_back(path);    
                }
                return;
            }

            for (int len = 1; len <= 3 && start + len <= n; len++){
                string temp = s.substr(start,len);
                if(check(temp)){
                    point++;
                    dfs(dfs,len+i,len+i,path+temp+'.');
                    point--;
                }
            }

        };
        dfs(dfs,0,0,"");
        return res;
    }
};
```

## 三、组合型回溯

所谓的组合型回溯，实际上就是子集型的回溯，但是有个数约束

### 组合

力扣***[77. 组合](https://leetcode.cn/problems/combinations/)***

>   给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。
>
>   你可以按 **任何顺序** 返回答案。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：n = 4, k = 2
>   输出：
>   [
>     [2,4],
>     [3,4],
>     [2,3],
>     [1,2],
>     [1,3],
>     [1,4],
>   ]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：n = 1, k = 1
>   输出：[[1]]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= n <= 20`
>   -   `1 <= k <= n`

#### 选与不选

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        auto dfs = [&](auto&&dfs,int i)->void{
            int d = k - path.size();
            if(d == 0){
                res.push_back(path);
                return;
            }
            for(int j = i;j>=d;j--){
                path.push_back(j);
                dfs(dfs,j-1);
                path.pop_back();
            }
        };
        dfs(dfs,n);
        return res; 
    }
};
```

#### 枚举

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        auto dfs = [&](auto&&dfs,int i)->void{
            int d = k - path.size();  //还要遍历 d 个数
            if(d == 0){
                res.push_back(path);
                return;
            }
            //选和不选
            if(i > d){  //如果 i <= d 说明这个数一定要选，不然根本实现不了答案的个数要求
                dfs(dfs,i-1);
            }

            path.push_back(i);
            dfs(dfs,i-1);
            path.pop_back();
        };
        dfs(dfs,n);
        return res;
    }
};
```

 



### 括号生成

力扣***[22. 括号生成](https://leetcode.cn/problems/generate-parentheses/)***

>   数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：n = 3
>   输出：["((()))","(()())","(())()","()(())","()()()"]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：n = 1
>   输出：["()"]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= n <= 8`

#### 分析

如果我们仔细观察，我们发现，在当前要添加的下标中，我们一定要满足左括号的数量大于等于右括号，否则根本不可能成立。 我们可以依据这个数学条件，进行回溯。

#### 实现

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        auto dfs = [&](auto&&dfs,string path,int left,int right)->void{
            //抓住一个点 左括号>= 右括号 才使得永远有效 
            if(left > n || right > left) return;
            if(path.size() == 2*n){
                res.push_back(path);
            }
            dfs(dfs,path + '(',left+1,right);
            dfs(dfs,path +')',left,right+1);
        };
        dfs(dfs,"",0,0);
        return res;
    }
};
```

## 四、排列型回溯

排列型回溯，与组合型回溯最大的区别就是排列型回溯的答案要求有顺序，但是组合型回溯却不要求顺序。

### 全排列
力扣***[46.全排列](https://leetcode.cn/problems/permutations/description/#:~:text=%E6%B5%8B%E8%AF%95%E7%BB%93%E6%9E%9C-,46.%20%E5%85%A8%E6%8E%92%E5%88%97,-%E5%B7%B2%E8%A7%A3%E7%AD%94)***

>   给定一个**不含重复数字**的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,2,3]
>   输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [0,1]
>   输出：[[0,1],[1,0]]
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：nums = [1]
>   输出：[[1]]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 6`
>   -   `-10 <= nums[i] <= 10`
>   -   `nums` 中的所有整数 **互不相同**

#### 分析

这是一道最经典的排列型回溯问题，显然这里不能再套用以前组合型问题的模版了，如果把排列搜索过程画成一棵树，那么显然这是一颗完全树，而组合型问题的树并不是，他不允许上一个分支选过的元素再选了，而组合型问题允许，但是这里不允许在同一个分支下重复选。我们需要维护一个变量，用于指示这个分支下我们已经选了哪些元素。

我们可以用哈希集合或者一个布尔数组维护。这里用布尔数组来实现。

#### 实现



```C++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> path(n);
        vector<bool> on_path(n,false);
        auto dfs =[&](auto&&dfs,int i){
            if(i == n){
                res.push_back(path);
                return;
            }
            for(int j = 0;j<n;j++){ //从0开始遍历 但是子集型是从i开始遍历
                if(!on_path[j]){
                    on_path[j] = true;
                    path[i] = nums[j];
                    dfs(dfs,i+1);
                    on_path[j] = false;
                }
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```

*注*： 我们这里`dfs`传入的参数 `i`并不和以前的组合型回溯一样代表原数组下标或者数字，这里的`i`代表的是每个分支下每个***答案的下标***。



### 破解锁的最少时间 I —— 隐藏在暗处的回溯

力扣***[3376. 破解锁的最少时间 I](https://leetcode.cn/problems/minimum-time-to-break-locks-i/)***

>   Bob 被困在了一个地窖里，他需要破解 `n` 个锁才能逃出地窖，每一个锁都需要一定的 **能量** 才能打开。每一个锁需要的能量存放在一个数组 `strength` 里，其中 `strength[i]` 表示打开第 `i` 个锁需要的能量。
>
>   Bob 有一把剑，它具备以下的特征：
>
>   -   一开始剑的能量为 0 。
>   -   剑的能量增加因子 `X` 一开始的值为 1 。
>   -   每分钟，剑的能量都会增加当前的 `X` 值。
>   -   打开第 `i` 把锁，剑的能量需要到达 **至少** `strength[i]` 。
>   -   打开一把锁以后，剑的能量会变回 0 ，`X` 的值会增加一个给定的值 `K` 。
>
>   你的任务是打开所有 `n` 把锁并逃出地窖，请你求出需要的 **最少** 分钟数。
>
>   请你返回 Bob 打开所有 `n` 把锁需要的 **最少** 时间。
>
>    
>
>   **示例 1：**
>
>   **输入：**strength = [3,4,1], K = 1
>
>   **输出：**4
>
>   **解释：**
>
>   | 时间 | 能量 | X    | 操作          | 更新后的 X |
>   | ---- | ---- | ---- | ------------- | ---------- |
>   | 0    | 0    | 1    | 什么也不做    | 1          |
>   | 1    | 1    | 1    | 打开第 3 把锁 | 2          |
>   | 2    | 2    | 2    | 什么也不做    | 2          |
>   | 3    | 4    | 2    | 打开第 2 把锁 | 3          |
>   | 4    | 3    | 3    | 打开第 1 把锁 | 3          |
>
>   无法用少于 4 分钟打开所有的锁，所以答案为 4 。
>
>   **示例 2：**
>
>   **输入：**strength = [2,5,4], K = 2
>
>   **输出：**5
>
>   **解释：**
>
>   | 时间 | 能量 | X    | 操作          | 更新后的 X |
>   | ---- | ---- | ---- | ------------- | ---------- |
>   | 0    | 0    | 1    | 什么也不做    | 1          |
>   | 1    | 1    | 1    | 什么也不做    | 1          |
>   | 2    | 2    | 1    | 打开第 1 把锁 | 3          |
>   | 3    | 3    | 3    | 什么也不做    | 3          |
>   | 4    | 6    | 3    | 打开第 2 把锁 | 5          |
>   | 5    | 5    | 5    | 打开第 3 把锁 | 7          |
>
>   无法用少于 5 分钟打开所有的锁，所以答案为 5 。
>
>    
>
>   **提示：**
>
>   -   `n == strength.length`
>   -   `1 <= n <= 8`
>   -   `1 <= K <= 10`
>   -   1 <= strength[i] <= 10^6^

#### 分析

由于每个锁都要选，而且开锁顺序影响着答案。我们可以转换成一个开锁顺序的排列。

设当前已经开了`i`个锁，也就是我们要排列剩下的锁的排序。

那么当前的`X = i + k*i`。对于要剩下要开的锁设下标为`j`,那么开`j`这个锁所需要的时间是：$\lceil \frac a b \rceil$

关于向上取整的运算，我们有:

>   $\lceil \frac a b \rceil = \lfloor \frac {a-1} b \rfloor + 1$

#### 实现

``` c++
class Solution {
public:
    int findMinimumTime(vector<int>& strength, int k) {
        int res = INT_MAX;
        int n = strength.size();
        vector<bool> done(n,false);
        auto dfs =[&](auto&&dfs,int i,int times) ->void{
            if(times >= res ) return;
            if(i == n){
                res = times;
                return;
            }
            int x = 1 + k*i;
            for(int j = 0;j<n;j++){
                if(!done[j]){
                    done[j]  = true;
                    dfs(dfs,i+1,times+(strength[j] - 1)/x + 1) ; 
                    done[j] = false;
                }
            }
        };
        dfs(dfs,0,0);
        return res;
    }
};
```



### ==N皇后问题 —— 从回溯到位运算的优化==

学习了回溯法，我们可以解决一个举世闻名的问题 —— N皇后问题

力扣***[51. N 皇后](https://leetcode.cn/problems/n-queens/)***

>   按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
>
>   **n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。
>
>   给你一个整数 `n` ，返回所有不同的 **n 皇后问题** 的解决方案。
>
>   每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)
>
>   ```
>   输入：n = 4
>   输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
>   解释：如上图所示，4 皇后问题存在两个不同的解法。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：n = 1
>   输出：[["Q"]]
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= n <= 9`

#### 分析

N皇后问题也可以看作是一种排列问题，对于每一行，我们又可以枚举每个`col`下标，看看这个位置`[row,col]`放皇后是否合法。最直观的思路就是放皇后的时候都检查一次这个位置当前是否合法，如果合法就继续递归。



#### 实现一

```c++
class Solution {
private:
    bool check(const vector<string>& board,int x,int y){
        //检查行
        for(int r = x - 1;r >= 0;r--){
            if(board[r][y] == 'Q'){
                return false;
            }
        }
        //检查左上对角
        for(int r = x - 1,c = y - 1;r>=0&&c>=0;r--,c--){
            if(board[r][c] == 'Q') return false;
        }
        //检查右上对角
        for(int r = x - 1,c = y + 1;r>=0&&c<board[0].size();r--,c++){
            if(board[r][c] == 'Q') return false;
        }
        return true;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n,string(n,'.'));
        auto dfs =[&](auto&&dfs,int r)->void{
            if(r == n){
                res.push_back(board);
                return;
            }
            for(int c = 0;c < n;c++){
                board[r][c] = 'Q';
                if(check(board,r,c)){
                    dfs(dfs,r+1);
                }
                board[r][c] = '.';
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```

*   时间复杂度 $O(n!)$
*   空间复杂度$O(1)$ 不计答案的开销。



#### 优化

显然，实现一每一次检查的时间复杂度是$O(n)$ 的，能不能让每一次检查的时间复杂度降到$O(1)$呢？

可以，我们可以**“用空间换时间”**，维护三个一维布尔数组，`col`、`diag_left`、`diag_right`，分别指示列上，对角线上的存放情况。对于对角线，我们发现两侧的对角线有一个特点：`x + y` 、 `x - y`分别为一个定值，所以我们用这样的方法判断是否合法就可以了。

#### 实现二



```c++
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n,string(n,'.'));
        vector<bool> diag1(2 * n - 1, false), diag2(2 * n - 1, false),col(n, false);
        auto dfs = [&](auto&& dfs, int r) -> void {
            if (r == n) {
                res.push_back(board);
                return;
            }
            for (int c = 0; c < n; c++) {
                int d1 = r + c;
                int d2 = r - c + n - 1; // r - c最小也不过就是 [-n+1] 这样可以完美防止越界
                if (!diag1[d1] && !diag2[d2] && !col[c]) {
                    diag1[d1] = diag2[d2] = col[c] = true;
                    board[r][c] = 'Q';
                    dfs(dfs,r+1);
                    board[r][c] = '.';
                    diag1[d1] = diag2[d2] = col[c] = false;
                }
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```

*   时间复杂度$O(n!)$
*   空间复杂度$O(n)$ 开销就是三个维护的数组

*注*:虽然实现一和实现二的时间复杂度是一样的，但是当数据比较小的时候，实现二的运行时间一定优于实现二。但`n>10`左右的时候 ~~这两种方法时间也没有什么区别了）~~

#### 进一步优化

对于每个格子，我们有两个状态，空和皇后，我们可以把它抽象成0、1分别代表空闲和皇后

>   举例 n = 4的时候 如果我再第一行第二个格子放了皇后
>
>   | row  | col  |        diag_left         |        diag_right        |
>   | :--: | :--: | :----------------------: | :----------------------: |
>   |  0   | 0100 |           0100           |           0100           |
>   |  1   | 0101 | （左移一位）1000 –> 1010 | （右移一位）0010 –> 0010 |
>   |  2   | 1101 | （左移一位）0100 –> 1100 | （右移一位）0001 –> 1001 |
>   |  3   | 1111 | （左移一位）1000 –>1010  | （右移一位）0000 –> 0010 |

具体实现就是每一行我们遍历到`col`时，我们可以`int queen = 1 << n - 1 - c;`  也就是吧queen移动到某个位置下面，将这个`queen`和上面三个变量进行**与运算** 如果三个的结果都是0，说明这个位置在对角线上和列上都合法，可以放皇后。

#### 实现三

```c++
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        // 位运算实现
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        auto dfs = [&](auto&& dfs, int r, int col, int diag_left,
                       int diag_right) -> void {
            if (r == n) {
                res.push_back(board);
                return;
            }
            for (int c = 0; c < n; c++) {
                int queen = 1 << n - 1 - c;
                if (!(queen & col) && !(queen & diag_left) && !(queen & diag_right)) {
                    board[r][c] = 'Q';
                    dfs(dfs, r + 1, col | queen, (diag_left | queen) << 1,(diag_right | queen) >> 1);
                    board[r][c] = '.';
                }
            }
        };
        dfs(dfs, 0, 0, 0, 0);
        return res;
    }
};
```



### 构建字典序最大的可行序列 —— 从隐藏在回溯中的贪心算法优化



力扣***[1718. 构建字典序最大的可行序列](https://leetcode.cn/problems/construct-the-lexicographically-largest-valid-sequence/)***

题目略，点击超链接即可



#### 解法一

本题思路很明确，我们只要组合数字到`[0,2*n-1]`这些下标之下即可。



```c++
class Solution {
private:
    bool compare(vector<int>& path, vector<int>& res) {
        for (int i = 0; i < res.size(); i++) {
            if (path[i] == res[i])
                continue;
            else if (path[i] > res[i])
                return true;
            else
                return false;
        }
        return false;
    }

public:
    vector<int> constructDistancedSequence(int n) {
        unordered_map<int, int> umap; // 数字 -> 第一次出现的下标
        for (int i = 2; i <= n; i++)
            umap[i] = -1; // 不用下标1 没有意义
        vector<bool> on_path(n + 1, false);
        vector<int> res(2 * n - 1, -1);
        vector<int> path(2 * n - 1, 0);
        auto dfs = [&](auto&& dfs, int i) -> void {

            if(!compare(path,res)) return;
            if (i == 2 * n - 1) {
                res = path;
                return;
            }
            // 如果这个位置放1 和不放1
            // 放1
            if (!on_path[1]) {
                on_path[1] = true;
                path[i] = 1;
                dfs(dfs, i + 1);
                on_path[1] = false;
            }

            // 不放1
            for (int num = n; num >= 1; num--) {
                if (on_path[num])
                    continue;
                int& first_idx = umap[num];
                if (first_idx == -1) { // 之前未曾出现
                    first_idx = i;
                    path[i] = num;
                    dfs(dfs, i + 1);
                    first_idx = -1;
                } else {
                    if (i - first_idx == num) {
                        on_path[num] = true;
                        path[i] = num;
                        dfs(dfs, i + 1);
                        on_path[num] = false;
                    }
                }
            }
        };
        dfs(dfs, 0);
        return res;
    }
};
```

#### ==解法二==

但是，解法一不能AC，到n=8的时候就挂了。TLE，因为本质上解法一还是太暴力了，我们枚举了每个下标进行组合，实际上，我们根本需不需要哈希表记录第一次出现的下标，因为当我们第一次放这个数字`i`的时候，第二个数字一定就已经确定了。

其次，题目的目的是字典序最大，这里可以贪心一下，我们应该尽量把大的数字放在靠前的下标，这样可以减少无效的递归遍历的次数。

我们可以用一个布尔值作回溯参数的返回值，可以剪去很多支



```c++
class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        int len = 2*n-1;
        vector<int> path(len,0);
        vector<bool> used(n+1,false);
        //新思路 返回值用bool 可以减去很多没必要的分支
        auto dfs = [&](auto&&dfs,int i)->bool{
            while(i < len && path[i]!=0){ //找到最近的没有填充的格子
                i++;
            }
            if(i == len){
                return true;
            }
            for(int num = n;num>=1;num--){ //贪心优化 从大的开始排
                if(used[num]) continue;
                //计算第二个数字的间距
                int secondIdx = num == 1?i:i + num;
                if(secondIdx < len && path[secondIdx] == 0){
                    path[i]  = num;
                    path[secondIdx] = num;
                    used[num] = true;
                    //我用的贪心思路，第一次返回true的时候一定就是最优解，直接返回即可
                    if(dfs(dfs,i+1)) return true;
                    used[num] = false;
                    path[i]  = 0;
                    path[secondIdx] = 0;
                }
            }
            //如果一直不合法，说明前面的有的下标填错了，直接返回false传给上面
            return false;
        };
        dfs(dfs,0);
        return path;
    }
};
```



### 解数独

这也是一道经典且有点困难的算法题。

但是初见时很容易思维固化，因为这道题递归的方法和之前的题目不一样。

力扣***[37. 解数独](https://leetcode.cn/problems/sudoku-solver/)***

题目略；

#### 解法一

最直接简单的方法，每个情况下的每个格子，和1～9折九个数字，看看这个数字在当前格是否生效

```c++
class Solution {
private:
    bool check(vector<vector<char>>& board,int r,int c,char num){
        //检查行
        for(int i = 0;i < 9;i++){
            if(board[r][i] == num) return false;
        }
        //检查列
        for(int i = 0;i < 9;i++){
            if(board[i][c] == num) return false;
        }
        //检查九宫格
        int r_grid = (r / 3) * 3;
        int c_grid = (c / 3) * 3;
        for(int i = r_grid;i < r_grid +3;i++){
            for(int j = c_grid;j<c_grid+3;j++){
                if(board[i][j] == num) return false;
            }
        }
        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        auto dfs = [&](auto&&dfs) -> bool{
            for(int r = 0;r<9;r++){
                for(int c = 0;c<9;c++){
                    if(board[r][c] != '.') continue;
                    for(char ch = '1';ch<='9';ch++){
                        if(check(board,r,c,ch)){
                            board[r][c] = ch;
                            if(dfs(dfs)) return true;
                            board[r][c] = '.';
                        }
                    }
                    return false; //九个数都试完了 还不行，说明上面就放错了
                }
            }
            return true;
        };
        dfs(dfs);
    }
};
```

#### 解法二

其实只要预处理一下，把个空格的下标选出来，也可以看作是一个组合问题

```c++
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        bool row_on[9][9]{};
        bool col_on[9][9]{}; // col_on[j][x] 表示第j列是否含有x
        bool box_on[3][3][9]{}; // box_on[i][j][x] 表示第（i,j)个宮是否含有x
        vector<pair<int, int>> empty_pos; // 空格子的位置
        // 初始化 确实是一个优秀的初始化
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char b = board[i][j];
                if (b == '.') {
                    empty_pos.push_back({i, j});
                } else {
                    int x = b - '1';
                    row_on[i][x] = col_on[j][x] = box_on[i / 3][j / 3][x] = true;
                }
            }
        }
        auto dfs = [&](auto&&dfs,int i)->bool{
            if(i == empty_pos.size()){
                return true;
            }
            auto& [r,c] = empty_pos[i];
            for(int num = 1;num <= 9;num++){
                int idx = num - 1;
                if(row_on[r][idx] || col_on[c][idx] || box_on[r / 3][c / 3][idx]){
                    continue;
                } 
                row_on[r][idx]  = col_on[c][idx] = box_on[r / 3][c / 3][idx] = true;
                board[r][c] = num + '0';
                if(dfs(dfs,i+1)) return true;
                board[r][c] = '.';
                row_on[r][idx]  = col_on[c][idx] = box_on[r / 3][c / 3][idx] = false;
            }
            return false;
        };
        dfs(dfs,0);
    }
};
```



## 五、有重复元素的回溯

### 子集 II

力扣***[90. 子集 II](https://leetcode.cn/problems/subsets-ii/)***

题目略

实际上就是在子集型回溯加了一个有重复元素的条件。

我们仍然可以从选和不选以及枚举这两个方面解题

#### 选和不选

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> path;
        int n = nums.size();
        auto dfs=[&](auto&&dfs,int i)->void{
            //选和不选
            if(i == n){
                res.push_back(path);
                return;
            }
            //选x
            path.push_back(nums[i]);
            dfs(dfs,i+1);
            path.pop_back();

            //不选x 那么相当于后面所有的x都不选
            int x = nums[i];
            while(i < n && nums[i] == x){
                i++;
            }
            dfs(dfs,i);
        };
        dfs(dfs,0);
        return res;
    }
};
```

#### 枚举

```c++
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> path;
        auto dfs=[&](auto&&dfs,int index)->void{
            res.push_back(path);
            for(int i = index;i < nums.size();i++){
                if(i > index && nums[i] == nums[i-1]) continue;
                path.push_back(nums[i]);
                dfs(dfs,i+1);
                path.pop_back();
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```



### ==非递减子序列 — — 不能改变原数组的顺序==

力扣***[491. 非递减子序列](https://leetcode.cn/problems/non-decreasing-subsequences/)***

>   给你一个整数数组 `nums` ，找出并返回所有该数组中不同的递增子序列，递增子序列中 **至少有两个元素** 。你可以按 **任意顺序** 返回答案。
>
>   数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [4,6,7,7]
>   输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [4,4,3,2,1]
>   输出：[[4,4]]
>   ```

#### 理解

这道题目和前面的*子集II* 这道题不一样，对于子集，我们的答案和原数组的顺序无关。

但是对于子序列，答案的顺序和原数组的顺序息息相关。所以，我们并不能通过之前的**“先排序，再去重”**

我们可以通过哈希表来实现这种去重逻辑

#### 实现

```c++
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        int n = nums.size();
        auto dfs =[&](auto&&dfs,int i,int pre)->void{
            if(path.size()>1){
                res.push_back(path);
            }
            unordered_set<int> uset;//横向去重
            //哈希集合不用去重 这只是一个局部变量 用于指示搜索树这一层出现了哪个元素
            for(int j = i;j < n;j++){
                int x = nums[j];
                if(uset.contains(x)) continue;
                if(pre > x) continue;
                uset.insert(x);
                path.push_back(x);
                dfs(dfs,j+1,x);
                path.pop_back();
            }
        };
        dfs(dfs,0,INT_MIN);
        return res;
    }
};
```

其实这个和之前排列型型回溯很像，但是这里是使用对每一层进行去重，而排列型回溯是使用used数组对每一个分支进行去重。



### 全排列II

力扣***[47. 全排列 II](https://leetcode.cn/problems/permutations-ii/)***

和前面两道题目不一样，这道题是排列型回溯，也就是只能用枚举法解决。

题目略，只是在全排列的基础上加了有重复元素

#### 分析

*   重复来自哪？

    >   以示例 1 nums=[1,1,2] 为例。如果按照 46 题的做法，在递归的过程中，会发生如下两种情况：
    >
    >   ​	第一个位置填 nums[0]，第二个位置填 nums[1]。
    >   ​	第一个位置填 nums[1]，第二个位置填 nums[0]。
    >   这两种填法，最终都会得到排列 [1,1,2]，重复了。

*   如何解决重复呢？

>   对于当前遍历的下标，由上面的例子我们知道，对于答案数组的某个下标`i`，只能出现一次`num`,因此我们应该在全排列，也就是说，如果我们的原数组出现了多次数字`num`,我们只能在答案的每个下标使用一次，我们需要对搜索树的每一层也做去重。

#### 解法一 —— 哈希

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        int n = nums.size();
        vector<bool> used(nums.size(),false);
        auto dfs= [&](auto&&dfs,int i){
            if(i == n){
                res.push_back(path);
                return;
            }
            unordered_set<int> uset;
            for(int j = 0;j<n;j++){
                int x = nums[j];
                if(used[j] || uset.contains(x)) continue;
                path.push_back(x);
                uset.insert(x);
                used[j] = true;
                dfs(dfs,i+1);
                used[j] = false;
                path.pop_back();
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```

#### 解法二 —— 哈希的优化

我们知道，对原数组排序，如果有多个`num`我们只要枚举一个第一次出现`num`给当前下标。

也就是如果在填 *nums*[1]=1 的时候，发现 *nums*[0]=1 在这个分支上还没有填过，那么就不使用这种填法，直接 continue。

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        sort(nums.begin(),nums.end());
        int n = nums.size();
        vector<bool> used(n,false);
        auto dfs = [&](auto&&dfs,int i)->void{
            if(i == n){
                res.push_back(path);
                return;
            }
            for(int j = 0;j<n;j++){
                if(used[j]) continue;
                if(j>0 && nums[j-1] == nums[j] && !used[j-1]) continue; 
                path.push_back(nums[j]);
                used[j] = true;
                dfs(dfs,i+1);
                used[j] = false;
                path.pop_back();
            }
        };
        dfs(dfs,0);
        return res;
    }
};
```



## 六、搜索

很多题目的回溯法并不会显然得呈现，搜索问题就是这样，我们需要根据题目设计回溯法，事实上，在实际解题过程中，如果没有告诉你题目类型，直接想出回溯法。

换句话说，搜索问题就是回溯算法的应用



### 黄金矿工

力扣***[1219. 黄金矿工](https://leetcode.cn/problems/path-with-maximum-gold/)***

>   你要开发一座金矿，地质勘测学家已经探明了这座金矿中的资源分布，并用大小为 `m * n` 的网格 `grid` 进行了标注。每个单元格中的整数就表示这一单元格中的黄金数量；如果该单元格是空的，那么就是 `0`。
>
>   为了使收益最大化，矿工需要按以下规则来开采黄金：
>
>   -   每当矿工进入一个单元，就会收集该单元格中的所有黄金。
>   -   矿工每次可以从当前位置向上下左右四个方向走。
>   -   每个单元格只能被开采（进入）一次。
>   -   **不得开采**（进入）黄金数目为 `0` 的单元格。
>   -   矿工可以从网格中 **任意一个** 有黄金的单元格出发或者是停止。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
>   输出：24
>   解释：
>   [[0,6,0],
>    [5,8,7],
>    [0,9,0]]
>   一种收集最多黄金的路线是：9 -> 8 -> 7。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
>   输出：28
>   解释：
>   [[1,0,7],
>    [2,0,6],
>    [3,4,5],
>    [0,3,0],
>    [9,0,20]]
>   一种收集最多黄金的路线是：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= grid.length, grid[i].length <= 15`
>   -   `0 <= grid[i][j] <= 100`
>   -   最多 **25** 个单元格中有黄金。



#### 分析 —— 为什么要回溯？

第一眼看到这道题，其实有点像岛屿问题，但仔细一看，这道题目并不是让我们找最大金子容量，我们不能回头走，所以是一个路线问题，我们期望是找到最大黄金路线，所以我们要用回溯法试探。实际上，后面的其他图论中dfs大部分都是依赖回溯。



```c++
class Solution {
private:
    int DIRS[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int res = 0;
        int cnt = 0;
        int m = grid.size(),n = grid[0].size(); 
        auto dfs = [&](auto&&dfs,int x,int y)->void{
            int temp = grid[x][y];
            cnt += temp;
            grid[x][y] = 0;
            for(auto [dx,dy]:DIRS){
                int xx = x + dx;
                int yy = y + dy;
                if(xx < 0||yy<0||xx >=m ||yy>=n ||grid[xx][yy]==0) continue;
                dfs(dfs,xx,yy);  
            }
            res = max(res,cnt);
            grid[x][y] = temp;
            cnt -= temp;
        };
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(grid[i][j]!=0){
                    dfs(dfs,i,j);
                }
            }
        }
        return res;
    }
};
```

### 给表达式添加运算符

力扣***[282. 给表达式添加运算符](https://leetcode.cn/problems/expression-add-operators/)***

>   给定一个仅包含数字 `0-9` 的字符串 `num` 和一个目标值整数 `target` ，在 `num` 的数字之间添加 **二元** 运算符（不是一元）`+`、`-` 或 `*` ，返回 **所有** 能够得到 `target` 的表达式。
>
>   注意，返回表达式中的操作数 **不应该** 包含前导零。
>
>   **注意**，一个数字可以包含多个数位。
>
>    
>
>   **示例 1:**
>
>   ```
>   输入: num = "123", target = 6
>   输出: ["1+2+3", "1*2*3"] 
>   解释: “1*2*3” 和 “1+2+3” 的值都是6。
>   ```
>
>   **示例 2:**
>
>   ```
>   输入: num = "232", target = 8
>   输出: ["2*3+2", "2+3*2"]
>   解释: “2*3+2” 和 “2+3*2” 的值都是8。
>   ```
>
>   **示例 3:**
>
>   ```
>   输入: num = "3456237490", target = 9191
>   输出: []
>   解释: 表达式 “3456237490” 无法得到 9191 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= num.length <= 10`
>   -   `num` 仅含数字
>   -   -2<sup>31</sup> <= target <= 2<sup>31</sup> - 1





```c++
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        int n = num.size();
        auto dfs = [&](auto&& dfs, int i, string path, long multi,long sum) -> void {
            if (i == n) {
                if (sum == target) {
                    res.push_back(path);
                }
                return;
            }
          
            long val = 0;
            for (int j = i; j < n; j++) {
                if(num[i]=='0'&&j>i) break;
                val = val * 10 + num[j] - '0';
                if(i == 0){
                    dfs(dfs,j+1,to_string(val),val,val);
                    continue;
                }
                dfs(dfs, j + 1, path + '+' + to_string(val), val, sum + val);
                dfs(dfs, j + 1, path + '-' + to_string(val), -val, sum - val);
                dfs(dfs, j + 1, path + '*' + to_string(val), val * multi,sum - multi + multi * val);
            }
        };
        dfs(dfs,0,"",0,0);
        return res;
    }
};
```



# 动态规划

动态规划，是新手必须迈过的一道坎，有人说，动态规划至少做200+以上才算入门 ~~太可怕了~~ 

动态规划 (*Dynamic Programming*)  简称*DP*，它的核心思想是**将复杂问题分解为子问题，解决子问题并存储其结果，以避免重复计算，从而提高效率**

## 从递归入手DP

力扣***[198. 打家劫舍](https://leetcode.cn/problems/house-robber/)***

>   你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。
>
>   给定一个代表每个房屋存放金额的非负整数数组，计算你 **不触动警报装置的情况下** ，一夜之内能够偷窃到的最高金额。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：[1,2,3,1]
>   输出：4
>   解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
>        偷窃到的最高金额 = 1 + 3 = 4 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：[2,7,9,3,1]
>   输出：12
>   解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
>        偷窃到的最高金额 = 2 + 9 + 1 = 12 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 100`
>   -   `0 <= nums[i] <= 400`

### 分析

前面我们的递归，有选和不选这种方法，在打家劫舍这道题目中，我们同样可以遵循“选还是不选”这种思想。

建议观看***[动态规划入门：从记忆化搜索到递推【基础算法精讲 17】](https://leetcode.cn/link/?target=https%3A%2F%2Fwww.bilibili.com%2Fvideo%2FBV1Xj411K7oF%2F)***

从最朴素的选和不选这种思想开始，由于最左边或者最右边涉及的限制最小，我们考虑从最左边或者最右边开始选起。

>   例子:`[2,3,4,6]`
>
>   如果我们从第四个开始选起，我们有选和不选这两种选择。我们可以画出下面的搜索树
>
>   <img src="https://p.ipic.vip/fstmjo.png" alt="image-20251229211744066" style="zoom: 50%;" />
>
>   我们可以退出递推公式:
>
>   `dfs[i] = max(dfs[i-1],dfs[i-2]+nums[i-1]`
>
>   解释： `dfs[i]`表示的是前`i`个房子能收获的最大金额，我们有两种情况推出当前最大金额：
>
>   1.   我选择不偷这个房子，也就是当前的金额由前`i-1`的最大金额，也就`dfs[i-1]`
>   2.   我选择偷这个房子，也就是说我不能偷上个房子，当前的金额由前`i-2`个最大金额  + 上一个房子的金额——:`nums[i] + dfs[i-2]`

### 实现

#### 最直接的递归



```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        auto dfs = [&](this auto&&dfs,int i)->int{
            if(i < 0) return 0;
            return max(dfs(i-1),dfs(i-2)+nums[i]);
        };
        return dfs(nums.size()-1);
    }
};
```

每个数字有选和不选两种方法，时间复杂度是O（2^n^)，显然会超时。

#### 记忆化搜索

观察搜索树，我们发现我们重复计算了“2”和“1”这两个节点，也就是说，我们完全没有必要新算一个节点，直接把已经计算过的节点放入一个哈希表中，如果计算过直接取出来就行了，这样就可以把时间复杂度降低到O（n）级别了，但我们额外开了空间。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> memo(101,-1);
        auto dfs = [&](this auto&&dfs,int i)->int{
            if(i < 0) return 0;
            if(memo[i] != -1) 
                memo[i] = max(dfs(i-1),dfs(i-2)+nums[i]); //这都超时？
            return memo[i];
        };
        return dfs(nums.size()-1);
    }
};
```



我有点不理解力扣，这凭什么超时？一定要记忆化搜索？ ~~sb力扣~~

#### 递推

甚至我们可以去除递归中的归，1:1翻译成递推

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if(len == 1) return nums[0];
        int len = nums.size();
        vector<int> dp(len, -1);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]); // 选和不选 找最大的
        for (int i = 2; i < len; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[len - 1];
    }
};
```

#### 空间优化

上述代码空间复杂度为O( n )的。但是显然我们只需要用到前一项和前前一项的数据。我们维护这个常量空间就可以了。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if(len == 1) return nums[0];
        int prepre = nums[0];
        int pre = max(nums[0],nums[1]);
        for (int i = 2; i < len; i++) {
            int curr = max(pre,prepre + nums[i]);
            prepre = pre;
            pre = curr;
        }
        return pre;
    }
};
```

#### 总结

对于一般的入门dp，我们都可以把把这个问题先从我们熟悉的递归入手，再通过记忆化优化时间复杂度，最后得到递推公式1:1还原为dp。

并且，从回溯法传过来的“选和不选”这种思想，在DP中也很常见



## 一、入门DP

### 爬楼梯问题

#### 最小花费爬楼梯

力扣***[746. 使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/)***

>   给你一个整数数组 `cost` ，其中 `cost[i]` 是从楼梯第 `i` 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
>
>   你可以选择从下标为 `0` 或下标为 `1` 的台阶开始爬楼梯。
>
>   请你计算并返回达到楼梯顶部的最低花费。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：cost = [10,15,20]
>   输出：15
>   解释：你将从下标为 1 的台阶开始。
>   - 支付 15 ，向上爬两个台阶，到达楼梯顶部。
>   总花费为 15 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：cost = [1,100,1,1,1,100,1,1,100,1]
>   输出：6
>   解释：你将从下标为 0 的台阶开始。
>   - 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
>   - 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
>   - 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
>   - 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
>   - 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
>   - 支付 1 ，向上爬一个台阶，到达楼梯顶部。
>   总花费为 6 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `2 <= cost.length <= 1000`
>   -   `0 <= cost[i] <= 999`



##### 记忆化搜索

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> memo(n + 1, -1);
        auto dfs = [&](auto&& dfs, int i) -> int {
            if(i<=1) return 0;
            int& res = memo[i];
            if(res !=-1) return res;
            return res = min(dfs(dfs,i-1)+cost[i-1],dfs(dfs,i-2)+cost[i-2]);
        };
        return dfs(dfs,n);
    }
};
```

##### 1:1翻译成递推

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        //递推
        int n = cost.size();
        int f0 = 0,f1 =0;
        for(int i = 2;i<n+1;i++){
            int f2 = min(f0+cost[i-2],f1+cost[i-1]);
            f0 = f1;
            f1 = f2;
        }
        return f1;
    }
};
```

#### 组合总和IV

力扣***[377. 组合总和 Ⅳ](https://leetcode.cn/problems/combination-sum-iv/)***

>   给你一个由 **不同** 整数组成的数组 `nums` ，和一个目标整数 `target` 。请你从 `nums` 中找出并返回总和为 `target` 的元素组合的个数。
>
>   题目数据保证答案符合 32 位整数范围。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,2,3], target = 4
>   输出：7
>   解释：
>   所有可能的组合为：
>   (1, 1, 1, 1)
>   (1, 1, 2)
>   (1, 2, 1)
>   (1, 3)
>   (2, 1, 1)
>   (2, 2)
>   (3, 1)
>   请注意，顺序不同的序列被视作不同的组合。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [9], target = 3
>   输出：0
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 200`
>   -   `1 <= nums[i] <= 1000`
>   -   `nums` 中的所有元素 **互不相同**
>   -   `1 <= target <= 1000`

##### 分析

实际上这道题也是爬楼类型的题目， 没吃从*nums*中取出一个数爬*num*层，阶梯数为*target*

##### 记忆化搜索（超时）

回溯也可以，但是百分之百超时。。。

```c++
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int cnt = 0;
        //2 记忆化搜索
        vector<int> memo(target+1,0);
        memo[0] = 1; //递归出口
        auto dfs =[&](auto&&dfs,int i)->int{
            if(i < 0) return 0;
            int& res = memo[i];
            if(res!=0) return res;
            for(int num:nums){
                res += dfs(dfs,i-num);
            }
            return res;
        };
        dfs(dfs,target);
        return memo[target];
    }
};
```

##### 递推

```c++
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int cnt = 0;
        //1:1动态规划
        vector<unsigned long long> dp(target+1,0);
        dp[0] = 1;
        for(int i = 1;i<target+1;i++){
            for(int num:nums){
                if(i - num < 0) continue;
                dp[i]+=dp[i - num];
            }
        }
        return dp.back();
    }
};
```



#### ==统计打字方案数==

力扣***[2266. 统计打字方案数](https://leetcode.cn/problems/count-number-of-texts/)***

>   Alice 在给 Bob 用手机打字。数字到字母的 **对应** 如下图所示。
>
>   ![img](https://pic.leetcode.cn/1722224025-gsUAIv-image.png)
>
>   为了 **打出** 一个字母，Alice 需要 **按** 对应字母 `i` 次，`i` 是该字母在这个按键上所处的位置。
>
>   -   比方说，为了按出字母 `'s'` ，Alice 需要按 `'7'` 四次。类似的， Alice 需要按 `'5'` 两次得到字母 `'k'` 。
>   -   注意，数字 `'0'` 和 `'1'` 不映射到任何字母，所以 Alice **不** 使用它们。
>
>   但是，由于传输的错误，Bob 没有收到 Alice 打字的字母信息，反而收到了 **按键的字符串信息** 。
>
>   -   比方说，Alice 发出的信息为 `"bob"` ，Bob 将收到字符串 `"2266622"` 。
>
>   给你一个字符串 `pressedKeys` ，表示 Bob 收到的字符串，请你返回 Alice **总共可能发出多少种文字信息** 。
>
>   由于答案可能很大，将它对 `109 + 7` **取余** 后返回。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：pressedKeys = "22233"
>   输出：8
>   解释：
>   Alice 可能发出的文字信息包括：
>   "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae" 和 "ce" 。
>   由于总共有 8 种可能的信息，所以我们返回 8 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：pressedKeys = "222222222222222222222222222222222222"
>   输出：82876089
>   解释：
>   总共有 2082876103 种 Alice 可能发出的文字信息。
>   由于我们需要将答案对 109 + 7 取余，所以我们返回 2082876103 % (109 + 7) = 82876089 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= pressedKeys.length <= 105`
>   -   `pressedKeys` 只包含数字 `'2'` 到 `'9'` 。

##### 实现

```c++
class Solution {
private:
    int MOD = 1e9 + 7;
public:
    int countTexts(string pressedKeys) {
        int n = pressedKeys.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1; // 下标i代表长度为i时一共有几种解法
        for (int i = 1; i <= n; i++) {
            char ch = pressedKeys[i-1];
            int times = (ch == '7' || ch == '9') ? 4 : 3; //最大向左移次数
            for(int j = 1;j<=times;j++){ //从1开始 从0开始没有意义 i-0还是i
                if(i-j<0 || pressedKeys[i-j]!=ch) break;
                dp[i] =(dp[i]+dp[i-j])%MOD;
            }
        }
        return dp[n];
    }
};
```



### 打家劫舍

在*从递归入手DP*中已经给了一个打家劫舍问题的例子了，以下我们不做讲解。



####  打家劫舍II

力扣***[213. 打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)***

题目略,实际上就是加了一个左边和右边已经联通了。

##### 分析

实际上，对于环形数组，我们都可以把它转换成线性数组。

> * 如果我选择了*nums[0]* 那么我就不能再选*nums[1]*和*nums[n-1]*这两个位置了。问题转换从**下标2开始到下标n-2的线性打家劫舍子问题了**。
> * 如果我不选*nums[0]*，问题变为从**下标2开始到下标n-1*的线性打家劫舍子问题了**。

##### 实现

```c++
class Solution {
    int rob1(vector<int>&nums,int start,int end){  //[start,end)
        int f0= 0,f1 = 0;
        for(int i = start;i<end;i++){
            int f = max(f0 + nums[i],f1);
            f0 = f1;
            f1 = f;
        }
        return f1;
    }
public:
    int rob(vector<int>& nums) {  
        int n = nums.size();
        return max(rob1(nums,1,n),nums[0]+rob1(nums,2,n-1));
    }
};
```



#### 统计放置房子的方法
力扣***[2320. 统计放置房子的方式数](https://leetcode.cn/problems/count-number-of-ways-to-place-houses/description/)***

##### 分析
> 对于第 i 块地皮,我们放和不放房子两种操作：
> * 放房子，那么对于 i-1 块地皮，我们不能放置，对于i-2的地皮 我们无论它放还是放 ： *f(i) = f(i-2)*;
> * 不放房子，那么对于i-1块地皮，我们无论它放还是不放房子： * f(i) = f(i-1)*;
>
> 我们可以导出递推公式： 
>
> ​								$ f(i) = f(i-1) + f(i+1) $



##### 实现
```c++
class Solution {
private:
    int MOD =1e9 +7;
public:
    int countHousePlacements(int n) {
        //考虑第i个地皮放与不放
        //若i不放,则i-1可以放可不放
        //若i放,则i-2可放可不放房
        long long f0 = 1,f1 = 2;//没有地皮也有一种方案数
        for(int i = 2;i<=n;i++){
            int f =(f0 + f1)%MOD;
            f0 = f1;
            f1 = f;
        }
        return (f1*f1)%MOD;
    }
};
```



#### 删除并获得点数 —— ==值域打家劫舍问题I==

力扣***[ 740.删除并获得点数](https://leetcode.cn/problems/delete-and-earn/)***

> 给你一个整数数组 `nums` ，你可以对它进行一些操作。
>
> 每次操作中，选择任意一个 `nums[i]` ，删除它并获得 `nums[i]` 的点数。之后，你必须删除 **所有** 等于 `nums[i] - 1` 和 `nums[i] + 1` 的元素。
>
> 开始你拥有 `0` 个点数。返回你能通过这些操作获得的最大点数。
>
>  
>
> **示例 1：**
>
> ```
> 输入：nums = [3,4,2]
> 输出：6
> 解释：
> 你可以执行下列步骤：
> - 删除 4 获得 4 个点数，因此 3 也被删除。nums = [2]。
> - 之后，删除 2 获得 2 个点数。nums = []。
> 总共获得 6 个点数。
> ```
>
> **示例 2：**
>
> ```
> 输入：nums = [2,2,3,3,3,4]
> 输出：9
> 解释：
> 你可以执行下列步骤：
> - 删除 3 获得 3 个点数。所有的 2 和 4 也被删除。nums = [3,3]。
> - 之后，再次删除 3 获得 3 个点数。nums = [3]。
> - 再次删除 3 获得 3 个点数。nums = []。
> 总共获得 9 个点数。
> ```
>
>  
>
> **提示：**
>
> - 1 <= *nums.length* <= 2 * 10^4^
> -  1 <=*nums[i]* <= 10^4^
> 

##### 分析

*nums[i-1]*和*nums[i+1]* 不能选，这很我们之前的打家劫舍问题，打家劫舍的下标换成了这里的值域，我们是否可以转化一下呢？

> 把 nums 转换成一个值域数组 a，其中 a[i] 表示 nums 中的等于 i 的元素之和。上面的例子中，a=[0,0,4,9,4]。因为 nums 中有 3 个 3，所以 a[3]=3+3+3=9。
>
> 计算数组 a 的  198. 打家劫舍，即为答案



##### 实现

```c++
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int mx = INT_MIN;
        for(int num:nums){
            if(num > mx) mx = num;
        }
        vector<int> vec(mx+1,0); //初始化为0，下面有妙用
        for(int num:nums){
            vec[num]+=num;
        }
        int f0 = 0,f1 = 0;
        for(int i =0;i<vec.size();i++){
            int f = max(f0 + vec[i],f1);
            f0 = f1;
            f1 = f;
        }
        return f1;
    }
};
```



#### 施咒的最大伤害 —— ==值域打家劫舍II==

力扣***[3186. 施咒的最大总伤害](https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/)***

> 一个魔法师有许多不同的咒语。
>
> 给你一个数组 `power` ，其中每个元素表示一个咒语的伤害值，可能会有多个咒语有相同的伤害值。
>
> 已知魔法师使用伤害值为 `power[i]` 的咒语时，他们就 **不能** 使用伤害为 `power[i] - 2` ，`power[i] - 1` ，`power[i] + 1` 或者 `power[i] + 2` 的咒语。
>
> 每个咒语最多只能被使用 **一次** 。
>
> 请你返回这个魔法师可以达到的伤害值之和的 **最大值** 。
>
>  
>
> **示例 1：**
>
> **输入：**power = [1,1,3,4]
>
> **输出：**6
>
> **解释：**
>
> 可以使用咒语 0，1，3，伤害值分别为 1，1，4，总伤害值为 6 。
>
> **示例 2：**
>
> **输入：**power = [7,1,6,6]
>
> **输出：**13
>
> **解释：**
>
> 可以使用咒语 1，2，3，伤害值分别为 1，6，6，总伤害值为 13 。
>
>  
>
> **提示：**
>
> - *1 <= power.length <= 10^5^*
> - *1 <= power[i] <= 10^9^*

##### 分析

上题的值域打家劫舍直接开了一个容量为数组最大值的新*dp*数组，之所以能AC，是因为上面的数据量不大*nums[i]*最大也才是*10^5^*，随便过。

而这道题给的数据范围很大*10^9^* 如果再开一个连续数组，一定会**MLE** ，我们需要对这些数进行离散化处理，而不是只是简单的连续储存值域。



如何实现离散化处理呢？

我们可以把所有值和出现频率组成一个二元组，存入一个数组中，在对这个数组进行排序（按值域排序)。然后和正常的打家劫舍问题一样。

> 对于当前要处理的下标*i* 我们有两种选择：
>
> * 对这个下标释放魔咒，也就是说，值域为*power[i]-1*、*power[i]-2* 的魔咒我们不能再选了，我们在上上面的离散数组中找到最大的**小于*power[i]-2* 的下标*j* 就可以了**。*（用二分查找或者直接暴力都可以）*
> * 忽略这个下标，也就是说，当前*dp[i] = dp[i-1]*
>
> 据此，我们得到了递推公式：
>
> ​							$dp[i] = max(dp[i-1],dp[j] + power* freq)$



##### 实现

```c++
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int,int> umap;
        for(int n:power){
            umap[n]++;
        }
        vector<pair<int,int>> a(umap.begin(),umap.end());
        sort(a.begin(),a.end());
        int n = a.size();
        vector<long long> dp(n+1,0); //技巧： 我们开一个n+1容量的数组，有效避免了i-1下标的越界和j的越界
        for(int i = 0;i < n;i++){
            int j = i;
            auto& [x,c] = a[i];
            while(j > 0 && a[j-1].first >= x-2){
                j --;
            }
            dp[i+1] = max(dp[i],dp[j]+(long long)x*c); // 注意dp数组整体平移了1个 所以这里不用i-1和j-1
        }
        return dp[n];
    }
};
```

#### ==思维拓展==： 先入为主的误区 —— 解决智力问题

力扣***[解决智力问题](https://leetcode.cn/problems/solving-questions-with-brainpower/)***

> 给你一个下标从 **0** 开始的二维整数数组 `questions` ，其中 `questions[i] = [pointsi, brainpoweri]` 。
>
> 这个数组表示一场考试里的一系列题目，你需要 **按顺序** （也就是从问题 `0` 开始依次解决），针对每个问题选择 **解决** 或者 **跳过** 操作。解决问题 `i` 将让你 **获得** `pointsi` 的分数，但是你将 **无法** 解决接下来的 `brainpoweri` 个问题（即只能跳过接下来的 `brainpoweri` 个问题）。如果你跳过问题 `i` ，你可以对下一个问题决定使用哪种操作。
>
> - 比方说，给你 `questions = [[3, 2], [4, 3], [4, 4], [2, 5]]` ：
>   - 如果问题 `0` 被解决了， 那么你可以获得 `3` 分，但你不能解决问题 `1` 和 `2` 。
>   - 如果你跳过问题 `0` ，且解决问题 `1` ，你将获得 `4` 分但是不能解决问题 `2` 和 `3` 。
>
> 请你返回这场考试里你能获得的 **最高** 分数。
>
>  
>
> **示例 1：**
>
> ```
> 输入：questions = [[3,2],[4,3],[4,4],[2,5]]
> 输出：5
> 解释：解决问题 0 和 3 得到最高分。
> - 解决问题 0 ：获得 3 分，但接下来 2 个问题都不能解决。
> - 不能解决问题 1 和 2
> - 解决问题 3 ：获得 2 分
> 总得分为：3 + 2 = 5 。没有别的办法获得 5 分或者多于 5 分。
> ```
>
> **示例 2：**
>
> ```
> 输入：questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
> 输出：7
> 解释：解决问题 1 和 4 得到最高分。
> - 跳过问题 0
> - 解决问题 1 ：获得 2 分，但接下来 2 个问题都不能解决。
> - 不能解决问题 2 和 3
> - 解决问题 4 ：获得 5 分
> 总得分为：2 + 5 = 7 。没有别的办法获得 7 分或者多于 7 分。
> ```
>
>  
>
> **提示：**
>
> - *1 <= questions.length <= 10^5^*
> - `questions[i].length == 2`
> - *1 <= points[i], brainpower[i] <= 10^5^*

##### 分析

起初刚做这道题目的时候，我想用记忆话搜索，但是最后递归的时候总写不出来，实际上我还是陷入了思维陷阱，我先入为主地认为记忆化搜索就是从后向前递归，实际上如果仔细观察题干，这道题目其实需要从前向后递归，因为前面的选和不选影响到了后面是否递归，这里有点像**二叉树的后序遍历，把答案传回给*memo[0]* ** 。值得仔细理解`

##### 实现



```c++
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        //记忆化搜索
        int n = questions.size();
        vector<long long> memo(n,-1);
        auto dfs = [&](auto&&dfs,int i)->long long{
            if(i >= n) return 0;
            long long& res = memo[i];
            if(res != -1) return res;
            return res = max(dfs(dfs,i+1),dfs(dfs,i+questions[i][1]+1)+questions[i][0]);
        };
        dfs(dfs,0);
        return memo[0];
    }
};
```



```c++
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> f(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            int j = min(i + questions[i][1] + 1, n);
            f[i] = max(f[i + 1], f[j] + questions[i][0]);
        }
        return f[0];
    }
};
```



#### ==答疑==
>  问：在 1:1 翻译的过程中，如何根据记忆化搜索，确定递推数组（DP 数组）的大小？为什么有时候要开 n+1 大小的数组，有时候要开 n+2 大小的数组？



> 答：看记忆化搜索的参数的范围（最小值和最大值）。例如 i 最小是 −1（递归边界也算），最大是 n−1（递归入口），那么一共有 n+1 个不同的 i，就需要开 n+1 大小的 DP 数组。如果 i 最小是 −2，最大是 n−1，一共有 n+2 个不同的 i，就需要开 n+2 大小的 DP 数组。



---



### ==总结 I==



* 对于上面所有的初级DP，我们都有记忆化搜索和严格DP这两种写法。

  > 通过我的观察，我发现：
  >
  > * 记忆化搜索，也就是递归，**递归开始时传入的参数总和严格DP中for循环传入的参数是相反的**
  > * 同时，我还发现对于这两种方法，实际上两种的**递推、递归公式实际上是相同的**，最好的例子就是上面那道思维推展：
  >   * 递归:	`res = max(dfs(dfs,i+1),dfs(dfs,i+questions[i][1]+1)+questions[i][0])`，
  >   * 严格dp:       `f[i] = max(f[i + 1], f[j] + questions[i][0]);`

* 我们将记忆化搜索1：1转化为DP的时候，可以将dp数组稍微开大一点，防止某些下标越界，详见上面的答疑



### 最大子数组和

一般这种题目有两种做法:

1. 定义状态 f[i] 表示以 a[i] 结尾的最大子数组和，不和 i 左边拼起来就是 f[i]=a[i]，和 i 左边拼起来就是 f[i]=f[i−1]+a[i]，取最大值就得到了状态转移方程 f[i]=max(f[i−1],0)+a[i]，答案为 max(f)。这个做法也叫做 Kadane 算法。
2. 用 前缀和，转化成  121. 买卖股票的最佳时机。



#### 最大子数组和

力扣***[53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/)***

> 给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
>
> **子数组**是数组中的一个连续部分。
>
>  
>
> **示例 1：**
>
> ```
> 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
> 输出：6
> 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
> ```
>
> **示例 2：**
>
> ```
> 输入：nums = [1]
> 输出：1
> ```
>
> **示例 3：**
>
> ```
> 输入：nums = [5,4,-1,7,8]
> 输出：23
> ```
>
>  
>
> **提示：**
>
> - *1 <= nums.length <= 10^5^*
> - *-10^4^ <= nums[i] <= 10^4^*
> 



##### DP策略

对于每个位置*i*，我们可以选择在这个位置加上前面的子段和，也可以选择不加，我们得到了递推公式：

​						$dp[i] = max(0,dp[i-1])+nums[i]$	

最终我们收集**dp数组中的最大值即可**



```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //dp策略
        int n = nums.size();
        int f0 = 0;
        int res = INT_MIN;
        for(int i = 0;i<n;i++){
            f0 = max(f0,0) + nums[i];
            res = max(res,f0);
        }
        return res;
    }
};
```

##### 前缀和策略

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //前缀和策略
        int pre_sum = 0,min_pre_sum = 0;
        int res = INT_MIN;
        for(int num:nums){
            pre_sum+=num;
            res = max(pre_sum - min_pre_sum,res);
            min_pre_sum = min(min_pre_sum,pre_sum);
        }
        return res;
    }
};
```



##### 类似变形题:

力扣***[1749. 任意子数组和的绝对值的最大值](https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/)***



#### K次串联后最大子数组之和

力扣***[1191. K 次串联后最大子数组之和](https://leetcode.cn/problems/k-concatenation-maximum-sum/)***

> 给定一个整数数组 `arr` 和一个整数 `k` ，通过重复 `k` 次来修改数组。
>
> 例如，如果 `arr = [1, 2]` ， `k = 3` ，那么修改后的数组将是 `[1, 2, 1, 2, 1, 2]` 。
>
> 返回修改后的数组中的最大的子数组之和。注意，子数组长度可以是 `0`，在这种情况下它的总和也是 `0`。
>
> 由于 **结果可能会很大**，需要返回的 `109 + 7` 的 **模** 。
>
>  
>
> **示例 1：**
>
> ```
> 输入：arr = [1,2], k = 3
> 输出：9
> ```
>
> **示例 2：**
>
> ```
> 输入：arr = [1,-2,1], k = 5
> 输出：2
> ```
>
> **示例 3：**
>
> ```
> 输入：arr = [-1,-2], k = 7
> 输出：0
> ```
>
>  
>
> **提示：**
>
> - *1 <= arr.length <= 10^5^*
> - *1 <= k <= 10^5^*
> - *10^4^ <= arr[i] <= 10^4^*
> 



##### 分析

* 当*k = 1*时，直接套用最大子数组之和代码即可。

* 当*k = 2*时，重复一遍套用代码即可

* 当*k >= 3* 时：

  > 记`arr`的总和为*total*：
  >
  > * 当*total < 0* 时，我们只要考虑两个拼接的数组即可，因为后面的*k-2*个拼接的数组一定会让总和越来越小，问题变为了*k = 2*的情况
  >
  > * 当*total > 0*时：
  >
  >   ​	我们给出一个定理：
  >
  >   > 定理：当*total > 0*时，两个*arr*拼接的最大子数组一定横跨这两个*arr*。
  >   >
  >   > 反证法： 假设最大子数组只在第一个 arr 中间，记为*max_arr*，下标范围为 [l,r]。我们可以在最大子数组后面拼接一个完整的 arr,即：
  >   >
  >   > ​					*arr~1~*^后缀[r+1,n−1]^  +  *arr~2~*^前缀[0,r]^ = *total* + *max_arr*
  >   >
  >   > 这样得到了一个更大的子数组和。矛盾
  >
  >   ​	此时我们可以把 k 个 arr 看成是 :
  >
  >   ​					$post\_max\_arr + (k-2)*arr + pre\_max\_arr$ 
  >
  >   ​	简单理解就是： 尾 + 总 + 首 

  

  #####  实现

  ```c++
  class Solution {
      int maxSubArray(vector<int>& nums, int repeat) {
          int n = nums.size();
          int ans = 0, f = 0; // 本题允许子数组为空，ans 可以初始化成 0
          for (int i = 0; i < n * repeat; i++) {
              f = max(f, 0) + nums[i % n];
              ans = max(ans, f);
          }
          return ans;
      }
  
  public:
      int kConcatenationMaxSum(vector<int>& arr, int k) {
          if (k == 1) {
              return maxSubArray(arr, 1);
          }
          long long ans = maxSubArray(arr, 2); // arr+arr 的最大子数组和
          int s = reduce(arr.begin(), arr.end());
          ans += 1LL * max(s, 0) * (k - 2);
          return ans % 1'000'000'007;
      }
  };
  ```



#### ==环形数组的最大和==

力扣***[918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/)***

题目略: 大意就是数组是环形了怎么办，而且不能重复利用数字，而且不能非空



##### 分析

**先入为主的直接拷贝一份原数组到后面是行不通的**，因为这样会造成元素重复出现。

那么我们怎么解决呢？

回到答案的形式上，答案无非两种情况：

1. 在数组中间，也就是不成环
2. 在数组两侧，也就是成环

我们知道成环的情况是难解决的，真难则反，既然 情况2 难解决，我们考虑他的反命题，**最大子数组成环了，那么最小子数组一一定就不成环了**。我们直接拿数组总和减去最小子数组总和就是 情况2 的最大子数组总和了。

​	*这种思想在滑动窗口中也有题目体现。*

注意：当数组全为负数的时候，这种方法会失效，因为题目要求的是非空子数组，这种方法得到的会是0，所以我们要注意这种情况，处理方法见下面的实现。



##### 实现

```c++
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // 答案只有两种情况
        // 1. 最大子数组和在数组中间
        // 2. 最大子数组和在数组两侧 ——> 最小子数组和在数组中间(真难则反的思想)
        int mx_mid = 0, mn_mid = 0;
        int sum = 0,mx = INT_MIN,mn = INT_MAX;
        for (int num : nums) {
            sum += num;
            mx_mid = max(mx_mid, 0) + num;
            mx = max(mx_mid,mx);
            mn_mid = min(mn_mid,0) + num;
            mn = min(mn,mn_mid);
        }
        //如果最大值都是负数了，那么说明这个环形数组全为负数，直接返回最大负数即可。
        if(mx<0) return mx;
        return max(sum-mn,mx);
    }
};
```



#### ==拼接数组的最大分数==

力扣***[2321. 拼接数组的最大分数](https://leetcode.cn/problems/maximum-score-of-spliced-array/)***

> 给你两个下标从 **0** 开始的整数数组 `nums1` 和 `nums2` ，长度都是 `n` 。
>
> 你可以选择两个整数 `left` 和 `right` ，其中 `0 <= left <= right < n` ，接着 **交换** 两个子数组 `nums1[left...right]` 和 `nums2[left...right]` 。
>
> - 例如，设 `nums1 = [1,2,3,4,5]` 和 `nums2 = [11,12,13,14,15]` ，整数选择 `left = 1` 和 `right = 2`，那么 `nums1` 会变为 `[1,12,13,4,5]` 而 `nums2` 会变为 `[11,2,3,14,15]` 。
>
> 你可以选择执行上述操作 **一次** 或不执行任何操作。
>
> 数组的 **分数** 取 `sum(nums1)` 和 `sum(nums2)` 中的最大值，其中 `sum(arr)` 是数组 `arr` 中所有元素之和。
>
> 返回 **可能的最大分数** 。
>
> **子数组** 是数组中连续的一个元素序列。`arr[left...right]` 表示子数组包含 `nums` 中下标 `left` 和 `right` 之间的元素**（含** 下标 `left` 和 `right` 对应元素**）**。
>
>  
>
> **示例 1：**
>
> ```
> 输入：nums1 = [60,60,60], nums2 = [10,90,10]
> 输出：210
> 解释：选择 left = 1 和 right = 1 ，得到 nums1 = [60,90,60] 和 nums2 = [10,60,10] 。
> 分数为 max(sum(nums1), sum(nums2)) = max(210, 80) = 210 。
> ```
>
> **示例 2：**
>
> ```
> 输入：nums1 = [20,40,20,70,30], nums2 = [50,20,50,40,20]
> 输出：220
> 解释：选择 left = 3 和 right = 4 ，得到 nums1 = [20,40,20,40,20] 和 nums2 = [50,20,50,70,30] 。
> 分数为 max(sum(nums1), sum(nums2)) = max(140, 220) = 220 。
> ```
>
> **示例 3：**
>
> ```
> 输入：nums1 = [7,11,13], nums2 = [1,1,1]
> 输出：31
> 解释：选择不交换任何子数组。
> 分数为 max(sum(nums1), sum(nums2)) = max(31, 3) = 31 。
> ```
>
>  
>
> **提示：**
>
> - *n == nums1.length == nums2.length*
> - *1 <= n <= 10^5^*
> - *1 <= nums1[i], nums2[i] <= 10^4^*



##### 分析

首先，题目要求的是两个交换之后最大值，也就是说，我们要对数组a，b分别枚举。

以数组`nums1`为例：

>​			$Sum(nums1) = SumA - (a[l]+a[l+1]+...+a[r]） + (b[l]+b[l+1]+...+b[r])	$	
>
> ​			$Sum(nums1)=SumA+\sum_{i=l}^{r}(b[i]-a[i])$
>
> ​	令		$diff[i] =b[i]-a[i]$
>
> ​	也就是要求差分数组中最大子数组和，问题转换完毕

在实际实现的时候，为保证代码复用性，我们可以额外写一个`helper()`分别实现对*Sum(nums1)*和*Sum(nums2)*的求解



##### 实现

```c++
class Solution {
private:
    int helper(vector<int>&a,vector<int>& b){
        int mx = 0,f = 0,sum = 0;
        for(int i = 0;i<a.size();i++){
            sum+=b[i];
            f = max(f,0) + a[i] - b[i];
            mx = max(mx,f);
        }
        return sum + mx;
    }
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        return max(helper(nums1,nums2),helper(nums2,nums1));
    }
};
```

#### 思维拓展

1. 如果我现在把加法改成乘法，怎么做？注意有数组中正有负。

   这道题就是力扣***[152. 乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/)***

2. ==力扣***[1186. 删除一次得到子数组最大和](https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/)***==

3. 力扣***[3381. 长度可被 K 整除的子数组的最大元素和](https://leetcode.cn/problems/maximum-subarray-sum-with-length-divisible-by-k/)***（滑动窗口+DP)但是这题的主流题解是前缀和~~但是我前缀和掌握的还不太好（悲）~~



## 二、网格图DP

对于一些二维 DP（例如背包、最长公共子序列），如果把 DP 矩阵画出来，其实状态转移可以视作在网格图上的移动。所以在学习相对更抽象的二维 DP 之前，做一些形象的网格图 DP 会让后续的学习更轻松（比如 0-1 背包的空间优化写法为什么要倒序遍历）。

### 最小路径和 —— 从暴力到极致的细节空间优化

力扣***[64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)***

> 给定一个包含非负整数的 `*m* x *n*` 网格 `grid` ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
>
> **说明：**每次只能向下或者向右移动一步。
>
>  
>
> **示例 1：**
>
> ![img](https://assets.leetcode.com/uploads/2020/11/05/minpath.jpg)
>
> ```
> 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
> 输出：7
> 解释：因为路径 1→3→1→1→1 的总和最小。
> ```
>
> **示例 2：**
>
> ```
> 输入：grid = [[1,2,3],[4,5,6]]
> 输出：12
> ```
>
>  
>
> **提示：**
>
> - `m == grid.length`
> - `n == grid[i].length`
> - `1 <= m, n <= 200`
> - `0 <= grid[i][j] <= 200`



#### 分析 & 实现

看到这道题目的第一眼：网格图dfs，回溯，这是最简单的方法，但是这种方法显然时间复杂度是*O(2^mn^)，肯定会超时。没关系，我们可以从暴力入手逐渐优化。

传统的dfs超时原因就是反复算了多个相同的坐标，于是我们想到了挂一个缓存，也就是记忆化搜索。思路很简单，这里不作分析，直接贴实现。

##### 记忆化搜索
```c++
class Solution {
    public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        memo[0][0] = grid[0][0];
        auto dfs = [&](auto&& dfs, int x, int y) -> int {
            if (x < 0 || y < 0 || x >= m || y >= n) {
                return INT_MAX;
            }
            int& res = memo[x][y];
            if (res != -1)
                return res;
            return res = min(dfs(dfs,x-1,y),dfs(dfs,x,y-1)) + grid[x][y];
        };
        return dfs(dfs, m - 1, n - 1);
    }
};
```

*值得关注的是这里的返回值和初始化的设计。可以仔细琢磨，这里留给不做赘述。*



能记忆化搜索也能用严格DP,下面是1:1翻译为递推

##### 严格DP

对于每一个位置`(i，j)`，它一定是由左边（如果存在）和上面的元素取`min`得到的所以这里我们要初始化为`INT_MAX`，但是我们不能全部初始化为inf，这样会造成起始位置判断`dp[i+1][j+1] = min(dp[i][j+1],dp[i+1][j]) + grid[i][j]`的时候造成`INT_MAX + ……` 显然不能得到正确的结果，所以我们要特判起始位置。



```c++
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
    for (int i = 0; i < m; i++) {
        for (int j = 0;j<n;j++){
            if(i==0&&j==0) dp[i+1][j+1] = grid[i][j];
            else dp[i+1][j+1] = min(dp[i][j+1],dp[i+1][j]) + grid[i][j];
        }
    }
    return dp[m][n];
}
```



##### 空间优化I
对于当前格子，我们知道它是从上面和左边推过来的，那么我们完全没有必要维护二维dp数组，整个过程只需要维护一行即可。其实这就是01背包的优化方法
```c++
int minPathSum(vector<vector<int>>& grid) {
    int n = grid[0].size();
    //空间优化，由于当前的数据之只有可能是上一行和左边过来的，所以我们实际上只用维护一行的数据即可
    //这里的初始化值得考究
    vector<int> dp(n+1,INT_MAX);
    dp[1] = 0; 
    for(auto row:grid){
        for(int j = 0;j<n;j++){
            dp[j+1] = min(dp[j],dp[j+1]) + row[j];
        }
    }
    return dp[n];
}
```



##### 空间优化 II

其实也没有必要再开一个dp数组，我们用grid数组第一行做表头就可以了，这样就实现了空间复杂度*O(1)*的优化

```c++
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    auto& dp = grid[0]; //用下标0的行数作表头
    //特判第一行
    for(int j = 1;j<n;j++){
        dp[j]+=dp[j-1];
    }
    for(int i = 1 ;i<m;i++){
        //特判第一列
        dp[0] += grid[i][0]; //第一列左边没有数可以推，所以直接从上一行第一列推就行。
        for(int j = 1;j<n;j++){
            dp[j] = min(dp[j-1],dp[j]) + grid[i][j];
        }
    }
    return dp[n-1];
}   
```



#### 注释

*关于空间优化*： 有的题目下一行有可能需要用到上一行的原数据，这样我们就不能传统的直接 一行覆盖了，可以见下面这道题的优化方案： 力扣***[网格中的最小路径代价](https://leetcode.cn/problems/minimum-path-cost-in-a-grid/)***

有时候从右往左遍历就可以解决这种问题，这就是01背包的优化策略

网格图 dp 千篇一律，这里就不列举过多的题目了，详情见 *[算法题单](https://leetcode.cn/discuss/post/3581838/fen-xiang-gun-ti-dan-dong-tai-gui-hua-ru-007o/)*



### 矩阵的最大非负乘积

力扣***[1594. 矩阵的最大非负积](https://leetcode.cn/problems/maximum-non-negative-product-in-a-matrix/)***

>   给你一个大小为 `m x n` 的矩阵 `grid` 。最初，你位于左上角 `(0, 0)` ，每一步，你可以在矩阵中 **向右** 或 **向下** 移动。
>
>   在从左上角 `(0, 0)` 开始到右下角 `(m - 1, n - 1)` 结束的所有路径中，找出具有 **最大非负积** 的路径。路径的积是沿路径访问的单元格中所有整数的乘积。
>
>   返回 **最大非负积** 对 **`109 + 7`** **取余** 的结果。如果最大积为 **负数** ，则返回 `-1` 。
>
>   **注意，**取余是在得到最大积之后执行的。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/12/23/product1.jpg)
>
>   ```
>   输入：grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
>   输出：-1
>   解释：从 (0, 0) 到 (2, 2) 的路径中无法得到非负积，所以返回 -1 。
>   ```
>
>   **示例 2：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/12/23/product2.jpg)
>
>   ```
>   输入：grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
>   输出：8
>   解释：最大非负积对应的路径如图所示 (1 * 1 * -2 * -4 * 1 = 8)
>   ```
>
>   **示例 3：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/12/23/product3.jpg)
>
>   ```
>   输入：grid = [[1,3],[0,-4]]
>   输出：0
>   解释：最大非负积对应的路径如图所示 (1 * 0 * -4 = 0)
>   ```
>
>    
>
>   **提示：**
>
>   -   `m == grid.length`
>   -   `n == grid[i].length`
>   -   `1 <= m, n <= 15`
>   -   `-4 <= grid[i][j] <= 4`

#### 分析

由于数值有负有正，传统的取最大是不行的，我们需要维护两个变量分别储存最小和最大进行 dp。

#### 实现

```c++
class Solution {
private:
    int MOD = 1e9 + 7;
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<long long> dp_min(n);
        vector<long long> dp_max(n);
        dp_min[0] = dp_max[0] = grid[0][0];
        for (int j = 1; j < n; j++) { // 第一行只能由左边推过来
            dp_min[j] = dp_max[j] = dp_max[j-1] * grid[0][j];
        }
        for (int i = 0; i < m; i++) {
            long long r = dp_max[0] * grid[i][0];
            dp_min[0] = dp_max[0] = r;
            for (int j = 1; j < n; j++) {
                int num = grid[i][j];
                long long left_max = dp_max[j - 1] * num;
                long long left_min = dp_min[j - 1] * num;
                long long up_max = dp_max[j] * num;
                long long up_min = dp_min[j] * num;
                dp_max[j] = max({up_max, up_min, left_max, left_min});
                dp_min[j] = min({up_max, up_min, left_max, left_min});
            }
        }
        return dp_max[n - 1] < 0 ? -1 : dp_max[n - 1] % MOD;
    }
};
```



### 矩阵中能被K整除的路径

力扣***2435. 矩阵中和能被 K 整除的路径***

>   给你一个下标从 **0** 开始的 `m x n` 整数矩阵 `grid` 和一个整数 `k` 。你从起点 `(0, 0)` 出发，每一步只能往 **下** 或者往 **右** ，你想要到达终点 `(m - 1, n - 1)` 。
>
>   请你返回路径和能被 `k` 整除的路径数目，由于答案可能很大，返回答案对 `109 + 7` **取余** 的结果。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2022/08/13/image-20220813183124-1.png)
>
>   ```
>   输入：grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
>   输出：2
>   解释：有两条路径满足路径上元素的和能被 k 整除。
>   第一条路径为上图中用红色标注的路径，和为 5 + 2 + 4 + 5 + 2 = 18 ，能被 3 整除。
>   第二条路径为上图中用蓝色标注的路径，和为 5 + 3 + 0 + 5 + 2 = 15 ，能被 3 整除。
>   ```
>
>   **示例 2：**
>
>   ![img](https://assets.leetcode.com/uploads/2022/08/17/image-20220817112930-3.png)
>
>   ```
>   输入：grid = [[0,0]], k = 5
>   输出：1
>   解释：红色标注的路径和为 0 + 0 = 0 ，能被 5 整除。
>   ```
>
>   **示例 3：**
>
>   ![img](https://assets.leetcode.com/uploads/2022/08/12/image-20220812224605-3.png)
>
>   ```
>   输入：grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
>   输出：10
>   解释：每个数字都能被 1 整除，所以每一条路径的和都能被 k 整除。
>   ```
>
>    
>
>   **提示：**
>
>   -   `m == grid.length`
>   -   `n == grid[i].length`
>   -   1 <= m, n <= 5 * 10^4^
>   -   1 <= m * n <= 5 * 10^4^
>   -   `0 <= grid[i][j] <= 100`
>   -   `1 <= k <= 50`



#### 记忆化搜索

这道题目实际上就是一道模运算 + dp 的题目。

```c++
class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        const int mod = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dpPre(n, vector<int>(k, 0));
        vector<vector<int>> dpCru(n, vector<int>(k, 0));

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
                fill(dpCru[j].begin(), dpCru[j].end(), 0);
            
            for(int j = 0; j < n; j++)
            {
                int v = grid[i][j] % k;

                if(i == 0 && j == 0)
                {
                    dpCru[0][v] = 1;
                    continue;
                }

                for(int r = 0; r < k; r++)
                {
                    if(i > 0 && dpPre[j][r] > 0)
                    {
                        int nr = (r + v) % k;
                        dpCru[j][nr] = (dpCru[j][nr] + dpPre[j][r]) % mod;
                    }
                    if(j > 0 && dpCru[j - 1][r] > 0)
                    {
                        int nr = (r + v) % k;
                        dpCru[j][nr] = (dpCru[j][nr] + dpCru[j - 1][r]) % mod;
                    }
                }
            }
            dpPre.swap(dpCru);
        }
        return dpPre[n - 1][0];
    }
};
```



#### 严格DP

```c++
class Solution {
private:
    const int MOD = 1e9 + 7;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n =grid[0].size();
        vector<vector<vector<int>>> dp(m+1,vector<vector<int>>(n+1,vector<int>(k,0)));
        dp[1][0][0] = 1; //也可以写 dp[0][1][0]  = 1;
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                int num = grid[i][j];
                for(int s = 0;s<k;s++){
                    int new_s = (s + num)%k;
                    dp[i+1][j+1][s] =(dp[i+1][j][new_s] + dp[i][j+1][new_s])% MOD;
                    //dp[i+1][j+1][new_s] =(dp[i+1][j][s] + dp[i][j+1][s])% MOD;
                    //这样写也能过，不过为了体现 1:1 翻译为递推我们就这样写
                }
            }
        }
        return dp[m][n][0];
    }
};
```

### 地下城游戏

力扣***[174. 地下城游戏](https://leetcode.cn/problems/dungeon-game/)***

>   恶魔们抓住了公主并将她关在了地下城 `dungeon` 的 **右下角** 。地下城是由 `m x n` 个房间组成的二维网格。我们英勇的骑士最初被安置在 **左上角** 的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。
>
>   骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。
>
>   有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为*负整数*，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 *0*），要么包含增加骑士健康点数的魔法球（若房间里的值为*正整数*，则表示骑士将增加健康点数）。
>
>   为了尽快解救公主，骑士决定每次只 **向右** 或 **向下** 移动一步。
>
>   返回确保骑士能够拯救到公主所需的最低初始健康点数。
>
>   **注意：**任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。
>
>    
>
>   **示例 1：**
>
>   ![img](https://assets.leetcode.com/uploads/2021/03/13/dungeon-grid-1.jpg)
>
>   ```
>   输入：dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
>   输出：7
>   解释：如果骑士遵循最佳路径：右 -> 右 -> 下 -> 下 ，则骑士的初始健康点数至少为 7 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：dungeon = [[0]]
>   输出：1
>   ```
>
>    
>
>   **提示：**
>
>   -   `m == dungeon.length`
>   -   `n == dungeon[i].length`
>   -   `1 <= m, n <= 200`
>   -   `-1000 <= dungeon[i][j] <= 1000`

#### 分析

初看这道题，很容易想到**64. 最小路径和**这道题，但实际上，这道题是Hard，不可能就是简单的网格图DP就能解决的。

看下面这个例子：

>   由于骑士的血量一旦小于等于0就会死亡，也就是说，如果选择正序遍历，我们需要注意两个变量：
>
>   第一个是「从出发点到当前点的路径和」，第二个是「从出发点到当前点所需的最小初始值」。而这两个值的重要程度相同，参看下面的示例：
>
>   ![fig1](https://assets.leetcode-cn.com/solution-static/174/174_fig1.png)
>
>   从 (0,0) 到 (1,2) 有多条路径，我们取其中最有代表性的两条：
>
>   ![fig2](https://assets.leetcode-cn.com/solution-static/174/174_fig2.png)
>
>   *   绿色路径「从出发点到当前点的路径和」为 1，「从出发点到当前点所需的最小初始值」为 3。
>
>   *   蓝色路径「从出发点到当前点的路径和」为 −1，「从出发点到当前点所需的最小初始值」为 2。
>
>   我们希望「从出发点到当前点的路径和」尽可能大，而「从出发点到当前点所需的最小初始值」尽可能小。这两条路径各有优劣。
>
>   在上图中，我们知道应该选**取绿色路径**，因为蓝色路径的路径和太小。使得蓝色路径需要增大初始值到 4 才能走到终点，而绿色路径只要 3 点初始值就可以直接走到终点。但是如果把终点的 −2 换为 0，蓝色路径只需要初始值 2，绿色路径仍然需要初始值 3，最优决策就变成蓝色路径了。在上图中，我们知道应该选取绿色路径，因为蓝色路径的路径和太小，使得蓝色路径需要增大初始值到 4 才能走到终点，而绿色路径只要 3 点初始值就可以直接走到终点。但是如果把终点的 −2 换为 0，蓝色路径只需要初始值 2，绿色路径仍然需要初始值 3，最优决策就变成蓝色路径了。

因此，如果按照从左上往右下的顺序进行动态规划，我们无法直接确定到达 (1,2) 的方案，因为有两个重要程度相同的参数同时影响后续的决策。也就是说，这样的动态规划是不满足「无后效性」的。

于是我们考虑从右下往左上进行动态规划。令 `dp[i][j]` 表示从坐标 `(i,j)` 到终点所需的最小**初始值**。

换句话说，当我们到达坐标 (i,j) 时，如果此时我们的路径和不小于 `dp[i][j]`，我们就能到达终点。

这样一来，我们就无需担心路径和的问题，只需要关注最小初始值。对于 `dp[i][j]`，我们只要关心 `dp[i][j+1]` 和 `dp[i+1][j]` 的最小值` minn`。记当前格子的值为 `dungeon[i][j]`，那么在坐标` (i,j)` 的初始值只要达到` minn−dungeon[i][j]` 即可。同时，初始值还必须大于等于 1。这样我们就可以得到状态转移方程：

​				$dp[i][j]=max(min(dp[i+1][j],dp[i][j+1])−dungeon(i,j),1)$
最终答案即为 `dp[0][0]`。

边界条件为，当 i=n−1 或者 j=m−1 时，`dp[i][j]` 转移需要用到的 `dp[i][j+1]` 和` dp[i+1][j]` 中有无效值，因此代码实现中给无效值赋值为极大值。特别地，`dp[n−1][m−1]` 转移需要用到的 `dp[n−1][m]` 和 `dp[n][m−1]` 均为无效值，因此我们给这两个值赋值为 1。

>   注: 题解来源 —— [力扣官方题解](https://leetcode.cn/problems/dungeon-game/solutions/326171/di-xia-cheng-you-xi-by-leetcode-solution/)。

#### 实现

```c++
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(),n = dungeon[0].size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
        dp[m-1][n] = 1; //边界初始化为 1 防止特判
        for(int i = m-1;i>=0;i--){
            for(int j = n -1;j>=0;j--){
                int minn = min(dp[i+1][j],dp[i][j+1]);
                dp[i][j] = max(minn - dungeon[i][j],1);
            }
        }
        return dp[0][0];
    }
};
```



### 值得练习好题

***[2267. 检查是否有合法括号字符串路径](https://leetcode.cn/problems/check-if-there-is-a-valid-parentheses-string-path/)***

***[2510. 检查是否有路径经过相同数量的 0 和 1（plus）](https://leetcode.cn/problems/check-if-there-is-a-path-with-equal-number-of-0s-and-1s/)*** ——本质上就是2267更简单的版本

***[1937. 扣分后的最大得分](https://leetcode.cn/problems/maximum-number-of-points-with-cost/)*** ——考虑优化方法

***[174. 地下城游戏](https://leetcode.cn/problems/dungeon-game/)***——考虑遍历顺序

***[1463. 摘樱桃 II](https://leetcode.cn/problems/cherry-pickup-ii/description/)***——考虑遍历顺序

+++

## 三、背包DP

背包问题最关键的核心就是「选和不选」，牢记这个，可以解决很多背包问题。

### 0-1背包 

每个物品只能选一次，即要么选，要么不选。

所以 0-1 背包是「选或不选」的代表。



#### 0-1背包入门——从记忆化搜索到DP

洛谷***[NOIP 2005 普及组\] 采药 - 洛谷](https://www.luogu.com.cn/problem/P1048)***

题目大意就是：给你一个容量为t的背包，一共有m个货物，每个货物只能选一次，其中每个货物的价值和重量分别用`cost[i]`和`value[i]`表示，求能在背包中装最多价值的货物。

##### 实现

我们考虑「选和不选」，递归货物，对于每个货物，我们都可以选和不选这个货物，这就是典型的回溯逻辑。

###### 记忆化搜索

```c++
int zero_oneBags(vector<int>& costs,vector<int>& values,int capacity){
    int m = costs.size();
    vector<vector<int>> memo(m,vector<int>(capacity+1,-1)); //注意要包含capacity这个下标
    auto dfs = [&](auto&&dfs,int i,int c)->int{
        if(i == m) return 0;
        int& res = memo[i][c];
        if(res!=-1) return res;
        if(c < costs[i]) return res = dfs(dfs,i-1,c);
        return res = max(dfs(dfs,i-1,c),dfs(dfs,i,c-costs[i])+values[i]);
    };
    return dfs(dfs,0,capacity);
}
```

###### 1:1翻译为递推

```c++
int zero_oneBags(vector<int>& costs,vector<int>& values,int capacity){
    int m = costs.size();
   	vector<vector<int>> dp(m+1,vector<int>(capacity+1,0)); 
    //dp[0][k]啥也没放
    //对于第一行
    for(int i = 0;i<m;i++){
		for(int j = 0;j<=capacity;j++){
			dp[i+1][j] = dp[i][j];
            if(j >= costs[i]){
				dp[i+1][j] = max(dp[i+1][j],dp[i][j-capacity]+costs[i]);
            }
        }
    }
    return dp[m-1][capacity];
}
```

通过记忆化搜索，我们很容易得到递推，但是我们也可以从另一个角度分析递推

######  理解01背包的本质

上述的`dp[i][j]` 的含义就是：遍历到第i个物品背包容量为j的时候我们我们最多能放下物品的最大价值。

对于每个物品，我们都有选和不选这两种操作：

*   不选的情况下，我们直接继承上一行的数据。
*   选的情况下，如果当前背包容量可以放下当前物品，我们减去这个物品的重量，再从上一行取减去之后重量的dp值即可。

也就是说，对于每行的数据，我们实际上都是由正上方和右上方推导过来的，所以我们用滚动数组进行空间优化

###### 空间优化

注意这里遍历容量的时候一定要倒序遍历。如果我们正序遍历，前面的值直接被覆盖了，导致后面`dp[j - cost[i]]`访问的值是被更新之后的值了，前面的网格图dp里也有这种优化方法。

```C++
int zero_oneBags(vector<int>& costs,vector<int>& values,int capacity){
    int m = costs.size();
   	vector<int> dp(capacity+1,0);
    for(int i = 0;i<m;i++){
		for(int j = capacity;j>=costs[i];j--）{
            dp[j] = max(dp[j],dp[j-csot[i]]	+ value[i]);
        }
    }
    return dp[m-1][capacity];
}
```





#### 分割等和子集

力扣***[416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)***

>   给你一个 **只包含正整数** 的 **非空** 数组 `nums` 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,5,11,5]
>   输出：true
>   解释：数组可以分割成 [1, 5, 5] 和 [11] 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [1,2,3,5]
>   输出：false
>   解释：数组不能分割成两个元素和相等的子集。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 200`
>   -   `1 <= nums[i] <= 100`



##### 分析

集合是没有顺序的，所以我们不必关心顺序。既然要求两个和相同的子集，也就是原数组和`sum/2`即可，注意这里的答案不能为负数。

我们可以抽象的把这道题看做0-1背包，背包容量为`sum/2`，每个物品价值和重量相同。我们期望对于每个容量为`j`的背包，我们能装下的最大价值是多少，最终我需要判断，这个背包是否能装满。

难道还有装不满的情况？

>   比如数组[1,5,11,5],对于dp[7],我们一定装不满，最大价值为6，而对于dp[6]我们可以装满，最大价值就是等于背包容量。

##### 实现1

```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum % 2) return false;
        int target = sum / 2;
        //target就是背包容量
        int n = nums.size();
        vector<int> dp(target+1,0);
        for(int i = 0;i<n;i++){
            for(int j = target;j>=nums[i];j--){
                dp[j] = max(dp[j],dp[j-nums[i]] + nums[i]);
            }
        }
        return dp[target] == target;
    }
};
```

上述的代码还是太慢了，有没有更快的方法呢？

实际上，我们只需要关心每个背包是否装满就可以了，我们可以用一个`bool`型变量来进行dp：
经过分析，我们可以得到下面的递推公式:
$$
dp[i][j]=
\begin{cases}
dp[i-1][j]  & \text{if  } j < nums[i] \\ 
dp[i−1][j]\or dp[i−1][j−nums[i]] 
& \text{otherwise}
\end{cases}
$$

##### 实现2

```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum % 2) return false;
        int target= sum / 2;
        vector<int > dp(target+1,0); //dp[j]代表容量为j背包是否装满了
        dp[0] = 1;
        for(int i = 0;i<nums.size();i++){
            for(int j = target;j>=nums[i];j--){
                dp[j] |= dp[j - nums[i]];
            }
            if(dp[target]) return true; //剪枝，如果已经找到解，直接返回即可
        }
        return false;
    }
};
```



#### 目标和

力扣 ***[494. 目标和](https://leetcode.cn/problems/target-sum/)***

>   给你一个非负整数数组 `nums` 和一个整数 `target` 。
>
>   向数组中的每个整数前添加 `'+'` 或 `'-'` ，然后串联起所有整数，可以构造一个 **表达式** ：
>
>   -   例如，`nums = [2, 1]` ，可以在 `2` 之前添加 `'+'` ，在 `1` 之前添加 `'-'` ，然后串联起来得到表达式 `"+2-1"` 。
>
>   返回可以通过上述方法构造的、运算结果等于 `target` 的不同 **表达式** 的数目。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [1,1,1,1,1], target = 3
>   输出：5
>   解释：一共有 5 种方法让最终目标和为 3 。
>   -1 + 1 + 1 + 1 + 1 = 3
>   +1 - 1 + 1 + 1 + 1 = 3
>   +1 + 1 - 1 + 1 + 1 = 3
>   +1 + 1 + 1 - 1 + 1 = 3
>   +1 + 1 + 1 + 1 - 1 = 3
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [1], target = 1
>   输出：1
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 20`
>   -   `0 <= nums[i] <= 1000`
>   -   `0 <= sum(nums[i]) <= 1000`
>   -   `-1000 <= target <= 1000`

##### 分析

设符号位“+”的子集总和为p，符号为“-”的子集总和为为q。

也就有
$$
\begin{cases}
p+q=sum\\
p-q=target
\end{cases}
$$
得到	 $ p=\frac{sum+target} {2}$ 	也就是说，我们要找到和为`p`的子集。

这又变成了和上面分割等和子集相似的题目了，不过上面是问是否存在，这道题是问方法数，怎处理呢？

只要改一下dp数组的定义就可以了，设`dp[i][j]`代表遍历到第`i`个物品的时候，一共有多少个方法数能够使容量为`j`的背包装满。

根据加法原理，也就得到了递推公式：
$$
dp[i][j] =
\begin{cases} 
dp[i-1][j] + dp[i-1][j-nums[i]]&\text{if } j > nums[i]\\
dp[i-1][j] & \text{otherwise}\\
\end{cases}
$$


##### 实现

```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if((target + sum) % 2 || target + sum < 0) return 0;
        int w = (target + sum )/ 2;
        //dp[j]代表可可以得到容量为j的背包的方法数
        vector<int> dp(w+1,0);
        dp[0] = 1;
        for(int x : nums){
            for(int j = w;j>=x;j--){
                dp[j] += dp[j - x];
            }
        }
        return dp[w];
    }
};
```



#### 执行操作可获得的最大总奖励 I

>   给你一个整数数组 `rewardValues`，长度为 `n`，代表奖励的值。
>
>   最初，你的总奖励 `x` 为 0，所有下标都是 **未标记** 的。你可以执行以下操作 **任意次** ：
>
>   -   从区间 `[0, n - 1]` 中选择一个 **未标记** 的下标 `i`。
>   -   如果 `rewardValues[i]` **大于** 你当前的总奖励 `x`，则将 `rewardValues[i]` 加到 `x` 上（即 `x = x + rewardValues[i]`），并 **标记** 下标 `i`。
>
>   以整数形式返回执行最优操作能够获得的 **最大** 总奖励。
>
>    
>
>   **示例 1：**
>
>   **输入：**rewardValues = [1,1,3,3]
>
>   **输出：**4
>
>   **解释：**
>
>   依次标记下标 0 和 2，总奖励为 4，这是可获得的最大值。
>
>   **示例 2：**
>
>   **输入：**rewardValues = [1,6,4,3,2]
>
>   **输出：**11
>
>   **解释：**
>
>   依次标记下标 0、2 和 1。总奖励为 11，这是可获得的最大值。
>
>    
>
>   **提示：**
>
>   -   `1 <= rewardValues.length <= 2000`
>   -   `1 <= rewardValues[i] <= 2000`

##### 分析

对于`rewardValues`中的数，如果我们先选了大的数，那么一定就不能选更小的数了，比如说对于`[6,2,5]`，如果我们先选了 6，那么我们一定无法再选 2 和 5 了。但显然 2 + 5 这个答案是更优解。
根据上面描述，我们应该尽可能先选小的数，这样才能保证我们的答案尽可能大。所以我们应该先对`rewardValues`中的每个数按从小到大的顺序排序。

考虑记忆化搜索：

> 从左到右递归`rewardValues`，我们都考虑「选和不选」，也就很容易得到了递归公式。
> $$
> dfs(i,j)=
> \begin{cases}
> max(dfs(i+1,j),dfs(i+1,j-rewardValues[i])) & \text{if }j>rewardValues[i]\\
> dfs(i+1,j)&\text{otherwise}\\
> \end{cases}
> $$

那我们应该开多大的数组呢？
> 记 *rewardValues* 的最大值为 *m*，因为最后一次操作前的总奖励一定小于等于 *m*−1，所以可获得的最大总奖励小于等于 2*m*−1

所以我们开一个 2*m*-1 大小的数组就可以了

##### 记忆化搜索

```c++
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(),rewardValues.end());
        //上界是 2*m-1
        //这题数据量比较小，不会爆M优化方案见3181 
        vector<vector<int>> memo(rewardValues.size(),vector<int>(2*rewardValues.back(),-1));
        auto dfs = [&](auto&&dfs,int i,int x)->int{
            if(i == rewardValues.size()){
                return x;
            }
            int& res = memo[i][x];
            if(res!=-1) return res;
            if(rewardValues[i] <= x){
                return res = dfs(dfs,i+1,x);
            }
            return res = max(dfs(dfs,i+1,x),dfs(dfs,i+1,x+rewardValues[i]));
        };
        return dfs(dfs,0,0);
    }
};
```

##### 递推

这道题很显然是一道 0-1 背包的问题，我们可以把它翻译成递推，如果我们令`dp[i][j]`代表**第 i 个物品背包容量为 j 所能装的最大价值** 其中数组中每个数代表他们的价值和重量，这种最基础的0-1 背包思想，可以是可以，但是完全没有必要，考虑下面这个场景。

>   假设遍历背包容量为 j
>
>   如果 `dp[i-1][j - v]` 是从一个合法状态转移过来的，那么它的值理论上就是 `j - v`，因为物品价值和重量相同。
>
>   那么 `dp[i-1][j - v] + v` 的结果必然是 `(j - v) + v = j`。
>
>   所以，`dp[i][j]` 最终存的值，**只要它是合法的，就一定等于 `j`**。
>
>   还能有不相同的情况吗？
>
>   >   考虑这个场景数组`[1,5,5,11]`,对于`dp[1][7]`,我们一定装不满，最大价值为6，而对于`dp[1][6]`我们可以装满,他可以由合法状态`dp[0][1]`推过来，最大价值就是等于背包容量。（我们可以定义不合法状态为-1，初始化 `dp[0][rewardValues[i] = rewardValues[i]` 如果前一个`dp[i-1][k] == -1`,我们就不该使用这个状态。）

*   既然 `dp[i][j]` 的值永远等于 `j`（或者 -1 表示不可达），那么存这个 `int` 是**冗余**的。我们只需要知道“`j` 这个状态是否可达”即这很像***[416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)***

所以我们只要**关注容量为 *j*的时候，这个背包是否充满了就好了，最终检查最后一行那个被充满的背包容量最大即可**

或者更好理解的方法是改变一下 dp 数组的定义，定义 dp 数组为**表示能否从 *rewardValues* 的前 *i* 个数中得到总奖励 *j***

所以我们得到递推公式，这里我直接用滚动数组优化了。
$$
dp[j]=\begin{cases}
dp[j] \or dp[j-v]&\text{if  }0≤j-v<v\\
dp[j]&\text{otherwise}\\
\end{cases}
$$
其中 `v = rewardValue[i]`

注意，关于这里的 $0≤j-v<v$ `j-v`代表上一行容量为`j-v`的背包是否装满也就是 x，根据题意，如果我们要访问这个状态，x 必须要小于 v。

实现

```c++
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(),rewardValues.end());
        int m = rewardValues.back();
        vector<int> dp(2*m,0); //dp[j]代表容量为j时是否已经装满了
        //定义 dp[i][j] 表示能否从 rewardValues 的前 i 个数中得到总奖励 j。
        dp[0] = 1;//容量为0一定可以拿到
        for(int v:rewardValues){
            for(int j = 2*v-1;j>=v;j--){
                dp[j] |=dp[j-v];
            }
        }
        int res = 0;
        for(int j = 0;j<2*m;j++){
            if(dp[j]) res = j;
        }
        return res;
    }
};
```



##### 进阶

这道题数据量太小了，不会溢出，其实观察一下，重复元素根本不用取。

关于更高级的优化方法，见力扣***[181. 执行操作可获得的最大总奖励 II](https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/)*** —— 位运算(bitset)优化上题

+++



#### ==总结==

*   实际上01背包问题可以解决子集问题，这跟子集型回溯很像，子集型回溯也有「选和不选」这种思想，对于子数组类型的问题，我们通常用Kandane算法，见入门DP

*   如果我们要选的是**方法数**，我们一般用**加法原理**，定义 dp 数组值代表方法书，比如**目标和**这道题
*   如果我们关心的是**最大和**，我们通常考虑他是否装满即可，因为合法用 一个 bool 变量维护上一个单位格是否合法，最终找到最大容量合法的 j 值即可。常常我们这么定义 dp 数组：**`dp[i][j]`表示==能否==从 数组中的前 *i* 个数中得到总奖励 *j***，比如**目标和**和**执行操作可获得的最大总奖励 I**这道题。



---------

#### ==给墙壁刷油漆 —— 至少装满的0-1 背包问题==

力扣***[2742. 给墙壁刷油漆](https://leetcode.cn/problems/painting-the-walls/)***

>   给你两个长度为 `n` 下标从 **0** 开始的整数数组 `cost` 和 `time` ，分别表示给 `n` 堵不同的墙刷油漆需要的开销和时间。你有两名油漆匠：
>
>   -   一位需要 **付费** 的油漆匠，刷第 `i` 堵墙需要花费 `time[i]` 单位的时间，开销为 `cost[i]` 单位的钱。
>   -   一位 **免费** 的油漆匠，刷 **任意** 一堵墙的时间为 `1` 单位，开销为 `0` 。但是必须在付费油漆匠 **工作** 时，免费油漆匠才会工作。
>
>   请你返回刷完 `n` 堵墙最少开销为多少。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：cost = [1,2,3,2], time = [1,2,3,2]
>   输出：3
>   解释：下标为 0 和 1 的墙由付费油漆匠来刷，需要 3 单位时间。同时，免费油漆匠刷下标为 2 和 3 的墙，需要 2 单位时间，开销为 0 。总开销为 1 + 2 = 3 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：cost = [2,3,4,2], time = [1,1,1,1]
>   输出：4
>   解释：下标为 0 和 3 的墙由付费油漆匠来刷，需要 2 单位时间。同时，免费油漆匠刷下标为 1 和 2 的墙，需要 2 单位时间，开销为 0 。总开销为 2 + 2 = 4 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= cost.length <= 500`
>   -   `cost.length == time.length`
>   -   `1 <= cost[i] <= 106`
>   -   `1 <= time[i] <= 500`

##### 递推——「选与不选」

*分析见代码注释*

值得注意的是这里的递归边界和 *offset* 防止越界的用法

```c++
class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        /*
            记忆化搜索
            考虑「选和不选」
            由题意，付费匠的时间一定大于免费匠。
            我们定义 dfs(i,j) -> i 代表我们当前遍历的墙，j 代表我们剩余的时间（可以为负数）
            返回值代表我们的最小费用 对于第 i 面墙，
            如果我们考虑： 
            用付费匠去刷，也就是 -> dfs(i-1,j + times[i]) + cost[i] 
            用免费匠去刷，也就是 -> dfs(i-1,j - 1)
            但是这里会出现一个问题，比如说我们这里是倒过来遍历的，如果对于最后一面墙，我们考虑直接白嫖，
            那么在这里的 j 变为负数，怎么办呢？
                我们可以把它想为一个赊账，为了防止下标越界，我们可以定义一个
           offset，让我们每次访问 memo 防止越界

            递归公式：dfs(i,j) = min(dfs(i-1,j-1),dfs(dfs,i-1,j-times[i])+cost[i]); 
            递归边界：当 i == -1 时： dfs(-1,<0) -> 还是”赊账“的状态，不合法直接返回 inf
                    dfs(-1,>=0) -> 这里可以优化 => if(j >= i + 1)
           也就是剩下的墙全可以让免费匠去刷，直接返回0 即可。
        */
        int n = cost.size();
        vector<vector<int>> memo(n,vector<int>(2 * n + 1, -1)); // 时间范围最多为[-n,n];
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (j > i) {
                return 0;
            }
            if (i < 0) {
                return INT_MAX / 2;
            }
            int& res = memo[i][j + n]; //关键
            if (res != -1)
                return res;
            return res = min(dfs(i - 1, j - 1),dfs(i - 1, j + time[i]) + cost[i]);
        };
        return dfs(n - 1, 0);
    }
};
```



##### 0-1背包

我们可以发现，上面的记忆化搜索的递归公式：`min(dfs(i-1,j-1),dfs(dfs,i-1,j-times[i])+cost[i]); `这很像背包问题，那我们是否可以转化为背包问题呢？

由题意，我们可以得到两条有用的数量关系：

*   *付费匠刷墙的个数 + 免费匠刷墙的个数 = n*
*   *付费匠刷墙的时间 ≥ 免费匠刷墙的时间 = 免费匠刷墙的个数*

由关系 1,2，我们可以进一步整理得到：*付费匠刷墙的时间 + 付费匠刷墙的个数 ≥ n*

如果我们把**付费匠刷墙的个数拆开为 *k*个 “1”**

我们可以得到：$\sum{ time[i] + 1} ≥ n$ 

问题可以转化为：

>   每件物品的容量为 *time [i] + 1*,每件物品开销为 *cost[i]*,问至少装满容量为 *n *的背包最少需要的开销

这和我们之前的 0-1 背包很像，但是之前的 0-1 背包问题并不是求**“至少”**，这里求至少该怎么做呢？

我们先从记忆化搜索入手。

```java
class Solution {
    public int paintWalls(int[] cost, int[] time) {
        int n = cost.length;
        int[][] memo = new int[n][n + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1); // -1 表示没有计算过
        }
        return dfs(n - 1, n, cost, time, memo);
    }

    // j 表示剩余需要的体积
    private int dfs(int i, int j, int[] cost, int[] time, int[][] memo) {
        if (j <= 0) { // 没有约束，后面什么也不用选了
            return 0;
        }
        if (i < 0) { // 此时 j>0，但没有物品可选，不合法
            return Integer.MAX_VALUE / 2; // 防止加法溢出
        }
        if (memo[i][j] != -1) { // 之前计算过
            return memo[i][j];
        }
        int res1 = dfs(i - 1, j - time[i] - 1, cost, time, memo) + cost[i];
        int res2 = dfs(i - 1, j, cost, time, memo);
        return memo[i][j] = Math.min(res1, res2);
    }
}
```

翻译成递归，观察上面的记忆化搜索，当 *j≤0* 也就是符合条件的时候，我们完全可以并到 `dp[i][0]`这个状态里面

实现

```java
class Solution {
    public int paintWalls(int[] cost, int[] time) {
        int n = cost.length;
        int[] dp = new int[n+1];
        Arrays.fill(dp,Integer.MAX_VALUE/2);
        dp[0] = 0;
        for(int i = 0;i<n;i++){
            int c = cost[i],t = time[i] + 1;
            for(int j = n;j>0;j--){
                int idx = Math.max(0,j - t); //关键 如果就 j - t ≤ 0 ，直接并到 dp[0]的条件里
                dp[j] = Math.min(dp[j] , dp[idx] + c); 
            }
        }
        return dp[n];
    }
}
```



#### 一些好题

***[474. 一和零](https://leetcode.cn/problems/ones-and-zeroes/)*** ——二维背包

***[3489. 零数组变换 IV](https://leetcode.cn/problems/zero-array-transformation-iv/)***

***[3685. 含上限元素的子序列和](https://leetcode.cn/problems/subsequence-sum-after-capping-elements/)*** —— 增量法

***[1049. 最后一块石头的重量 II](https://leetcode.cn/problems/last-stone-weight-ii/)*** —— 如何转为背包

***[1774. 最接近目标价格的甜点成本](https://leetcode.cn/problems/closest-dessert-cost/)***——可以先从回溯入手

==***[3082. 求出所有子序列的能量和](https://leetcode.cn/problems/find-the-sum-of-the-power-of-all-subsequences/)***==——经典背包，附上*贡献法*，并考虑一维背包的优化

==***[2518. 好分区的数目](https://leetcode.cn/problems/number-of-great-partitions/)***== ——思路值得借鉴



----



### 完全背包 



#### 零钱兑换

力扣***[322. 零钱兑换](https://leetcode.cn/problems/coin-change/)***

>   给你一个整数数组 `coins` ，表示不同面额的硬币；以及一个整数 `amount` ，表示总金额。
>
>   计算并返回可以凑成总金额所需的 **最少的硬币个数** 。如果没有任何一种硬币组合能组成总金额，返回 `-1` 。
>
>   你可以认为每种硬币的数量是无限的。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：coins = [1, 2, 5], amount = 11
>   输出：3 
>   解释：11 = 5 + 5 + 1
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：coins = [2], amount = 3
>   输出：-1
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：coins = [1], amount = 0
>   输出：0
>   ```



##### 记忆化搜索

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //记忆化搜索
        int n = coins.size();
        vector memo(n,vector<int>(amount+1,-1));
        auto dfs = [&](auto&&dfs,int i ,int j)->int{
            if(i < 0){
                return j == 0 ? 0:INT_MAX/2;
            }
            int& res = memo[i][j];
            if(res!=-1) return res;
            if(j < coins[i]){ //不能选
                return res = dfs(dfs,i-1,j);
            }
            return res = min(dfs(dfs,i-1,j),dfs(dfs,i,j - coins[i]) + 1); //可以重复选，所以这里不用i-1
        };
        int ans = dfs(dfs,n-1,amount);
        return ans >= INT_MAX/2 ? -1:ans;
    }
};
```



##### 1:1 翻译为递推

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector dp(n+1,vector<int>(amount+1,INT_MAX/2));
        dp[0][0] = 0;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<=amount;j++){
                if(coins[i] > j){
                    dp[i+1][j] = dp[i][j];
                }else{
                    dp[i+1][j] = min(dp[i][j],dp[i+1][j - coins[i]] + 1);
                }
            }
        }
        int ans = dp[n][amount];
        return ans < INT_MAX/2 ? ans:-1;
    }
};
```



##### 优化写法（滚动数组）

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n  = coins.size();
        vector<int> dp(amount+1,INT_MAX/2);
        dp[0] = 0;
        for(int c:coins){
            for(int k = c;k<=amount;k++){ // 正序遍历，因为可以重复利用，后面的依赖当前层前面的数据
                dp[k] = min(dp[k],dp[k - c] + 1);
            }
        }
        int res = dp[amount];
        return res < INT_MAX / 2 ? res : -1;
    }
};
```



#### 关于遍历顺序

我们发现，0-1 背包的滚动数组是倒叙遍历的，因为当我们遍历第 i 个物品的时候，我们的 `dp[i][j]`只和上一个物品的 *dp* 数组有关，如果我们用正序遍历优化 *dp* 会导致 `dp[i][j]`实际上继承的是`min(dp[i-1][j],dp[i][j])`，这是完全背包需要的，所以0-1 背包需要倒序遍历，完全背包需要正序遍历。

换句话来说，完全背包问题的*dp*表中`dp[i][j]`依赖**当前层左边和正上方的数据**，0-1 背包问题的中 `dp[i][j]` 只**依赖正上方和上一层左上方的数据**。根据这个我们也可以作为遍历顺序的理由。



#### ==硬币面值还原==——创新构造题「必做」

力扣***[3592. 硬币面值还原](https://leetcode.cn/problems/inverse-coin-change/)***

>   给你一个 **从 1 开始计数** 的整数数组 `numWays`，其中 `numWays[i]` 表示使用某些 **固定** 面值的硬币（每种面值可以使用无限次）凑出总金额 `i` 的方法数。每种面值都是一个 **正整数** ，并且其值 **最多** 为 `numWays.length`。
>
>   然而，具体的硬币面值已经 **丢失** 。你的任务是还原出可能生成这个 `numWays` 数组的面值集合。
>
>   返回一个按从小到大顺序排列的数组，其中包含所有可能的 **唯一** 整数面值。
>
>   如果不存在这样的集合，返回一个 **空** 数组。
>
>    
>
>   **示例 1：**
>
>   **输入：** numWays = [0,1,0,2,0,3,0,4,0,5]
>
>   **输出：** [2,4,6]
>
>   **解释：**
>
>   | 金额 | 方法数 | 解释                                                         |
>   | ---- | ------ | ------------------------------------------------------------ |
>   | 1    | 0      | 无法用硬币凑出总金额 1。                                     |
>   | 2    | 1      | 唯一的方法是 `[2]`。                                         |
>   | 3    | 0      | 无法用硬币凑出总金额 3。                                     |
>   | 4    | 2      | 可以用 `[2, 2]` 或 `[4]`。                                   |
>   | 5    | 0      | 无法用硬币凑出总金额 5。                                     |
>   | 6    | 3      | 可以用 `[2, 2, 2]`、`[2, 4]` 或 `[6]`。                      |
>   | 7    | 0      | 无法用硬币凑出总金额 7。                                     |
>   | 8    | 4      | 可以用 `[2, 2, 2, 2]`、`[2, 2, 4]`、`[2, 6]` 或 `[4, 4]`。   |
>   | 9    | 0      | 无法用硬币凑出总金额 9。                                     |
>   | 10   | 5      | 可以用 `[2, 2, 2, 2, 2]`、`[2, 2, 2, 4]`、`[2, 4, 4]`、`[2, 2, 6]` 或 `[4, 6]`。 |
>
>   **示例 2：**
>
>   **输入：** numWays = [1,2,2,3,4]
>
>   **输出：** [1,2,5]
>
>   **解释：**
>
>   | 金额 | 方法数 | 解释                                                         |
>   | ---- | ------ | ------------------------------------------------------------ |
>   | 1    | 1      | 唯一的方法是 `[1]`。                                         |
>   | 2    | 2      | 可以用 `[1, 1]` 或 `[2]`。                                   |
>   | 3    | 2      | 可以用 `[1, 1, 1]` 或 `[1, 2]`。                             |
>   | 4    | 3      | 可以用 `[1, 1, 1, 1]`、`[1, 1, 2]` 或 `[2, 2]`。             |
>   | 5    | 4      | 可以用 `[1, 1, 1, 1, 1]`、`[1, 1, 1, 2]`、`[1, 2, 2]` 或 `[5]`。 |
>
>   **示例 3：**
>
>   **输入：** numWays = [1,2,3,4,15]
>
>   **输出：** []
>
>   **解释：**
>
>   没有任何面值集合可以生成该数组。
>
>    
>
>   **提示：**
>
>   -   `1 <= numWays.length <= 100`
>   -   0 <= numWays[i] <= 2 * 10 ^8^
>   

##### 分析

我们常常习惯的问题是 —— 给你硬币面额，求方案数，这里反过来了，给你了若干方案数，让你反过来求硬币数值。

乍一看很奇怪，很难，但实际上这道题目难度分也只有 1700 左右，怎么思考呢？

>   建议观看[灵神视频讲解——第二题](https://leetcode.cn/link/?target=https%3A%2F%2Fwww.bilibili.com%2Fvideo%2FBV1GCNRzgEYp%2F%3Ft%3D9m14s)



### 多重背包

多重背包，实际上就是对于每个物品可以重复选，但是有次数限制。

#### 获得分数的方法数

力扣***[2585. 获得分数的方法数](https://leetcode.cn/problems/number-of-ways-to-earn-points/)***

>   考试中有 `n` 种类型的题目。给你一个整数 `target` 和一个下标从 **0** 开始的二维整数数组 `types` ，其中 `types[i] = [counti, marksi] `表示第 `i` 种类型的题目有 `counti` 道，每道题目对应 `marksi` 分。
>
>   返回你在考试中恰好得到 `target` 分的方法数。由于答案可能很大，结果需要对 `109 +7` 取余。
>
>   **注意**，同类型题目无法区分。
>
>   -   比如说，如果有 `3` 道同类型题目，那么解答第 `1` 和第 `2` 道题目与解答第 `1` 和第 `3` 道题目或者第 `2` 和第 `3` 道题目是相同的。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：target = 6, types = [[6,1],[3,2],[2,3]]
>   输出：7
>   解释：要获得 6 分，你可以选择以下七种方法之一：
>   - 解决 6 道第 0 种类型的题目：1 + 1 + 1 + 1 + 1 + 1 = 6
>   - 解决 4 道第 0 种类型的题目和 1 道第 1 种类型的题目：1 + 1 + 1 + 1 + 2 = 6
>   - 解决 2 道第 0 种类型的题目和 2 道第 1 种类型的题目：1 + 1 + 2 + 2 = 6
>   - 解决 3 道第 0 种类型的题目和 1 道第 2 种类型的题目：1 + 1 + 1 + 3 = 6
>   - 解决 1 道第 0 种类型的题目、1 道第 1 种类型的题目和 1 道第 2 种类型的题目：1 + 2 + 3 = 6
>   - 解决 3 道第 1 种类型的题目：2 + 2 + 2 = 6
>   - 解决 2 道第 2 种类型的题目：3 + 3 = 6
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：target = 5, types = [[50,1],[50,2],[50,5]]
>   输出：4
>   解释：要获得 5 分，你可以选择以下四种方法之一：
>   - 解决 5 道第 0 种类型的题目：1 + 1 + 1 + 1 + 1 = 5
>   - 解决 3 道第 0 种类型的题目和 1 道第 1 种类型的题目：1 + 1 + 1 + 2 = 5
>   - 解决 1 道第 0 种类型的题目和 2 道第 1 种类型的题目：1 + 2 + 2 = 5
>   - 解决 1 道第 2 种类型的题目：5
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：target = 18, types = [[6,1],[3,2],[2,3]]
>   输出：1
>   解释：只有回答所有题目才能获得 18 分。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= target <= 1000`
>   -   `n == types.length`
>   -   `1 <= n <= 50`
>   -   `types[i].length == 2`
>   -   `1 <= counti, marksi <= 50`

##### 记忆化搜索

```c++
class Solution {
private:
    const int MOD = 1e9 + 7;
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        int n = types.size();
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (j == 0)
                return 1;
            if (i < 0) {
                return 0;
            }
            int& res = memo[i][j];
            if (res != -1)
                return res;
            int cnt = types[i][0], marks = types[i][1];
            // 枚举每个物品选择的次数
            res = 0;
            for (int k = 0; marks * k <= j && k <= cnt; k++) {
                res = (res + dfs(dfs, i - 1, j - k * marks)) % MOD;
            }
            return res;
        };
        return dfs(dfs,n - 1,target);
    }
};
```



##### 1:1 转为递归

==注意枚举 *k* 个的时候  *k* 要从 1 开始遍历即可==

```c++
class Solution {
private:
    const int MOD = 1e9 + 7;
public:
    int waysToReachTarget1(int target, vector<vector<int>>& types) {
        int n = types.size();
        vector<vector<int>> memo(n, vector<int>(target + 1, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (j == 0)
                return 1;
            if (i < 0) {
                return 0;
            }
            int& res = memo[i][j];
            if (res != -1)
                return res;
            int cnt = types[i][0], marks = types[i][1];
            // 选 k 个
            res = 0;
            for (int k = 0; marks * k <= j && k <= cnt; k++) {
                res = (res + dfs(dfs, i - 1, j - k * marks)) % MOD;
            }
            return res;
        };
        return dfs(dfs,n - 1,target) % MOD;
    }
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        vector<int> dp(target+1);
        dp[0] = 1;
        for(auto t:types){
            int cnt = t[0],marks = t[1];
            for(int j = target;j>=marks;j--){ //注意这里还是倒序遍历
                //枚举选多少个。
                for(int k = 1;k<=min(cnt,j/marks);k++){ //注意，这里 k 要从 1 开始，已经犯过很多次错了
                    dp[j] = (dp[j] + dp[j - marks * k]) % MOD;
                }
            }
        }
        return dp[target] % MOD;
    }
};
```



### 分组背包

分组背包，实际上就是同一组内的物品至多/恰好选一个。



#### 掷骰子等于目标和的方法数

力扣***[1155. 掷骰子等于目标和的方法数](https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/)***

>   这里有 `n` 个一样的骰子，每个骰子上都有 `k` 个面，分别标号为 `1` 到 `k` 。
>
>   给定三个整数 `n`、`k` 和 `target`，请返回投掷骰子的所有可能得到的结果（共有 `kn` 种方式），使得骰子面朝上的数字总和等于 `target`。
>
>   由于答案可能很大，你需要对 `109 + 7` **取模**。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：n = 1, k = 6, target = 3
>   输出：1
>   解释：你掷了一个有 6 个面的骰子。
>   得到总和为 3 的结果的方式只有一种。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：n = 2, k = 6, target = 7
>   输出：6
>   解释：你掷了两个骰子，每个骰子有 6 个面。
>   有 6 种方式得到总和为 7 的结果: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1。
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：n = 30, k = 30, target = 500
>   输出：222616187
>   解释：返回的结果必须对 109 + 7 取模。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= n, k <= 30`
>   -   `1 <= target <= 1000`



思路很简单，只要学好前面的背包问题自己也能推出

```c++
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        if (target < n || target > n * k) {
            return 0; // 无法组成 target
        }
        const int MOD = 1'000'000'007;
        vector<int> dp(target+1,0);
        dp[0] = 1;
        for(int i = 0;i<n;i++){
            for(int j = target;j >= 0;j--){
                dp[j] = 0; //不然会多加一个dp[i-1][j],实际上我们不能不选，至少都要选一个。所以我们要置空
                for(int p = 1;p<=k && p <= j;p++){
                    dp[j] = (dp[j] + dp[j - p]) % MOD;
                }
            }
        }
        return dp[target] % MOD;
    }
};
```



## 四、经典线性 DP



### 最长公共子序列 (*LCS*)

#### 最长公共子序列

力扣***[1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)***

>   给定两个字符串 `text1` 和 `text2`，返回这两个字符串的最长 **公共子序列** 的长度。如果不存在 **公共子序列** ，返回 `0` 。
>
>   一个字符串的 **子序列** 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
>
>   -   例如，`"ace"` 是 `"abcde"` 的子序列，但 `"aec"` 不是 `"abcde"` 的子序列。
>
>   两个字符串的 **公共子序列** 是这两个字符串所共同拥有的子序列。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：text1 = "abcde", text2 = "ace" 
>   输出：3  
>   解释：最长公共子序列是 "ace" ，它的长度为 3 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：text1 = "abc", text2 = "abc"
>   输出：3
>   解释：最长公共子序列是 "abc" ，它的长度为 3 。
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：text1 = "abc", text2 = "def"
>   输出：0
>   解释：两个字符串没有公共子序列，返回 0 。
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= text1.length, text2.length <= 1000`
>   -   `text1` 和 `text2` 仅由小写英文字符组成。



##### 记忆化搜索

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        //考虑选和不选
        int n = text1.size(), m = text2.size();
        vector memo(n,vector<int>(m,-1));
        auto dfs = [&](auto&&dfs,int i,int j)->int{
            if(i < 0 || j < 0) return 0;
            int& res = memo[i][j];
            if(res != -1) return res;
            char ch1 = text1[i],ch2 = text2[j];
            if(ch1 == ch2){
                return res = dfs(dfs,i-1,j-1)+1;
            }
            return res = max(dfs(dfs,i-1,j),dfs(dfs,i,j-1));
        };
        return dfs(dfs,n-1,m-1);
    }
};
```

##### 1:1翻译为递推

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(),n = text2.size();
        // dp[i][j] 代表 t1 前i个字母和 t2 中前 j 个字母组成的lcs
        vector dp(m+1,vector<int>(n+1,0));
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(text1[i] == text2[j]){
                    dp[i+1][j+1] = dp[i][j] + 1;
                }else{
                    dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);
                }
            }
        }
        return dp[m][n];
    }
};
```

##### 空间优化

如果把*dp*数组画成一个二维表，我们发现对于每个 `dp[i][j]`，它都是由正上方(`dp[i-1][j]`)，左上方(`dp[i-1][j-1]`)，以及左相邻(`dp[i][j-1]`)推过来的，和背包问题类似，我们可以把它优化成一维数组

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(),n = text2.size();
        //空间优化 dp[i][j]是由正上方，左上方，正左边推过来的，于是我们可以用一个一维数组优化
        vector<int> dp(n + 1,0);
        for(char c1:text1){
            int pre = 0;//暂时记录左上方的数据，因为下面会覆盖掉
            for(int j = 0;j<n;j++){ //注意，这里要用到正左边的数据，所以不能倒序遍历
                int temp = dp[j + 1];
                dp[j+1] = c1 == text2[j] ? pre + 1 : max(dp[j],dp[j+1]);
                pre = temp;
            }
        }
        return dp[n];
    }
};
```



####  编辑距离

力扣***[72. 编辑距离](https://leetcode.cn/problems/edit-distance/)***

>   给你两个单词 `word1` 和 `word2`， *请返回将 `word1` 转换成 `word2` 所使用的最少操作数* 。
>
>   你可以对一个单词进行如下三种操作：
>
>   -   插入一个字符
>   -   删除一个字符
>   -   替换一个字符
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：word1 = "horse", word2 = "ros"
>   输出：3
>   解释：
>   horse -> rorse (将 'h' 替换为 'r')
>   rorse -> rose (删除 'r')
>   rose -> ros (删除 'e')
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：word1 = "intention", word2 = "execution"
>   输出：5
>   解释：
>   intention -> inention (删除 't')
>   inention -> enention (将 'i' 替换为 'e')
>   enention -> exention (将 'n' 替换为 'x')
>   exention -> exection (将 'n' 替换为 'c')
>   exection -> execution (插入 'u')
>   ```
>
>    
>
>   **提示：**
>
>   -   `0 <= word1.length, word2.length <= 500`
>   -   `word1` 和 `word2` 由小写英文字母组成

##### 记忆化搜索

先从记忆化搜索入手，递归两个字符串 *s1*和*s2*

*   如果`s1[i] == s2[j]`，那么我们可以不必操作。

*   如果 `s1[i] ！= s2[j]`，我们要把*s1*转为*s2*考虑每种操作的实际意义：
    1.   删除下标 *i*，作逻辑上的删除，直接递归到*i-1*再和*s2*的下标 *j*比较即可，下一步操作是 *dfs(i-1,j)*；
    2.   替换下标 *i*，直接把下标 *i*替换为下标 *j*代表的字母，下一步操作是*dfs(i-1,j-1)*；
    3.   插入到下标 *i*（后面），我们直接插入下标 *j*代表的字母，下标 i 不变，我们要用 *s2*的下一个下标 *j-1*和下标 *i*比较，下一步操作是*dfs(i,j-1)*
    
    于是我们就得到了递推公式
    
    
    
    
    $$
    dfs(i,j)=
    \begin{cases}
    dfs(i-1,j-1) & \text{if }s[i] == s[j]\\ 
    \min(dfs(i-1,j),dfs(i,j-1),dfs(i-1,j-1))+1 & \text{if }s[i]!= s[j]
    \end{cases}
    $$
    **注意这里的递归出口**
    
    ``` c++
    class Solution {
    public:
        int minDistance(string word1, string word2) {
            int m = word1.size(),n = word2.size();
            vector memo(m,vector<int>(n,-1));
            auto dfs = [&](auto&&dfs,int i,int j)->int{
                if(i < 0){ // word1到头了，如果word2还剩，那么我还要在word1最前面插入 j + 1 个字符
                    return j + 1；
                }
                if(j < 0){ // word2到头了，如果word1还剩，那么我还要在word1最前面删除 j + 1 个字符
                    return i + 1;
                }
                int& res = memo[i][j];
                if(res!=-1) return res;
                if(word1[i] == word2[j]){
                    return res = dfs(dfs,i-1,j-1); //相同情况，不操作
                }else{
                    //删除 、 插入 、 替换
                    return res = min(dfs(dfs,i-1,j),dfs(dfs,i,j-1),dfs(dfs,i-1,j-1)) + 1; 
                }
            }
        }
    };
    ```



##### 1:1翻译为递推

``` c++
class Solution {
public:
    int minDistance(string s, string t) {
        int n = s.length(), m = t.length();
        vector f(2, vector<int>(m + 1));
        for (int j = 0; j < m; j++) {
            f[0][j + 1] = j + 1;
        }
        for (int i = 0; i < n; i++) {
            f[(i + 1) % 2][0] = i + 1;
            for (int j = 0; j < m; j++) {
                f[(i + 1) % 2][j + 1] = s[i] == t[j] ? f[i % 2][j] :
                        min({f[i % 2][j + 1], f[(i + 1) % 2][j], f[i % 2][j]}) + 1;
            }
        }
        return f[n % 2][m];
    }
};
```

一维数组

``` c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        //关于初始化： 我们可以先考虑二维的 dp 数组，容量为 （m + 1） x （n + 1）
        //那么 第一行 dp[0][k]就是下标 j 越界的情况 -> if(j < 0) return j + 1;  初始化为 j + 1
        //    第一列 dp[k][0]就是下标 i越界的情况  ->  if(j < 0) return i + 1;初始化为 i + 1
        int n = word2.size();
        vector<int> dp(n + 1);
        for (int j = 0; j < n; j++) {
            dp[j + 1] = j + 1; // if(j < 0) return j + 1;
        }
        for (char x : word1) {
            int pre = dp[0];
            dp[0]++; // if(j < 0) return i + 1
            for (int j = 0; j < n; j++) {
                int tmp = dp[j + 1];
                if (x == word2[j]) {
                    dp[j + 1] = pre;
                } else {
                    dp[j + 1] = min({dp[j + 1], dp[j], pre}) + 1;
                }
                pre = tmp;
            }
        }
        return dp[n];
    }
};
```



---



#### 一些好题

力扣***[712. 两个字符串的最小ASCII删除和](https://leetcode.cn/problems/minimum-ascii-delete-sum-for-two-strings/)*** —— 很常见但是有时候一下想不到的思想

力扣***[1458. 两个子序列的最大点积](https://leetcode.cn/problems/max-dot-product-of-two-subsequences/)*** —— LCS 的小变形

力扣***[718. 最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)***

力扣***[3628. 插入一个字母的最大子序列数](https://leetcode.cn/problems/maximum-number-of-subsequences-after-one-inserting/)*** ——前后缀分解技巧值得学习

力扣***[3316. 从原字符串里进行删除操作的最多次数](https://leetcode.cn/problems/find-maximum-removals-from-source-string/)*** —— 思路不难，但是很多细节要注意。

力扣***[1639. 通过给定词典构造目标字符串的方案数](https://leetcode.cn/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/)*** 

==力扣***[1092. 最短公共超序列](https://leetcode.cn/problems/shortest-common-supersequence/)*** —— 一道优秀的构造题 —— 可以参考 3592==



### 最长递增子序列 (*LIS*)

对于*LIS*问题，最常见的 DP 思路就是「枚举选哪个」，而不是「选和不选」。

力扣***[300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)***

>   给你一个整数数组 `nums` ，找到其中最长严格递增子序列的长度。
>
>   **子序列** 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。
>
>    
>
>   **示例 1：**
>
>   ```
>   输入：nums = [10,9,2,5,3,7,101,18]
>   输出：4
>   解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
>   ```
>
>   **示例 2：**
>
>   ```
>   输入：nums = [0,1,0,3,2,3]
>   输出：4
>   ```
>
>   **示例 3：**
>
>   ```
>   输入：nums = [7,7,7,7,7,7,7]
>   输出：1
>   ```
>
>    
>
>   **提示：**
>
>   -   `1 <= nums.length <= 2500`
>   -   *-10^4^ <= nums[i] <= 10^4^*

#### 「枚举选哪个」

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> memo(m);
        auto dfs = [&](auto&& dfs, int i) -> int {
            if (i < 0) {
                return 0;
            }
            int& res = memo[i];
            if (res > 0) {
                return res;
            }
            for (int k = 0; k < i; k++) {
                if (nums[k] < nums[i]) {
                    res = max(res, dfs(dfs, k));
                }
            }
            res++; //注意这里后手在让res + 1，保证长度为 1 的子序列
            return res;
        };
        
        //枚举子序列的最后下标
        int ans = 0;
        for (int i = 0; i < m; i++) {
            ans = max(ans, dfs(dfs, i));
        }
        return ans;
    }
};
```

递推写法

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int m = nums.size();
        vector<int> dp(m);
        for(int i = 0;i < m;i++){
            for(int j = 0;j < i;j++){
                if(nums[j] < nums[i]){
                    dp[i] = max(dp[j],dp[i]);
                }
            }
            dp[i]++;
        }
        return ranges::max(dp);
    }
};
```



#### 二分 + 贪心 （*nlog n* 的实现）

分析建议看[视频讲解](https://leetcode.cn/link/?target=https%3A%2F%2Fwww.bilibili.com%2Fvideo%2FBV1ub411Q7sB%2F)

```c++
class Solution {
//private:
    // //  返回下标 查找第一个大于等于 target 的数
    // int lowerBound(vector<int> v,int target){
    //     int left = 0,right = v.size(); //[left,right)
    //     while(left < right){
    //         int mid = left + (right - left) / 2;
    //         if(v[mid] >= target){
    //             right = mid;
    //         }else{
    //             left = mid + 1;
    //         }
    //     }
    //     return left;
    // }
public:
    int lengthOfLIS1(vector<int>& nums) {
        vector<int> d;
        for(int x:nums){
            int idx = upperBound(d,x);
            if(idx == d.size()){
                d.push_back(x);
            }else{
                d[idx] = x;
            }
        }
        return d.size();
    }
    //空间优化：直接 d 数组直接覆盖在原数组上
    int lengthOfLIS2(vector<int>& nums) {
        auto end = nums.begin();
        for(int x:nums){
            // int idx = lowerBound(d,x);
            auto it = lower_bound(nums.begin(),end,x);
            *it = x;
            if(it == end){
                end++;
            }
        }
        return end - nums.begin();
    }
};
```



如果不是**严格递增**，而是带有相同元素的递增，那么我们只要允许在 d 数组中不把等于 x 的数字覆盖掉而是在 d 数组后面加上就可以了。也就是只需把 *lower_bound*改为*upper_bound*即可



**这个贪心 + 二分还是很重要的，如果我只想求 k 元组的递增子序列，可以实现O(*n logk*) 的时间复杂度。**而传统 *dp*数据量一大肯定会超时。

### LCS 的进一步优化

回到最经典的 LCS 问题，如果两个数组的长度进一步大，1e5 次方以上，传统的 dp 时间复杂度是*O(mn)*的，一定会TLE，我们要想办法优化到*O(mlog n)*的情况下就能过了。这题就是***[1713. Minimum Operations to Make a Subsequence](https://leetcode.cn/problems/minimum-operations-to-make-a-subsequence/)***



其实 DP 有一种优化技巧，就是把状态值和下标进行交换，就和 LIS 的贪心优化一样，这里举一个例子。

>   对于数组 *target* = [5,1,3], *arr* = [9,4,2,3,4]
>
>   将 arr 中的元素转换成该元素在 target 中的下标（去掉不在 target 中的元素 7），可以得到一个新数组
>
>   ​								$arr ′=[1,0,5,4,2,0,3]$
>   若将 target 也做上述转换，这相当于将每个元素变为其下标，得
>
>   ​							$target ′ = [0,1,2,3,4,5]$
>
>   **注意**：这里原数组 *target*不能有元素重复，否则 *arr*在映射的时候下标混乱。
>
>   则求原数组的最长公共子序列等价于求上述转换后的两数组的最长公共子序列。
>
>   注意到 *target′*是严格单调递增的，因此 *arr′*在最长公共子序列中的部分也必须是严格单调递增的，因此问题可进一步地转换成求 *arr′* 的最长递增子序列的长度。这就变成了经典的 *LIS*问题了。

#### 实现

```c++
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        //  LCS的贪心优化
        unordered_map<int,int> umap;
        for(int i = 0;i < target.size();i++){
            umap[target[i]] = i;
        }
        vector<int> d;
        for(int val:arr){
            if(!umap.count(val)){
                continue;
            }
            int idx = umap[val];
            auto it = ranges::lower_bound(d,idx);
            if(it == d.end()){
                d.push_back(idx);
            }else{
                *it = idx;
            }
        }
        return target.size() - d.size();
    }
};
```





### 一些好题

力扣***[1671. 得到山形数组的最少删除次数 ](https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/)***—— 前后缀分解

力扣***[1964. 找出到每个位置为止最长的有效障碍赛跑路线](https://leetcode.cn/problems/find-the-longest-valid-obstacle-course-at-each-position/)*** —— 实际上很简单

#### 「套娃问题」

套娃问题也是 LIS 的一种变形，一般体现在某个更大的物品内能否塞下更小的物品，一般涉及多维的 LIS，一般思路是先对某个维度排序，详情见下面的***俄罗斯套娃信封问题***

==力扣***[354. 俄罗斯套娃信封问题](https://leetcode.cn/problems/russian-doll-envelopes/)***== —— 理解为什么那样排序

力扣***[1626. 无矛盾的最佳球队](https://leetcode.cn/problems/best-team-with-no-conflicts/)*** —— 上题的变形，但是不能不能「贪心 + 二分 」了

力扣***[1691. 堆叠长方体的最大高度](https://leetcode.cn/problems/maximum-height-by-stacking-cuboids/)*** —— 建议看灵茶题解和答疑。



力扣***[960. 删列造序 III](https://leetcode.cn/problems/delete-columns-to-make-sorted-iii/)*** —— 纸老虎

#### 「构造子序列」 —— from 数组的利用

==力扣***[368. Largest Divisible Subset](https://leetcode.cn/problems/largest-divisible-subset/)***==—— 如何构造答案？ ——  *from* 数组的妙用

力扣***[2901. Longest Unequal Adjacent Groups Subsequence II](https://leetcode.cn/problems/longest-unequal-adjacent-groups-subsequence-ii/)*** —— 同上



==力扣***[673. Number of Longest Increasing Subsequence](https://leetcode.cn/problems/number-of-longest-increasing-subsequence/)***==—— 求一共有多少个长度为 k 的递增子序列？





## 五、划分型 DP

### 1.判断能否能划分

一般定义 *f[i]*表示长为 *i* 的前缀 *a[:i]* 是否能划分。

枚举最后一个子数组的左端点 *L*，从 *f*[*L*] 转移到 *f*[*i*]，并考虑 *a*[*L*:*i*] 是否满足要求。



#### 检查数组是否存在有效划分

力扣***[2369. Check if There is a Valid Partition For The Array](https://leetcode.cn/problems/check-if-there-is-a-valid-partition-for-the-array/)***



>   You are given a **0-indexed** integer array `nums`. You have to partition the array into one or more **contiguous** subarrays.
>
>   We call a partition of the array **valid** if each of the obtained subarrays satisfies **one** of the following conditions:
>
>   1.  The subarray consists of **exactly** `2,` equal elements. For example, the subarray `[2,2]` is good.
>   2.  The subarray consists of **exactly** `3,` equal elements. For example, the subarray `[4,4,4]` is good.
>   3.  The subarray consists of **exactly** `3` consecutive increasing elements, that is, the difference between adjacent elements is `1`. For example, the subarray `[3,4,5]` is good, but the subarray `[1,3,5]` is not.
>
>   Return `true` *if the array has **at least** one valid partition*. Otherwise, return `false`.
>
>    
>
>   **Example 1:**
>
>   ```
>   Input: nums = [4,4,4,5,6]
>   Output: true
>   Explanation: The array can be partitioned into the subarrays [4,4] and [4,5,6].
>   This partition is valid, so we return true.
>   ```
>
>   **Example 2:**
>
>   ```
>   Input: nums = [1,1,1,2]
>   Output: false
>   Explanation: There is no valid partition for this array.
>   ```
>
>    
>
>   **Constraints:**
>
>   -   2 <= nums.length <= 10^5^
>   -   1 <= nums[i] <= 10^6^



##### 分析

对于每个下标 *i*，我们子数组要么是 *nums[i - 1 : i]* 要么是*nums[i - 2 : i]*，这两个区间，我们只需要考虑 *nums[i - 1 : i]* 、*nums[i - 2 : i]*是否合法，以及上一个子序列是否合法即可。

很容易得到递推公式：
$$
dp[i] = ∨
\begin{cases}
dp[i - 2] ∧ nums[i] == nums[i - 1] \\
dp[i - 3] ∧ nums[i] == nums[i - 1] == nums[i - 2] \\
dp[i - 3] ∧ nums[i] = nums[i - 1] + 1 == nums[i - 2] + 1 \\
\end{cases}
$$


##### 实现

```c++
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int m = nums.size();
        vector<bool> dp(m + 1, false);
        dp[0] = true;
        for (int i = 1; i < m; i++) {
            if (dp[i - 1] && nums[i] == nums[i - 1] ||
                i > 1 && dp[i - 2] &&
                    (nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2] ||
                     nums[i] == nums[i - 1] + 1 &&
                         nums[i - 1] == nums[i - 2] + 1)) {
                dp[i + 1] = true;
            }
        }

        return dp[m];
    }
};
```



---



### 2.最优划分

计算最少（最多）可以划分出多少段、最优划分得分等。

一般定义 f[i] 表示长为 i 的前缀 a[:i] 在题目约束下，分割出的最少（最多）子数组个数（或者定义成分割方案数）。

枚举最后一个子数组的左端点 L，从 f[L] 转移到 f[i]，并考虑 a[L:i] 对最优解的影响。



#### 分割回文串

力扣***[132. Palindrome Partitioning II](https://leetcode.cn/problems/palindrome-partitioning-ii/)***

>   Given a string `s`, partition `s` such that every substring of the partition is a palindrome.
>
>   Return *the **minimum** cuts needed for a palindrome partitioning of* `s`.
>
>    
>
>   **Example 1:**
>
>   ```
>   Input: s = "aab"
>   Output: 1
>   Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
>   ```
>
>   **Example 2:**
>
>   ```
>   Input: s = "a"
>   Output: 0
>   ```
>
>   **Example 3:**
>
>   ```
>   Input: s = "ab"
>   Output: 1
>   ```
>
>    
>
>   **Constraints:**
>
>   -   `1 <= s.length <= 2000`
>   -   `s` consists of lowercase English letters only.



##### 分析

由于本题数据量 10e3，我们必须预处理每个区间的回文串，否则光是每次判断回文串的时间开销是*O(n ^2^)*，乘以递推寻找分割线的时间复杂度*O(n)*，*O(n^3^)*显然会超时。







##### *dfs*

```c++
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector pal_memo(n, vector<int>(n, -1)); // -1 表示没有计算过
        auto is_palindrome = [&](this auto&& is_palindrome, int l, int r) -> bool {
            if (l >= r) {
                return true;
            }
            int& res = pal_memo[l][r]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            return res = s[l] == s[r] && is_palindrome(l + 1, r - 1);
        };

        vector<int> dfs_memo(n, INT_MAX); // INT_MAX 表示没有计算过
        auto dfs = [&](this auto&& dfs, int r) -> int {
            if (is_palindrome(0, r)) { // 已是回文串，无需分割
                return 0;
            }
            int& res = dfs_memo[r]; // 注意这里是引用
            if (res != INT_MAX) { // 之前计算过
                return res;
            }
            for (int l = 1; l <= r; l++) { // 枚举分割位置
                if (is_palindrome(l, r)) {
                    res = min(res, dfs(l - 1) + 1); // 在 l-1 和 l 之间切一刀
                }
            }
            return res;
        };
        return dfs(n - 1);
    }
};
```





##### 递推

```c++
class Solution {
public:
    int minCut(string s) {
        int m = s.size();
        //预处理回文串
        vector<vector<bool>> isPalindrome(m,vector<bool>(m,false));
        for(int i = 0;i < m;i++){
            for(int j = 0;j <= i;j++){
                if(s[i] == s[j] && (i - j <= 2 || isPalindrome[j + 1][i - 1])){
                    isPalindrome[j][i] = true;
                }
            }
        }
        vector<int> dp(m + 1,INT_MAX / 2);
        dp[0] = 0;
        for(int i = 0;i < m;i++){
            for(int j = 0;j <= i;j++){
                if(isPalindrome[j][i]){
                    dp[i + 1] = min(dp[i + 1],dp[j] + 1);
                }
            }
        }
        return dp[m] - 1;
    }
};
```



#### 一些好题

力扣***[3196. Maximize Total Cost of Alternating Subarrays](https://leetcode.cn/problems/maximize-total-cost-of-alternating-subarrays/)*** —— 直接考虑本质

力扣***[3578. Count Partitions With Max-Min Difference at Most K](https://leetcode.cn/problems/count-partitions-with-max-min-difference-at-most-k/)*** —— 考虑堆和优先级队列两种解法



### 数位 DP