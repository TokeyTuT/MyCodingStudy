## JAVA 常识

相比于 c++，Java 更安全。

在 Java 中，我们不需要手动释放内存，只有**基础数据类型 int、double、float、char……等是储存在栈区的**，**其他的数据全部储存在堆区**。堆区的释放规则就是，如果我们没有对象再指向这个堆区内存的地址，它会立即被释放。

并且在函数传递的时候，Java 没有所谓的引用传递，对于基本数据类型，只有值传递。

除此之外，不同于 c++，Java 在打印 *boolean* 值的时候是会显示 *false* 和 *true* 的





## 关于IDEA

### 快捷键

1.   *Alt + (Fn) + Insert  (Windows)*   / *commamd + N  (Mac)* 一键生成 *Javabean*  

2.   插件 PTG 一键生成标准*Javabean*，右键选中即可。

3.   |  缩写   |                       含义                        |
     | :-----: | :-----------------------------------------------: |
     | *psvm*  |               快速生成 `main` 方法                |
     | *sout*  |              System.out.println();`               |
     | *soutv* |      `System.out.println("变量名=" + 变量);`      |
     | Sc* + ↩︎ | `Scanner sc = new Scanner(System.in); sc.next();` |

### IDEA规范项目结构

Project
	module
		package
			class

## 字符串

### 1、String

`String`已经定义在`java.lang`包中，不需要导包。

和 c++不同，Java 中字符串一旦被创建就不能被修改。

```java
public class Main{
	public static main(String[] args){
		String s = "Tokey";
        s = "TokeyTuT"; //合法，实际上是创建了两个字符串。 s实际上是地址改变了
		//但是不能向 c++一样有类似 s。pop_back()的操作
        //但是可以有  + 这种操作
        //底层还是创建了一个新字符串
        
	}
}
```

#### 初始化

String 有四种初始化的方式

1.   直接赋值`String s1 = "hello world;"`
2.   用`new`创建 空字符串对象`String s2 = new String();`
3.   用`char[]`初始化`char[] ch = {'a','b','c'}; String s3 = new String(s3);`
4.   用`bytes[]`初始化，见下：![image-20260119172817479](https://p.ipic.vip/8tlt5o.png)

**注**：

使用双引号直接赋值的时候，系统会先检索堆区的字符串池是否已经存在一样的，如果存在就会复用，直接指向这块内存，如果不存在，会创建新的。由于`String`是不允许被修改的，所以我们不用担心修改问题。

但是如果一个是 new 出来的，一个是双引号引出来的，那么就不会复用了，new 会创建一个新的内存。



#### 比较

由于 String 的对象名存储的是字符串的地址，所以常规的“==”运算符会出现一些问题，考虑下面两段代码。

>   ```
>   public class Test{
>   	public static void main(String[] args){
>   		String a = "abc";
>   		String b = "abc";
>   		System.out.println(a == b); // true
>   		
>   		String c = new String "abc";
>   		String d = "abc";
>   		System.out.println(c == d); // false
>   	}
>   }
>   ```

原理可以见上面初始化的注释。

在Java 中已经提供了这样的方法给我们比较两个字符串是否一致。

>   1.   `s1.equals(String s2)` 不忽略大小写，两个字符串要完全一致
>   2.   `s2.equalsIgnoreCase(String s2)`忽略大小写

**注意**
Java 中的 *String*不能通过索引访问，如果我们想要查找某个下标代表的字符，我们只能用`charAt(int index)`方法。
或者使用 `toCharArray`方法，如下

```Java
String str = "Hello";
char[] charArray = str.toCharArray(); // 转字符数组
char c = charArray[1]; // 'e'，此时可以用[]
charArray[1] = 'a'; // 修改为'Hello'
String newStr = new String(charArray); // 转回String
```



### 2、StringBuilder

StringBuilder 可以看作是一个容器，里面存储的内容是可变的。

考虑下面这个案例：

>   String s = s1 + s2 + s3 + s4;
>
>   每一次相加，编译器都会创建一个新的 String，非常浪费内存，StringBuilder 就是用来解决这个问题的。



#### 初始化

1.   `StringBuilder sb = new StringBuilder()`空容器
2.   `StringBuilder sb = new StringBuilder("abc")` 赋值

#### 方法

|              方法名              |                 说明                 |
| :------------------------------: | :----------------------------------: |
| `public StringBuilder append()`  |               添加内容               |
| `public StringBuilder reverse()` |                 反转                 |
|      `public int length()`       |               获取长度               |
|    `public String toString()`    | 讲 `StringBuilder `容器转为` String` |



### 3、StringJoiner

*StringJoiner*和 *StringBuilder*差不多，都是一个*String*的容器，但是*StringJoiner*更好的对字符串进行格式化。

***注***：*StringJoiner* 要导入`java.util.StringJoiner`



### 使用说明

|                             方法                             |                             说明                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
|       `StringJoiner sj = new Stringjoiner(delimiter)`        |         在每个添加的字符串后面加上分割符*delimiter*          |
| `StringJoiner sj = new Stringjoiner(delimiter,prefix,suffix)` | 在开头加上*prefix*,结尾加上 *suffix*，每个添加的字符串后面加上分割符 *delimiter* |



|     方法      |      功能       |
| :-----------: | :-------------: |
|  `.length()`  | 获取字符串长度  |
|    `.add`     |   添加字符串    |
| `.toString()` | 转化为 `String` |



## 集合

Java 中的集合是用来同时存储多个数据，具有自动扩容的功能 。

但是 Java 中的集合有些特别。

*   对于数组，Java **允许存储基本数据类型(*int*、*double*……)和引用数据类型(*String*,自定义类……)**

*   对于集合，Java **只允许存储引用数据类型**，对于*int、double、char*等基本数据类型是不被允许的，但是 Java 中提供了包装类储存他们。

常见的集合有： *ArrayList*、HashMap 、HashSet…… 

### 基本数据类型的包装类

Java 提供了一些基本数据类型的包装类

规则很简单，除了 *int*以及*char*外，其余的基本数据类型的包装类只要原数据类型上给第一个字母大写即可

对于 *int*和 *char*，他们的包装类分别是 *Integer* 以及 *Character*

---



## ArrayList

*ArrayList*就是一种集合 就是 Java 中的可变数组，相当于 C++ 中的 *vector *容器。

### 初始化

`ArrayList<E> ls = new ArrayList<>();`

其中 *E*，代表一个泛型。

***注***：如果我们打印输出 *ls*，这个类 Java 做了一些底层处理，直接打印对象`System.out.println(ls)`不是地址值，而是 *ls*存储的内容，并且会自动用“[ ]”括住里面的数据。

### 方法

|        方法        |              说明               |
| :----------------: | :-----------------------------: |
|     *add(E e)*     |       添加之后返回 *true*       |
|   *remove(E e)*    |  按值删除，删除成功返回 *true*  |
| *remove(int idx)*  | 按索引删除，删除成功返回 *true* |
| *set(int idx,E e)* | 按索引修改，返回修改之前的元素  |
|   *get(int idx)*   |    按索引取值，返回索引的值     |
|      *size()*      |         返回集合的大小          |





## Javabean类 、 测试类、工具类

1.   Javabean 类是描述一类事物的一个类，比如 *Student 、Cat、Dog* 类

2.   测试类是测试程序的一个类，常常包含 *main*函数，通常用 *static* 修饰成静态方法

3.   工具类是用来提供工具方法的一个类，比如说 *Math*类，里面的方法常用 *static* 修饰成静态方法，通过类名进行调用

      >   这种类具有一个特点：***private*修饰构造方法，也就是不能被实例化**，通过类名调用成员方法。
      >
      >   比如 `Math.max(x,y);`

## static关键字

静态有关的东西都是存在堆区的，它在堆区有一块静态区

### 静态成员变量

和C++中的静态成员变量一样，程序开始的时候就已经存在，并且优先于类前创建。

### 静态方法

和C++中静态成员函数一样。可以通过对象或者类名调用。常用于**测试类和工具类**。

**静态方法只能访问静态成员和静态方法**，并且和 c++一样，**静态成员方法没有 *this* 指针**



## 继承

Java 中用 ***extends*** 关键字继承，并且和 C++ 不同，Java 中只允许**单继承**，不允许多继承，这就规避了 C++ 的菱形继承的问题，不需要用到所谓的*virtual* 继承。
但是，Java 中运行多层继承，比如

>   子类 A 继承 父类 B，父类 B 可以继承父类 C

对于 Java，在虚拟机创建时，所有的都会直接或者间接继承与 ***Object*** 类

### 能够继承的类型

1.   父类的构造方法不能被继承

2.   父类的所有成员变量都可以被继承，**包括被*private*修饰的成员变量**，只是**子类对象不能调用**

3.   对于成员方法，和成员变量不同，**被 *private*修饰的成员方法不能被继承**

     >   关于成员方法的继承，对于每个对象，虚拟机会创建一个**虚方法表**，里面记录了虚方法，虚方法是是指**非 *private、static、final* 修饰的成员方法**。相当于一个“字典”，用来检索每个方法存在在哪个类中，以便快速访问。
     >
     >   这个虚方法表中存储在方法区中

### super 关键字

**super **用于访问父类中的成员变量和函数，比如子类中有 *name*成员变量，父类中也有，我们想要访问父类中的 *name*，而不是本类的，我们就用`super.name`即可

### 方法的重写

如果我们要对父类的方法在子类中重写，我们要注意在子类的重写方法上加一个 **@Overwirite** 注解，用于提示虚拟机和程序员这是重写的方法。

方法重写的本质就是覆盖了虚方法表中的父类方法。

**注意**

![image-20260130224027603](https://p.ipic.vip/44uvam.png)



### 构造方法

构造方法不会被继承，所以我们要在子类中再写一个构造方法，注意**对于子类的所有构造方法，都会在最开始调用父类中的默认构造方法，如果我们要手动调用这个方法，我们可以用`super()`调用**

如果我们想要访问父类的有参构造方法，我们需要用`super(构造参数……)`



注意**`super()`**构造方法在创建类的时候只会调用一次，并且一定在构造方法的第一个语句中。

关于*this*：

>   如果我们在本类中的默认构造方法中写`this(有参构造的参数……)`，相当于给了一个默认参数，并且只会调用有参构造的`super()`方法







## 多态

### 多态实现条件

1.   有继承 / 实现关系
2.   父类引用指向子类对象
3.   要有方法重写

### 多态调用成员的规则

*   成员变量： 编译看左边，运行看左边

    >   比如这里有一个父类 *Animal*和一个子类 *Cat*，其中，*Animal*和 *Cat*都有一个成员变量*name*,分别为`String name = "动物"`、`String name = "猫"`，如果我们用多态的语法创建对象，如下，观察下面程序运行的结果
    >
    >   ```java
    >   public class main{
    >       public static void main(String[] args){
    >           Animal c = new Cat();
    >           sout(c.name);
    >       }
    >   }
    >   ```
    >
    >   运行结果为 **“动物”**，也就是说，对于成员变量，我们运行的时候实际上调用的是左边类（父类）的成员。
    >
    >   编译看左边的意思就是，如果*Animal*没有*name*这个成员，编译会报错。

    

*   成员方法： 编译看左边，运行看右边

>   类似上面的例子，如果 *Animal*和 *Cat*中都含有一个 *show()*方法，在调用 *show*方法的时候，会调用的是 *Cat*的 *show* 方法

### 多态的弊端

多态实例化的对象不能使用子类对象特有的功能。

解决方案：

```java
Animal a = new Cat();
Cat c = (Cat)a;  // 直接转换就行，解决了上面的弊端
```

注意，转换的时候只能转换为子类，不能转化为兄弟类，比 *Cat* 不能转化为 *Dog*

在实际开发的时候，我们也许不能清楚的明白哪个能转换哪个不能转。，这里我们引入一个 Java 关键字`instanceof`,用于指示这个变量指向的对象是否为目标对象

```java
if(a instanceof Cat){
    Cat c = (Cat) a;
}else{
    Dog d = (Dog) a;
}
```

![image-20260131195119308](https://p.ipic.vip/z86bvy.png)

## Final关键字

*   方法：表示该方法是最终方法，不能被重写

*   类：表明这个类是最终类，不能再被继承了

*   变量：叫做常量，只能被赋值一次

    >   注： 和 C++类似，*final*修饰的变量如果如果是引用数据类型，那么那么他的地址值不能改变，但是地址值对应的内部属性可以改变也就是说，*final*修饰的引用数据类型只是不能指向别的地址值而已。



## 权限关键字

![image-20260131200844759](https://p.ipic.vip/7vqn2k.png)



## 静态代码快

语法：`static{}`。

特点： 随着类的加载而加载，并且只执行一次，并且静态代码块只能被 *static* 修饰的成员和方法



## 抽象类和抽象方法

相当于 C++中的 *virtual*关键字，Java 中用*abstract*关键字修饰。

同样的，抽象类不能被实例化，并且要子类重写抽象方法

**注意：**

1.   抽象类不一定有抽象方法。

2.   抽象类可以有构造方法

3.   有抽象方法的类一定是抽象类

4.   抽象类不能被实例化

5.   抽象类的子类：

     *   要么子类也是抽象类

     *   要么子类中的一定要重写父类全部的抽象方法

         这里有一个快捷键 *alt + enter* / *option + enter*直接全部重写抽象方法

## 接口

和抽象类不同，接口是一种规则，适用于所需要的类。

### 接口的语法

![image-20260131203807327](https://p.ipic.vip/pkacwp.png)

接口只是提供一种规则，如命名规范，参数应该传递什么类等等，注意，**实现类中一定要重写这个抽象方法**

### 接口的成员特点

![image-20260131204628830](https://p.ipic.vip/cu5b79.png)



### ==接口多态==

**可以让接口引用直接指向实现类对象**

```java
// 1. 定义一个接口（能力说明书）
interface Flyable {
    // 接口中默认是 public abstract 的抽象方法
    void fly();
}

