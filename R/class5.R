data1 = c(1,2,2,2,3,3,2)
dtat2 = c(2,2,3,3,2,1)


# Ha:mu1 - mu2 < 1

var.test(data1,data2) # 两个样本的方差齐性检验 F检验，用于检验两个方差是否相同

t.test(data1,data2,alternative = "less",mu=1,var.equal = TRUE,paired = FALSE)


# 加载数据，csv
data = read.csv(file.choose())
data
data[-1,2]
data[-1,3]
# Ha:rho > 0
cor.test(data[,1],data[,2],alternative = "greater")$p.value
# 0.9963821 

x.new = data[,1] ^ 2
x.new
cor.test(x.new,data[,2],alternative = "greater")


# regression
m1=lm(y~x,data)
m1$coef 

cor.test(data[,1],data[,2],alternative = "two.sided")$p.value


# Multiple R-squared:  0.9919  决定系数，这个参数非常重要，反映了回归模型的效果

# 下面的方法可以用来检验模型
fitted(m1) # 预测值
data[,2]-fitted(m1) # 误差 = 真实值-预测值
#或者直接调用
resid(m1)

# 看看y和x^2的是否存在线性关系
m2=lm(data[,2]~data[,1]^2,data)
summary(m2)
# m2有R^2，m2模型应该比m1更优秀

summary(m2)$sigma


# cookie
data2 = read.csv(file.choose())
cor.test(data2[,1],data2[,2])

cor.test(data2[,1],data2[,3])

model1 <- lm(data2[,1]~data2[,2],data2)#Multiple R-squared:  0.7767
summary(model1)
model2 <- lm(data2[,1]~data2[,3],data2)#Multiple R-squared:  0.4933
summary(model2)

# 显然模型1优于模型 2


