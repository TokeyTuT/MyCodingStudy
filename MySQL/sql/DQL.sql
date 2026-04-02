CREATE DATABASE DQL;
USE DQL;

# 1. 创建商品表.
create table product
(
    pid         int primary key auto_increment, # 商品id, 主键
    pname       varchar(20),    # 商品名
    price       double,         # 商品单价
    category_id varchar(32)     # 商品的分类id
);

show tables;

# 2. 添加表数据.
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'联想',5000,'c001');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'海尔',3000,'c001');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'雷神',5000,'c001');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'杰克琼斯',800,'c002');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'真维斯',200, null);
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'花花公子',440,'c002');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'劲霸',2000,'c002');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'香奈儿',800,'c003');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'相宜本草',200, null);
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'面霸',5,'c003');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'好想你枣',56,'c004');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'香飘飘奶茶',1,'c005');
INSERT INTO product(pid,pname,price,category_id) VALUES(null,'海澜之家',1,'c002');



select pid,pname,price,category_id from product;
select pname,category_id from product;

select
    pname as 名称,
    price as 价格
from
    product;


select
    category_id as 商品类别, -- 最左边的列抬头
    count(pid) as 类别个数  -- 聚合函数
from product
group by category_id -- 按照 category_id 分组
having
    类别个数 > 2;  -- 组后筛选


select
    distinct category_id,price
from product;


select *
from product limit 0,3;
select *
from product limit 3,3;


# 外键约束
CREATE TABLE IF NOT EXISTS cl(
    cid INT PRIMARY KEY AUTO_INCREMENT,
    num INT
);

DROP TABLE cl;

CREATE TABLE IF NOT EXISTS students(
    sid INT PRIMARY KEY AUTO_INCREMENT,
    sname VARCHAR(10) CHARSET utf8,
    c_id INT,
    CONSTRAINT fk_class_stu foreign key (c_id) references cl(cid)
);


INSERT INTO cl VALUES(null,1);
INSERT INTO cl VALUES(null,2);
INSERT INTO cl VALUES(null,3);

INSERT INTO students VALUES(null,'张三',2);
INSERT INTO students VALUES(null,'tut',3);
INSERT INTO students VALUES(null,'tokey',2);
INSERT INTO students VALUES(null,'isson',1);
INSERT INTO students VALUES(null,'isson',1);