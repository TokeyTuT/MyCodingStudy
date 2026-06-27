data = read.csv(file.choose())
colnames(data) = c("tar","nico","weight","mono")


m1 = lm(mono~tar+nico+weight,data)
# \hat y = 3.4137 + 0.9629*tar - 2.6067*nico - 0.3769*weight
summary(m1)
#Residual standard error: 1.445

# group test: # h_0 ：所有参数系数为 0  h_a：所有参数至少有一个不为零
# p-value = 1.323e-11 tiny  h_a

# p-value(tar) = 0.000689 < 0.05 so tar is useful
# p-value(nico) = 0.510820 > 0.05 so nico is not useful
# p-value(weight) = 0.923465 > 0.05 so weight is not useful as well

m2 = lm(mono~tar,data)
summary(m2)
#Residual standard error:/Users/tuttokey/Documents/我的编程史/R/cigar 分析.R 1.397
# m2的Residual standard error比m1低，m2比m1更出色


anova(m2,m1)
# h_0:removal is correct
# h_a:removal is not correct
# 移除两个特征值后，p-value =  0.7904 huge.so removal is correct

# 所有特征向量有什么线性关系吗?
# h_0 :rho = 1 h_a:rho != 0
cor.test(data$nico,data$tar) # p-value < 2.2e-16
cor.test(data$weight,data$tar) # p-value = 0.01416
cor.test(data$weight,data$nico) # p-value = 0.01236
#从上面的 correlated 假设验证，这些变量都有相关性

vif(m1)
# 至少有个vif > 10,它的的结果也展现了相关性





