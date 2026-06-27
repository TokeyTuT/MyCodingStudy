data = read.csv(file.choose())

m2 = lm.ridge(data[,4]~data[,1]+data[,2]+data[,3],lambda=0.5) # L2正则化,岭回归

m2$GCV # generalized cross validation 交叉验证


m3 = lm.ridge(data[,4]~data[,1]+data[,2]+data[,3],lambda=c(0.5,1))
m3$GCV
# seq(1,10,3) 这个方法用来构造等差数列


lambda1 = seq(0,1000,0.001)
m3 = lm.ridge(data[,4]~data[,1]+data[,2]+data[,3],lambda=lambda1)
m3$GCV

# 我们希望找出GCV最小的
lambda.opt = lambda1[which.min(m3$GCV)]
lambda.opt

# m5 是最优模型
m5 = lm.ridge(data[,4]~data[,1]+data[,2]+data[,3],lambda=lambda.opt)


