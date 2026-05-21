a = 3
b = 100390^2

sqrt(a + b)

data = c(2,3,4)

mean(data)
var(data)  

hist(data)

data = matrix(c(1,2,3,4,5,6,7,8),2,4)



# lower.tail = TRUE 计算左尾面积，FALSE 计算右尾面积
pnorm(1.54,mean=0,sd=1,lower.tail=FALSE) # P(Z > 1.54)

# P(0 < Z < 1)
pnorm(1,mean=0,sd=1，lower.tail=TRUE) - pnorm(0,mean=0,sd=1,lower.tail=TRUE)
 
d1 = pnorm(c(0,1),mean=0,sd=1)
d1[2] - d1[1]
# P(1 < Z < 2.43)
d2 = pnorm(c(1,2.43),mean=0,sd=1)
d2[2] - d2[1]

# if P(Z < a) = 0.8790 find value of a
qnorm(0.8790,mean=0,sd=1,lower.tail=TRUE)


# if P(Z > a) = 0.3783
qnorm(0.3783,mean=0,sd=1,lower.tail=FALSE)

# P(a < Z < 1) = P(0 <  Z < 1) - P(a < Z) = 0.3333
d1 = pnorm(c(0,1),mean=0,sd=1)
tmp = d1[2] - d1[1] - 0.3333
qnorm(tmp,mean=0,sd=1,lower.tail=FALSE)

# X~N(mean=100,(sd=2)^2) find P(100 < Z < 105)

d3 = pnorm(c(100,105),mean=100,sd=2)
d3[2] - d3[1]


# R 的索引访问和切片和 Pandas 相同
data = matrix(c(1,2,3,4,5,6,7,8),4,2)
data[1,]
data[,1]
mean(data)

# P(102 < Z < 105)
d3 = pnorm(c(102,105),mean=100,sd=2)
d3[2] - d3[1]

# if P(X > a) = 0.3 mean = 100,sd = 2
qnorm(0.3,mean=100,sd=2,lower.tai=FALSE)


data2=c(0.9,0.85,1.05,1.1,1.2,1.05)
mean(data2)

mean(c(0.9,0.85,1.05,1.1,1.2,1.05))




# test1
data1 = c(3,2,2,6,7,6,5,8,7,7,5,6,7,3,3,2)
mean(data1)
var(data1)

# test2
pnorm(2.3,mean=0,sd=1,lower.tail=FALSE)
d = pnorm(c(-1,-0.5),mean=0,sd=1)
d[2] - d[1]

# test3
qnorm(0.2,mean=0,sd=1)

# test4
d = pnorm(c(5,15),mean=10,sd=3)
d[2] - d[1]

# test5
qnorm(0.3,mean=10,sd=3)