// 2. 实现类1：鸟实现飞行接口
class Bird implements Flyable {
    @Override
    public void fly() {
        System.out.println("小鸟扇动翅膀飞行");
    }
}

// 3. 实现类2：飞机实现飞行接口
class Plane implements Flyable {
    @Override
    public void fly() {
        System.out.println("飞机靠引擎推动飞行");
    }
}

// 4. 测试类：展示接口多态的核心用法
public class InterfacePolymorphismDemo {
    // 通用方法：接收 Flyable 类型的参数（接口引用）
    public static void letItFly(Flyable flyable) {
        flyable.fly(); // 调用时执行实际对象的 fly 方法（多态核心）
    }

    public static void main(String[] args) {
        // 接口多态的核心体现：接口类型引用指向实现类对象
        Flyable f1 = new Bird();   // 接口引用指向 Bird 对象
        Flyable f2 = new Plane();  // 接口引用指向 Plane 对象

        // 调用方法时，执行的是实际对象的实现逻辑
        f1.fly(); // 输出：小鸟扇动翅膀飞行
        f2.fly(); // 输出：飞机靠引擎推动飞行

        // 更实用的场景：通用方法接收不同实现类对象
        letItFly(new Bird());  // 输出：小鸟扇动翅膀飞行
        letItFly(new Plane()); // 输出：飞机靠引擎推动飞行
    }
}
```



### 接口与接口的关系

与类不同，接口与接口**可以单继承，也可以多继承**
但是实现类中，需要把接口体系中所有的抽象方法重写

#### 进阶

![image-20260131211628563](https://p.ipic.vip/od63s7.png)

### 适配器设计模式

考虑下面的业务场景

>   现已经有了一个接口 *Inter*，里面有10 个方法分别是*method1*、*method2*、……、*method10*，但是现在我的实现类*InterImpl*中只需要当前只需要实现 *Inter*中的一个接口，如果传统的直接 *implement Inter*,那么我就需要在 *InterImpl* 重写 10 个 method 的方法，这样降低了代码的可读性。怎么办呢？

我们引入了适配器设计模式。

我们创建一个新的 Java 类*InterAdapter*，在这个类中对接 *Inter*，但是在这个类中给 *Inter*的抽象方法空实现。然后我们在*InterImpl*中继承 *InterAdapter*，在*InterImpl*重写我们需要用到的接口方法即可。

我们创建的适配器通常不需要被外界实例化，所以我们通常给给适配器加上*abstract*关键字。



## 内部类

内部类就是在一个类内在写一个类

定义规则：

*   内部类表示的事物是外部类的一部分
*   内部类单独出现没有任何意义

满足上面两种规则的情况下，我们可以定义内部类

比如说

```java
public class Car{
	String name;
    String color;
    class Engine{
		String EngineName;
        int EngineAge;
        //构造略
    }
    //构造略
}
```



访问特点：

*   内部类可以直接访问外部类的成员，包括私有
*   外部类要访问的内部类成员，必须要创建对象



### 内部类的分类

### 成员内部类

![image-20260131215936518](https://p.ipic.vip/ph1mzl.png)

### 静态内部类

静态内部类就是成员内部类被*static*修饰。

规则：

*   **静态内部类只能访问外部类的静态对象**
*   可以直接打点调用静态内部类的方法和对象

![image-20260131220209663](https://p.ipic.vip/h7s5bd.png)



### 局部内部类

![image-20260131220510225](https://p.ipic.vip/ym8bd1.png)

没什么鸟用，了解即可



### ==匿名内部类==

匿名内部类的本质就是隐藏了名字的内部类

### 语法： 

```java
public class Test{    
	public static void main(String[] args){
        //匿名内部类重写结构
        new Swim(){
            @Overwrite
            public void Swim(){
                sout<<"匿名内部类的 Swim接口 重写"<<endl;
            }
        };
        //匿名内部类继承对象
        new Animal(){
			@Overwrite
            public void eat(){
				sout<<"匿名内部类重写继承 Animal 抽象方法"
            }
        }；
    }
}
```



**匿名内部类也会独立生成一个 class 字节码文件**

### 使用：

```java
public class Test{    
	public static void main(String[] args){
        
        //1.对于某个子类，如果我们只需要用一次就舍弃，
        //传统方法是创建一个 Dog 类继承 Animal 类
        Dog d = new Dog();
        method(d);
        
        
        //太麻烦了，用匿名内部类继承 Animal
        method(
            new Animal(){
                @Overwrite
                public void eat(){
                    sout<<"匿名内部类重写继承 Animal 抽象方法"
                }
            }
        );
        
        //2.利用接口多态重写接口
        Swim s = new Swim(){
            @Overwrite
            public void Swim(){
                sout<<"匿名内部类的 Swim接口 重写"<<endl;
            }
        };
        s.swim();
        
    }
    public void method(Animal a){
        a.eat();
    }
}
```



## 常用API

### System

1.   `exit(int status)`，关闭虚拟机,如果传入0为正常关闭，如果传入1为异常关闭
2.   `currentTimeMills()`:获取当前时间的毫秒值
3.   `arrayCopy()`拷贝数组，其中要传入五个参数，第一个参数是原数组，第二个参数要拷贝的数据在原数组的起始下标，第三个参数是目标数组，第四个参数是目标数组的开始下标，第五个参数是要拷贝数据的个数。

### Runtime

![截屏2026-02-03 19.38.57](https://p.ipic.vip/5apn3u.png)

**注意**：Runtime 的各种成员方法需要通过对象来调用，但是 *Runtime*的构造方法被 *private*修饰了，我们需要通过调用静态方法`Runtime.getRuntime()`去获得*Runtime*对象。

>   观察 *Runtime*的底层代码，我们发现，*Runtime*实际上有一个成员对象：
>
>   ​					`private final Runtime currRuntime = new Runtim()`
>
>   由于他的构造方法是被 *private*修饰的，这也就导致了外部无法创建 *Runtime*对象，但是 *Runtime*提供了*getRunTime()*静态方法，这就导致了在虚拟机运行当中，有且仅有一个 *Runtime*对象，这也符合常理，应为一个虚拟机中创建多个 *Runtime*对象是没意义的。

比如说

```java
Runtime r1 = Runtime.getRuntime();
r1.totalMemory();
r1.exit(0);
//……
```



### Object

*Object*类是所有类的顶级父类。

#### toString 方法

*toString*方法是用于类似 *System.out.println(E e)*自动调用的方法。

*Object*中的 toString 默认打印对象的地址值。如果想要打印对象的属性值，需要重写 *toString*方法



#### equals 方法

*equals*方法在*Object*类中的实现就是比较两个对象的地址值，如果我们想要比较两个对象是否有相同的属性值，那么我们需要对 *equals*进行重写。

特殊的，对于 *String*和 *StringBuilder*这两个类中，Java 只重写了 *String*这个类中的 *equals*，*StringBuilder*这个类还是比较地址值



#### clone方法（深浅拷贝）

*Object*的 *clone()*是浅拷贝，如果需要深拷贝，我们通常用到第三方工具类 *Gson*。



### Objects

*Objects*是 *Object* 的一个工具类



![image-20260203210518215](https://p.ipic.vip/2uqs4h.png)



### BigInteger

BigInteger 是用于表示大数的类，在人类计算机储存极限内，可以认为这个数是无限大的。

![image-20260203210801483](https://p.ipic.vip/p072in.png)

**注意**，对象一定创建，就不能修改里面的值。并且 *valueOf*最大不能超过 *long*的范围

![image-20260203211309867](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260203211309867.png)



### BigDecimal

BIgDecimal 用于创建精确小数

![image-20260203233346497](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260203233346497.png)





## 正则表达式



![image-20260204000657383](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260204000657383.png)

**注：**如果要忽略大小写，那么就在要忽略大小的的整体前面加上 ***( ?i )***，再给整体打上括号分组。



如果我们要判断一个字符串是否符合正则表达式 *regex*，我们调用 *String*方法的 *matches(String regex)*方法即可，返回值为 *boolean*类型。

### 利用正则表达式提取信息

假设要提取的字符串为 *s*，具体操作如下：

1.   获取正则表达式的对象：`Pattern p = Pattern compile(String regex);`
2.   获取文本匹配器的对象：`Matcher m = p.matcher(s);`
3.   调用 *Matcher*中的 *find()*方法，返回一个 *boolean*类型，并且在底层记录一个一个起始索引和目标索引的下标+1，也就是$[left,right + 1)$。
4.   调用 *group()*方法打印符合要求的子串。

```java
public class Main{
	public void main(String[] args){
		String s = "……";
        Pattern p  = s.compile(regex);
        Matcher m = p.matcher(s);
        while(m.find()){
			sout(m.group());
        }
    }
}
```

### 带条件爬取

这里介绍三种条件爬取

![image-20260209222328101](https://p.ipic.vip/vh516j.png)



### 贪婪爬取和非贪婪爬取

对于一个字符串“abbbbbbb”，如果我们想要爬取“abbbbbbb”，叫做贪婪爬取，如果我们只想获得“ab”，叫做非贪婪爬取

![image-20260209222646419](https://p.ipic.vip/7ri962.png)



### 正则表达式在 *String*中的应用

![image-20260209222743253](https://p.ipic.vip/99sz3v.png)



### 捕获分组

以左括号为基准，从 1 开始，每一个左括号为 一组

![image-20260209223512965](https://p.ipic.vip/8jj8o7.png)



![image-20260209223708323](https://p.ipic.vip/ubciit.png)

### 非捕获分组

![image-20260209223814608](https://p.ipic.vip/cl8o41.png)



![image-20260209224047073](https://p.ipic.vip/aam1mj.png)





## 时间 API



### Date 类

![image-20260210155433029](https://p.ipic.vip/kq9q1y.png)

获取到毫秒值之后我们就可以进行比较两个时间谁大谁小了。

**注**：这里获取的时间是 1970 年 1 月 1 日 8:00 经过之后的毫秒时。

并且 Date 类已经重写了 toString 方法，可以直接打印。



### *SimpleDateFormat*类

*SimpleDateFormat*类有两个作用：

1.   格式化时间输出的结果的
2.   解析字符串中的时间变成 Date 对象

#### 构造方法

*   空参构造：`SimpleDateFormat sdp = new SimpleDateFormat()`
*   有参构造：`SimpleDateFormat sdp = new SimpleDateFormat(String pattern)`

#### 成员方法

*   `format(Date date)`:根据构造方法中的 *pattern*格式进行打印输出，返回 *String*
*   `parse(String date)`；根据构造方法中的 *pattern*格式进行解析，返回 *Date*类



**注**：对于 *pattern*方法，我们必须要根据实际代表的字母一一对应：年 —— *yyyy*、月 ——*MM*、日——*dd*、时——*HH*、分——mm、秒 —— *ss*



### Calender

![image-20260210162306985](https://p.ipic.vip/p4bge2.png)

![image-20260210162157057](https://p.ipic.vip/rjeg0w.png)



## 包装类



### Integer

![image-20260210164541041](https://p.ipic.vip/u8u210.png)

静态方法，直接打点调用即可。

![image-20260210164828639](https://p.ipic.vip/o6h67s.png)







## Stream 流

Stream 流可以理解为“一条流水线”，作用是**结合了 lambda 表达式，简化了集合、数组的操作**

Stream 流的操作步骤：

>   1.   得到一个 Stream 流，并且把数据放上去
>   2.   利用 Stream 流中的中间方法进行操作
>   3.   利用 Stream 流中的终结方法进行操作



### 获取 Stream 流

1.   ##### 单列集合获取 Stream 流

     >   利用 Collection 中的默认方法 stream()即可，不需要调用方法类 Collections
     >
     >   ![image-20260216154722095](https://p.ipic.vip/cf599v.png)

2.   ##### 双列集合获取 Stream 流

     >   双列集合不能直接获取 Stream 流，我们可以利用 entrySet()方法或者 keySet()方法将双列集合转为单列集合进行操作。
     >
     >   ![image-20260216154913917](https://p.ipic.vip/q0q8wn.png)

3.   ##### 数组获取 Stream 流

     >   数组获取 Stream流要调用方法类 Arrays 中的 stream 方法
     >
     >   ![image-20260216155123139](https://p.ipic.vip/2md3fi.png)

4.   ##### 一堆零散的数据获取 Stream 流

     >   如果我们有一些数据没有成数组或者集合，我们可以直接调用 Stream 中的静态方法of() ，方法的形参是一个可变参数。
     >
     >   ![image-20260216155408182](https://p.ipic.vip/gc7xs0.png)



### Stream 流的中间方法

![image-20260216155524368](https://p.ipic.vip/atezgb.png)

**重点上面的的两个注意点**，再次提醒，中间方法返回的是一个新的 Stream 流，建议使用链式编程。



1.   filter 中的参数应该填一个接口 *Predicate*，是一个函数式接口，可以用 lambda 表达式简化。这个接口的返回值为 boolean 类型，代表是否滤过。

2.   对于 *skip*和 *limit*方法，其中的参数代表的是元素的**个数**

3.   对于 *distinct*方法，如果我们要使用自定义数据类型，我们一定要重写 *hashCode* 和 *equals* 方法

4.   对于 map 方法，如果我们使用匿名内部类的语法重写 Fuction，其中第一个泛型 T 代表原本的类型，第二个泛型 R 代表我们需要传唤的方法。

     >   ![ ](https://p.ipic.vip/pdqz6v.png)
     >
     >   如果我们要写成 lambda 表达式：
     >
     >   ```java
     >   list.stream().map(s -> Integer.parseInt(s.split('-')[1]).forEach(s -> sout(s));
     >   ```
     >
     >   





### Stream 流的终结方法

![image-20260216161240562](https://p.ipic.vip/2fsfau.png)



1.   ###### 关于 *toArray()* 方法：

    >   *toArray()*方法具有两个重载，一个是空参，一个是带有接口 *IntFuction<? extends Object[]>*
    >
    >   1.   对于空参方法，如果我们直接使用 *toArray()*作为终结方法，那么我们默认得到的是一个 *Object* 数组。
    >
    >   2.   对于有参方法，如果我们使用匿名内部类的方法调用，那么他应该遵从的语法如下： 
    >
    >        ![截屏2026-02-16 16.21.30](https://p.ipic.vip/g712pb.png)
    >
    >        如果我们要写成 *Lambda*表达式，那么：
    >
    >        ```java
    >        String[] arr = list.stream().toArray(value -> new String[value]);
    >        ```
    
1.   ###### 关于 collect 方法

    >   *   对于 *collect*方法将 Stream 流转 *list* 和 *set* 很简单，直接在 *collect()*方法呢内加上参数 *Collectors.toList() / Collectors.toSet()* 即可。
    >
    >   *   如果我们要讲 Stream 流转为 *Map*，有一点麻烦，我们要先调用*Collectors.toMap()* 方法，但这是个有参构造，里面有两个函数式接口泛型  —— *Fuction<T,R>。*重写方式如下： 
    >
    >       ![image-20260216164023526](https://p.ipic.vip/2v70zi.png)
    >
    >       ![image-20260216163903561](https://p.ipic.vip/uwef0g.png)

**注意**：使用toMap 进行转换的时候，原本的流中不能有相同的键值，否则会报错！



## 方法引用

1.   方法引用引用处必须是函数式接口
2.   被引用的方法必须已经存在
3.   被引用的方法的形参和返回值需要跟抽象方法的形参保持一致
4.   被引用的方法的功能必须要满足当前的需求

### 静态方法引用

格式 ： 类名::类名方法 *eg*. Integer::parseInt()



![image-20260216223340092](https://p.ipic.vip/fzc0tg.png)

### 引用成员方法

*   格式： 对象::成员方法
    1.   其他类 ： 其他类对象::方法名
    2.   本类 ： this:: 方法名
    3.   父类 ：supper::方法名

注意对于 2、3 类，引用处不能是静态方法



![image-20260216224122396](https://p.ipic.vip/qqin1e.png)

根据上面的例子，我们可以看出，我们不必再*implements ActionListener* 了并且也不需要再进行*Object oj = e.getSorce()*这个操作，因为只有按了 *Go*按钮才会调用 *method1*方法。



### 引用构造方法

格式： 类名::new

如果我们要使用引用构造方法构造对象，那么我们必须在原来的类中重写一个构造方法，构造方法传入的参数必须和我们流中的类保持一致。

![image-20260216224701134](https://p.ipic.vip/qr7oj9.png)

![image-20260216224648987](https://p.ipic.vip/h3uef4.png)



### 类名引用

![image-20260216225555215](https://p.ipic.vip/cd584x.png)

**再次强调**：

*   这种类名引用具有局限性，只能够引用函数式接口中抽象方法第一个形参的类型。
*   并且从抽象方法第二个形参开始，类名引用的第一个形参要和其一一对应。



## 异常

异常分为两种：**编译型异常**、**运行时异常（RuntimeException）**。

其中，编译型异常适用于检查语法错误，运行时异常最常见的有 数组下标越界异常、算数异常等等……

**这里要强调的是，每个异常都是一个类，他们共同继承了顶级父类 *Throwable*。**

### JVM 默认处理异常的方式

如果出现异常，Java 虚拟机默认会打印在控制台上，停止程序。

打印我们看到的红色信息，我们通常可以通过这个信息定位到代码的BUG



### 手动处理异常

**try…catch** 处理异常

格式：

```java
try{
    //可能出现异常的代码
}catch(异常类名,变量名){
    //异常处理的代码
}
```

![image-20260217001759452](https://p.ipic.vip/fb8mgk.png)

**优势**：可以让程序接着往下走，而不是停止程序。

*注* ： **在 JDK 7之后，我们可以在一个catch 中捕获多个异常，中间用“  |   ”连接**

注意点

1.   ![image-20260217002229115](https://p.ipic.vip/jtalt8.png)
2.   如果 *try*语句中出现了问题，那么会直接跳转到 *catch*中的语句，不会再执行 *try*异常之后面的语句了。



### 异常的常见方法

在顶级父类 *Throwable*当中，有一个方法 *printStackTrace()*，代表用红色的字体打印异常信息，**但是它不会停止程序运行**



### 抛出异常

*   *throws* 写在方法定义处，表明声明一个异常，告诉调用者，使用这个方法可能会出现的异常信息。

    >   细节： 
    >
    >   *   如果是编译时异常，必须要写。
    >   *   如果是运行时异常，可以省略不写。
    >
    >   ​	
    >
    >   注意，如果我们想要抛出多个异常，每个异常之间用逗号隔开即可

*   *throw* 写在方法内，结束方法，手动抛出异常对象，方法下面的代码不会运行了。

    >    ![image-20260217005516192](https://p.ipic.vip/3aycdc.png)

    这里抛出异常之后就可以被上面的 *try catch* 语句捕捉到了



### 自定义异常

1.   定义异常类 —— 类名要见名知意
2.   写继承关系
     *   如果是运行时异常就继承 *RuntimeException*
     *   如果是编译时异常就继承 *Exception*，核心提醒程序员检查本地信息
3.   空参构造
4.   带参构造 —— 就是为了让控制台的报错信息更加见名知意





## File

![image-20260224151243082](https://p.ipic.vip/k23fle.png)



![image-20260224151627432](https://p.ipic.vip/r18ocj.png)



![image-20260224153507672](https://p.ipic.vip/u9r79u.png)

![image-20260224153800519](https://p.ipic.vip/5r49ij.png)

***注意***:关于 *delete*方法,如果删除的是文件夹,有两种情况：如果是空文件夹，直接删除；如果是有内容的文件夹，返回 *false*。

如果想删除有内容的文件夹，**写一个递归函数即可**。





![image-20260224154347709](https://p.ipic.vip/fyuyyo.png)



**作用：**获取改路径下文件夹的所有的内容，把所有的内容放入数组中返回（包含隐藏文件夹）

**细节：**

​		i.当调用只 *File* 的路径不存在的时候，返回 *null*
​		ii.当调用者*File* 的路径为一个文件的时候，返回 *null*
​		iii.当调用者 *File*的路径是一个空文件夹的时候，返回一个长度为 0 的数组
​		iv.当调用者 *File*的路径下有需要权限才能访问的文件时，不会遍历



*其余的了解即可*

![image-20260224154944408](https://p.ipic.vip/srdsks.png)





## IO 流

什么是 IO 流？

存储和读取数据的解决方案 —— *input & output*

这里的读和写是**以程序为主题去读取或写入硬盘的**



### 分类

#### 流的方向

1.   输入流 —— *input*
2.   输出流 —— *output*

#### 操作文件的类型

1.   字节流 —— 所有类型的文件都可以操作
2.   字符流 —— 只能操作纯文本文件 （*txt* 、 *markdown*）



### 字节流

#### 字节输出流 ——*OutputStream*

##### *FileOutputStream*

操作**本地文件**的字节输出流，将程序中的数据写到本地文件中

>   1.   创建字节输出流对象
>   2.   写数据
>   3.   **释放资源**

**书写细节**

1.   创建字节输出流对象
     
        >   细节 1：字符串表示路径或者 *File*对象
        >   细节 2：如果文件不存在会先创建一个文件，但是要保证父级路径是存在的
        >细节 3：如果文件已经存在，**会清空文件**
     
1.   写数据
     
     >   *write*方法的参数是整数，但是实际上是 ASCII 码转换过来的字节

写数据的三种方式

![image-20260224173359006](https://p.ipic.vip/sf5e3e.png)

我们可以使用 String 中的 *getBytes()* 方法快速将字符串转为 *bytes* 数组





**换行**： 

1.   *windows* –> *\r\n*
2.   Linux –> *\n*
3.   Mac –> *\r*



**续写**：

每次写入文件都会删除文件内容，如果我们不想让他删除，那么我们需要**打开续写开关**。

只需要在构造方法内最后一个参数传一个 *true*就行了，代表打开了续写开关。



#### 字节输入流 —— *InPutStream*

##### *FileInputStream*

**书写细节**：

1.   创建字节输入流对象 

     >    如果文件不存在，就直接报错

2.   写数据

     >   1.   一次读一个字节，读出来是 ASCII 对应的值
     >   2.   读到文件末尾后，返回-1

3.   释放资源

如果我们要循环读取，借用 while 循环即可

```java
FileInputStream fis = new FileInputStream("/Users/tuttokey/JavaStudy/day1/a.txt");
        int b;
        while((b = fis.read())!= -1){
            System.out.print((char)b);
        }

        fis.close();
```



#### 基本的文件拷贝

借用 *FileOutputStream*和 *FileInputStream*，我们可以实现一个小文件的的拷贝

```java
public class Main {
    public static void main(String[] args) throws IOException {
        FileInputStream fis = new FileInputStream("/Users/tuttokey/aaa/hska.doc");
        FileOutputStream fos = new FileOutputStream("/Users/tuttokey/JavaStudy/day1/copy.doc");
        long l = System.currentTimeMillis();
        int b;
        while((b = fis.read()) != -1){
            fos.write(b);
        }
        //规则：先创建后关
        fos.close();
        fis.close();
        System.out.println(System.currentTimeMillis() - l + "ms");
    }
}
```



##### **弊端**

由于每次一次只读写了一个字节，这样使得一旦文件一大拷贝会非常慢。

##### 解决方案

*FileInputStream*中提供了一个*read*的重载方法

![image-20260225213820714](https://p.ipic.vip/gfyeis.png)

传入的 *buffer*数组是用来存储读取到的字节文件，返回值是一个 *int*类型的整数，代表本次读取字节的长度，如果最后一次一个也没有读取到，返回-1

**注**：如果最后一次读取的长度小于我们开的*buffer*数组的长度，那么 *buffer* 数组未覆盖的地方保留的还是上一次读取的字节文件，我们可以用 `new String(buffer,0,len)`来消除影响



### 字符集

#### GBK

![image-20260225222027902](https://p.ipic.vip/nymwgk.png)

#### Unicode

最常用的 Unicode 编码方式是 utf - 8,在这种编码方式下，中文占 3 个字节并且以 1 二进制开头



#### Java 中默认编码、解码方式

![image-20260225222836973](https://p.ipic.vip/8qdtkj.png)

IDEA 编译器默认使用 UTF - 8 进行编码，但是 eclipse 默认使用 GBK 进行编码



### 字符流

字符流底层就是字节流，字符流实际上就是 字节流 + 字符集

解决了字节流一次只能读写一个字节导致读取中文的时候乱码的问题

#### 特点

*   输入流：一次读一个字节，遇到中文时，一次读多个字节。
*   输出流：底层把数组按照指定的编码方式进行编码，变成字节写入文件当中



#### 字符输入流 —— *Reader*

##### *FileReader*

#### 字符输出流 —— *Writer*

##### *FileWriter*

这两个的成员方法和构造方法和字节流类似。

**只需要注意的是** ： 字符输入流*Reader*方法传入数组时不再是 *bytes*类型数组而是 ***char*类型的数组**，相当于直接把二进制数进行强转，强转之后存入 *char*中



#### 练习

**文件夹复制**

重点关注这里如何 *dest* ？ 

```java
package com.tuttokey;
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException {
        long start = System.currentTimeMillis();
        copyDirs(new File("/Users/tuttokey/Downloads"),new File("/Users/tuttokey/JavaStudy/day1/copiedDirs"));
        long end = System.currentTimeMillis();
        System.out.println((end - start) + "ms");
    }
    public static void copyDirs(File src,File dest) throws IOException {
        dest.mkdirs();
        File[] files = src.listFiles();
        if (files != null) {
            for (File file : files) {
                if(file.isFile()){
                    FileInputStream fis = new FileInputStream(file);
                    FileOutputStream fos = new FileOutputStream(new File(dest,file.getName())); // 父级路径 + 子集路径
                    int len;
                    byte[] buffer = new byte[1024 * 1024 * 5];
                    while((len = fis.read(buffer)) != -1){
                        fos.write(buffer,0,len);
                    }
                    fos.close();
                    fis.close();
                }else{
                    copyDirs(file,new File(dest,file.getName()));
                }
            }
        }
    }
}

```





### 缓冲流

缓冲流分为两部分：

*   字节缓冲流 —— 包含字节缓冲输出流（*BufferedOutputStream*）、字节缓冲输入流（*BufferedInputStream*）
*   字符缓冲流 —— 包含字节缓冲输出流（*BufferedWrite*）、字节缓冲输入流（*BufferedRead*）

缓冲流的作用就是加快了文件读取的速度，**减少与硬盘/网络的交互次数**来极大地提高读写效率，尤其是对于字节流有很大的效率提升，但是对于字符没有显著提升，因为字符流本身底层就自带了缓冲区。



>   传统的 IO 流每读写一个字节，操作系统就要进行一次磁盘访问或网络传输，这在底层涉及系统调用，非常耗时。
>
>   -   **读取时：** 缓冲流一次性从源头读取一大块数据（默认 8KB）放入内存中的**缓冲区**。当你调用 `read()` 时，它是直接从内存拿数据，直到缓冲区空了，才会去读下一次硬盘。
>   -   **写入时：** 写入的数据先存放在内存缓冲区中，等缓冲区满了，或者手动调用了 `flush()`，才会一次性写出到目的地。

**缓冲区默认大小为** **8192**也就是 8kb



#### 字节缓冲流

**构造方法** ：

*   `public BufferedInputStream(InputStream is)`
*   `public BufferedInputStream(InputStream is,int size)`  （默认为 8kb，如果要手动定义 *size*可以传入到构造方法中）



*   `public BufferedOutputStream(OutputStream os)`
*   `public BufferedOutputStream(OutputStream os,int size)`  （默认为 8kb，如果要手动定义 *size*可以传入到构造方法中）

成员方法和原来的 *FileInputStream*以及 *FileOutputStream*相同

![image-20260226004142773](https://p.ipic.vip/cpa7jl.png)



#### 字符缓冲流

其他和字节缓冲流一致，但是值得注意的是，**字符缓冲流有两个特殊的好用的成员方法**：

*   字符缓冲输**入**流特有：`public String readLine()` —— 整行读取，没有数据可读了返回 *null*
*   字符缓冲输**出**流特有：`public void newLine()` —— 跨平台的换行 （自动识别Mac 、 Windows 、 Linux 操作系统添加换行）





### 转换流

**转换流实际上是字节流和字符流连接的桥梁。**下面这张图可以形象的解释：
![image-20260226204548766](https://p.ipic.vip/ptn38t.png)



#### 作用一

已经被淘汰了，我们只需要了解最新版本的用法即可。 

>   由于 IDEA 默认的字符编码是 UTF-8，现在我有一个 GBK 文件，那么我们如何读取这个文件中的内容呢？![image-20260226205235593](https://p.ipic.vip/qr3042.png)

#### 作用二 

>   考虑下面这个场景，这就是字节转换流最重要的方式。字节流使用字符缓冲流中的 *readLine()* 方法等等
>
>   ![image-20260226211010258](https://p.ipic.vip/t40sde.png)



### 对象操作流

#### 序列化流/对象操作输出流

作用就是把java 中的对象写入文件当中。

![image-20260226211453170](https://p.ipic.vip/tte42v.png)

![image-20260226211639488](https://p.ipic.vip/c2fits.png)

**注意**：实际上 *Serializable*接口是一个抽象接口，里面没有实现方法，这种接口叫做**标记性接口**，用于指示此类可以被**序列化**

#### 反序列化流/对象操作输入流

反序列化流就是对序列化流输入到程序当中的

![image-20260226211956291](https://p.ipic.vip/x2azy9.png)



#### 细节

1.   当序列化流读、写入数据的时候，实际上每个类都有一个版本号，JVM 是通过这个类的版本号来读、写数据的。
     如果我们修改了JavaBean 类，对应的版本号也会改变，这就会导致我们原来写入文件的数据与最新的版本号不匹配了，导致写入失败。
     为了解决这个问题，我们可以**自定义版本号**

     自定义版本号的语法：

     >   `private final static long serialVersionUID = 自定义版本号;`
     >
     >   请注意：这个版本号的名字只能是 ***serialVersionUID***，否则 JVM 不能分辨

2.   如果我们不想让 JavaBean 中某些成员变量被序列化，我们可以在这个成员变量的名称前加一个 *transient*关键字

3.   **一旦序列化之后我们不能再人为修改，不然我们就读不了了**

4.   注意：当我们用反序列化去读取对象的时候，如果我们不知道对象的数目，一旦我们将对象读完，如果还在读，**那么程序会抛出一个异常！**

     >   在实际开发中，我们通常规定将所有需要序列化的对象都放到一个ArrayLIst<?>当中，读取的时候我们也只读一个 ArrayList 再对其中的元素进行遍历即可。



### 打印流

**打印流只有输出流**，没有输入流！也就是不能读，只能写。

打印流最大的作用就是保证数据的原样写出，而不会根据 ASCII 码转

#### 字节打印流

![image-20260226220754809](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260226220754809.png)

字节打印流打印流底层没有缓冲流，第二个参数 *autoFlush*开不开都一样

![image-20260226220852464](https://p.ipic.vip/fwq7j4.png)

#### 字符打印流

![image-20260226222923059](https://p.ipic.vip/3b48zs.png)

注意：字节打印流和字符打印流的不同点就是字符流底层有缓冲区，所以如果想要自动刷新需要手动开启

![image-20260226223040921](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260226223040921.png)



### 解压缩流 / 压缩流

#### 解压缩流

解压缩流用于读取压缩包中的数据，是一个**输入流**，**注意压缩包中的数据必须以 *.zip* 结尾！**

对于*zip*中的每一个文件，实际上就是一个 *zipEntry*对象（不论是file 还是文件夹）

我们先要思考：解压的本质是什么？

>   就是把 zip 中的每一个*zipEntry*按层级结果拷贝到另一个文件夹中

当我们一直读取 *ZipInputStream* 后，当文件全部被读取完毕，返回一个 *null*的 *zipEntry*对象。

**注**：*getNextEntry*方法可以一直 *get*到最深层的文件夹，不用我们手动递归。

![image-20260226224419169](https://p.ipic.vip/8nwocf.png)



#### 压缩

压缩的本质就是把每个文件/文件夹放入 *zipEntry*对象中



##### 压缩单个文件

我们要遵从下面几个步骤：

1.   创建压缩流关联压缩包
2.   创建 ZipEntry 对象，表示在压缩包内的每一个文件和文件夹
3.   把 ZipEntry 对象那个放到当前压缩包当中
4.   把 src 文件中的数据写到压缩包当中

![image-20260227000457045](https://p.ipic.vip/m7dbc5.png)

##### 压缩文件夹

首先我们要知道一个细节：**ZipEntry** 构造方法内的 “pathname”内的路径同时也代表了了压缩包内文件的**相对路径**。

>   比如说我这有 `ZipEntry entry  = new ZipEntry(“bbb/ccc/a.txt”);` 也就代表了压缩包内*a.txt*包含在压缩包内的 aaa/bbb 多级文件夹下。

**强调**：ZipEntry 对象一定不能用绝对路径，而是要用相对于压缩包的路径！

重点关注 23 行代码和 33 行代码！考虑参数 name 的作用

```java
package com.tuttokey;
import java.io.*;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        File src = new File("/Users/tuttokey/aaa");
        File parent = src.getParentFile();
        File dest = new File(parent,"aaa.zip");
        ZipOutputStream zop = new ZipOutputStream(new FileOutputStream(dest));
        toZip(zop,src,src.getName());

    }
    public static void toZip(ZipOutputStream zop,File src,String name) throws IOException {
        File[] files = src.listFiles();
        if(files == null){
            return;
        }
        for (File file : files) {
            if(file.isFile()){
                ZipEntry entry = new ZipEntry(name + "/" + file.getName());
                zop.putNextEntry(entry);
                FileInputStream fis = new FileInputStream(file);
                byte[] bytes = new byte[1024];
                int len;
                while((len = fis.read(bytes))!=-1){
                    zop.write(bytes,0,len);
                }
                zop.closeEntry();
            }else{
                toZip(zop,file,name + "/" + file.getName());
            }
        }
    }

}
```



### Commons-io 工具包

Common-io 是由 *Apach*开源基金组织提供的一套有关 IO 操作的开源工具包

具体使用可以见这个文档 ->*/Users/tuttokey/JavaStudy/commons-io相关资料/commons-io整理的文档.md*

![image-20260227010054643](https://p.ipic.vip/4zgdsc.png)

![image-20260227010107223](https://p.ipic.vip/3g0s1h.png)



### Hutool 工具包

*   [Hutool 官网](https://hutool.cn/)
*   [中文使用文档](https://hutool.cn/docs/#/)
*   [API 帮助文档](https://plus.hutool.cn/apidocs/)

很常用的几个方法

![image-20260227012451349](https://p.ipic.vip/tlyb98.png)





### 算法设计——带有权重的随机算法

前缀和 + 二分

```java
package com.tokey.RandomNamePicker;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class test4 {
    public static void main(String[] args) throws IOException {
        File data = new File("./src/com/tokey/RandomNamePicker/student.txt");
        BufferedReader br = new BufferedReader(new FileReader(data));

        ArrayList<Student> list = new ArrayList<Student>();
        String line;

        while((line = br.readLine()) != null){
            String[] split = line.split("-");
            list.add(new Student(split[0],split[1],Integer.parseInt(split[2]),Double.parseDouble(split[3])));
        }

        br.close();

        //计算总权重 + 计算前缀和
        double[] prefix_sum = new double[list.size()];
        double weight_sum = 0.0;
        for (int i = 0; i < list.size(); i++) {
            weight_sum += list.get(i).getWeight();
            prefix_sum[i] = weight_sum;
        }

        double random = Math.random() * weight_sum;

        //二分查找 —— 如果不存在就返回 -（插入点）- 1
        int idx =  - Arrays.binarySearch(prefix_sum, random) - 1;
        Student stu = list.get(idx);

        //输出答案
        System.out.println(stu.getName());

        //修改权重
        stu.setWeight(stu.getWeight() / 2);

        //修改到文件当中
        BufferedWriter bw = new BufferedWriter(new FileWriter(data));
        for (Student student : list) {
            bw.write(student.toString());
            bw.newLine();
        }
        bw.close();

    }
}

```







### 配置文件

配置文件有两大好处：

*   可以把软件的设置永久化存储
*   如果我们修改参数，不需要手动修改代码，直接修改配置文件即可



##### Properties

![image-20260228174313708](https://p.ipic.vip/6hjrs6.png)

*   *Properties*没有泛型，建和值都以 *Object*对象存储 —— 但是我们通常存入字符串
*   ![image-20260228174506318](https://p.ipic.vip/qzz384.png)
*   ![image-20260228174536693](https://p.ipic.vip/fivbia.png)



配置文件的一个基本小应用

>    ![image-20260228175150559](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260228175150559.png)
>
>   ![image-20260228175217851](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260228175217851.png)





---



## 多线程



在书写多线程的时候，我们要严格遵守下面的几个步骤：

1.   循环
2.   同步代码块
3.   判断共享数据是否到了末尾（到了末尾）
4.   判断共享数据是都到了末尾（没到末尾，执行核心逻辑）



通俗的讲，多线程就是同时让程序同时做多件事。

*   并发：同一时刻，有多个指令在单个 CPU **交替**执行
*   并行：同一时刻，多个指令在多个 CPU 上同时执行

### 多线程的三种实现方式

#### 继承 *Thread* 类的方法

如果要通过继承 *Thread*类方法去实现多线程，具体步骤如下

*   先创建一个类 *MyThread*，继承 *Thread*，并且重写其中的 *Run*方法。
*   在所需要的程序中创建 *MyThread* 对象，并且调用 ***start()***方法，开启线程。

#### 实现 *Runnable* 接口的方式实现

![image-20260304012120158](https://p.ipic.vip/6lpm14.png)

#### 利用 *Callabe* 接口和 *Future* 接口实现

上面两种方法 run 的返回值都是 *void*，这第三种实现方式就是为了**获取多线程返回值的运行结果**。

![image-20260304014310277](https://p.ipic.vip/fuo3sv.png)

![image-20260304014239871](https://p.ipic.vip/h9h47h.png)



#### 三种方式的对比

![image-20260304014358163](https://p.ipic.vip/9ocipb.png)





### 多线程中常用的成员方法

![image-20260306144944874](https://p.ipic.vip/r2iwkh.png)



*   setPriority()

    >   线程优先级从 1～10 分别排布，默认为 5，优先级越高，线程抢占执行的机会越高。

*   setDaemon()

    >   守护线程，就是在其他非守护线程执行完毕之后，守护线程会陆续关闭。



### 线程的生命周期

![image-20260306151646930](https://p.ipic.vip/jfrrzr.png)



### 线程安全的问题

考虑下面这一个场景：

>   某电影院需要卖票，一共有 100 张票，开了三个窗口，请设计一个程序帮助电影院卖票
>
>   代码很简单：
>
>   >   ```java
>   >   package com.tokey.demo8;
>   >   
>   >   public class test1 {
>   >       public static void main(String[] args) {
>   >           MyThread my1 = new MyThread();
>   >           MyThread my2 = new MyThread();
>   >           MyThread my3 = new MyThread();
>   >   
>   >           Thread t1 = new Thread(my1);
>   >           Thread t2 = new Thread(my2);
>   >           Thread t3 = new Thread(my3);
>   >   
>   >   
>   >           t1.start();
>   >           t2.start();
>   >           t3.start();
>   >       }
>   >   }
>   >   ```
>   >
>   >   
>   >
>   >   ```java
>   >   package com.tokey.demo8;
>   >   
>   >   public class MyThread extends Thread {
>   >       static int count = 0;
>   >   
>   >   
>   >       @Override
>   >       public void run() {
>   >           while(true){
>   >               if(count < 100){
>   >                   count++;
>   >                   System.out.println("正在买第" + count + "张票");
>   >                   try {
>   >                       Thread.sleep(100);
>   >                   } catch (InterruptedException e) {
>   >                       throw new RuntimeException(e);
>   >                   }
>   >               }else{
>   >                   break;
>   >               }
>   >           }
>   >       }
>   >   }
>   >   ```
>
>   但是当我们实际允许的时候会发现，我们卖的票会存在“**卖重复**”甚至是“**卖超**”这两个问题



#### 同步代码块

为了防止出现上面的问题，我们需要把代码锁起来，也就是当某个线程进入之后，其他线程不能在进入了，只能等待这个线程执行完毕之后才能重新争执线程的使用权。—— 我们把这个方式叫做**同步代码块**

![image-20260306153654021](https://p.ipic.vip/luqyw0.png)



![image-20260306154016723](https://p.ipic.vip/48vn04.png)



切记 *Sychronized*锁对象一定要是唯一的 —— 上面的锁对象也就是 *oj*，否则没有意义，如果我们改为 *this*，就不行，一般我们会使用字节码对象，也就是 ***MyThread.class***对象，这个对象唯一的。





#### 同步方法

上面的是对某部分代码块进行了**上锁**，如果我们想直接对某个方法进行上锁，就要用到**同步方法**，这个方法的锁对象不需要人为指定

![image-20260306154430432](https://p.ipic.vip/ekua4l.png)





#### lock 锁

lock 实际上是一个借口，不被被实例化，我们实例化它实现类的对象 —— *ReentrantLock*

lock 锁的作用就是手动上锁、释放锁

![image-20260306161345427](https://p.ipic.vip/fzuo4w.png)



注意两个细节：

*   和 synchronized 锁一样，我们需要共享同一个锁对象，也就是说要买我们用 Runnable 接口实现，要么我们**继承 *Thread*使用 static 关键字修饰 *Lock*对象**
*   注意，我们一定要在最后释放锁对象，否则程序会一直执行，这里用 finall 关键字最为稳妥，因为无论是什么情况下，*finall*中的内容一定会被执行



#### ==特别注意==

在写两个锁的时候，千万不能让两个锁嵌套起来，否则会形成**死锁**，导致程序停摆！！！



### 生产者和消费者（等待唤醒机制）

等待唤醒机智是多线程协作中最经典的一个机制

如果我们抽象成一个图片，我们可以如下

![image-20260306165202758](https://p.ipic.vip/y2nju6.png)





#### 常见方法

![image-20260306165255810](https://p.ipic.vip/oj6b8w.png)





#### 基本写法具体步骤如下：

>   1.   创建三个类 —— 消费者、生产者、共享数据
>   2.   ![image-20260306172243261](https://p.ipic.vip/4tdhi8.png)
>   3.   ![image-20260306172259925](https://p.ipic.vip/z0ezm6.png)
>   4.   ![image-20260306172314115](https://p.ipic.vip/9yefco.png)





#### 阻塞队列实现

利用数据结构**队列**，我们可以进行抽象为如下方法对等待唤醒机制进行实现：

>   1.   put 数据：放不进去，会等着，也叫做阻塞
>   2.   take 数据：取出队首数据，取不到也会等着，也叫阻塞

![image-20260306173004615](https://p.ipic.vip/s3m5u1.png)

**注意：生产者和消费者必须使用同一个阻塞队列** 

⚠️ ： 阻塞队列中内部的 put 和 take 方法已经封装了锁，不需要我们手动再 *synchronized*了

流程如下：

>   1.   ![image-20260306174746806](https://p.ipic.vip/939lim.png)
>   2.   ![image-20260306174806887](https://p.ipic.vip/y8cf3d.png)
>   3.   ![image-20260306174838786](https://p.ipic.vip/mfj0i0.png)



### 多线程的 6 个状态

![image-20260306182431580](https://p.ipic.vip/jo7iuf.png)





### 线程池

以前写的多线程代码有一个弊端：每次用到线程的时候就创建，不需要线程的时候就删掉，这很浪费资源。

我们可以利用一个容器存放线程。

![image-20260306204728259](https://p.ipic.vip/m7fg5v.png)

#### JUC 封装的一个简单线程池如下

![image-20260306204844991](https://p.ipic.vip/1d8eqv.png)

#### 自定义线程池对象

![image-20260306213012722](https://p.ipic.vip/33dwfa.png)

关于拒绝策略，有下面这几种策略，最常用的是**策略一**

![image-20260306213237566](https://p.ipic.vip/ry2aoo.png)

#### **线程池的工作原理**

![image-20260306213536882](https://p.ipic.vip/2657sf.png)

#### 线程池具体构造方式

![image-20260306213621106](https://p.ipic.vip/4ptq3y.png)



```java
package com.tokey.ThreadPool;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class test1 {
    public static void main(String[] args) {
        ThreadPoolExecutor pool = new ThreadPoolExecutor(
                3,
                6,
                1L,
                TimeUnit.SECONDS,
            	Executors.defaultThreadFactory(),
                new ArrayBlockingQueue<>(3),
                new ThreadPoolExecutor.AbortPolicy()
        );

        for (int i = 0; i < 9; i++) {
            pool.submit(()-> System.out.println(Thread.currentThread().getName() + "-hello"));
        }
    }
}
```



如果我们把上面 for 循环中“9”改成“10”，线程池就爆炸，抛出异常处理。



## 网络编程

### 主流架构

*    BS 架构
    *   不需要客户端，只需要页面 + 服务端
    *   用户不需要下载，打开浏览器即可用
    *   如果应用过大，用户体验受影响
*   CS 架构
    *   图片精美，用户体验好
    *   需要开发客户端，也许开发服务端
    *   用户需要下载和更新的时候太麻烦

### 网络编程三要素

*   IP
    *   设备在网络中的地址，是唯一的标识
*   端口号
    *   应用程序在设备中的唯一的标识
*   协议
    *   数据在网络中的传输规则，常见的协议有 UDP、TCP、http、https、ftp 等



### IP

常见的 IP 有 IPv4、IPv6

*   IPv4

​	采用32 位地址长度，分为 4 组 —— 采用电费呢十进制

![image-20260301221431478](https://p.ipic.vip/nbydhi.png)



![image-20260301221524963](https://p.ipic.vip/ct6vtc.png)

*   IPv6

    采用128 位地址长度





![image-20260301222944729](https://p.ipic.vip/u6axie.png)

注释：*InetAddress*这个类有两个子类，分别对于 ipv4和 ipv6，我们不能手动实例化这个类的对象，要通过他的静态方法`getByname`括号内填入 ip 地址或者主机名。



### 端口

![image-20260301223429575](https://p.ipic.vip/pwk4qp.png)



### 协议

![image-20260301223827668](https://p.ipic.vip/7wnzhe.png)

### UDP

![image-20260301223902730](https://p.ipic.vip/ppbdyk.png)

![image-20260301224120974](https://p.ipic.vip/41hdhk.png)







![image-20260301225258186](https://p.ipic.vip/rx0qz8.png)

![image-20260301225334208](https://p.ipic.vip/rzl9h6.png)





![image-20260303161610110](/Users/tuttokey/Library/Application Support/typora-user-images/image-20260303161610110.png)





### TCP

![image-20260303163520510](https://p.ipic.vip/5b6j39.png)

**注 **：为了确保客户端与服务端链接通畅，一定要先运行服务端，再运行客户端。





![image-20260303164106131](https://p.ipic.vip/qpln8w.png)

**注**：如果要穿中文，记得把右边的输入流改为转换流，否则这会乱码





![image-20260303164524365](https://p.ipic.vip/a76kgo.png)



### 三次握手

![image-20260303165602943](https://p.ipic.vip/b4xm93.png)





### 四次挥手

![image-20260303165643516](https://p.ipic.vip/2lbdfx.png)
