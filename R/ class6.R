data =  read.csv(file.choose())

m1 = lm(weight~diameter,data)
summary(m1)

m2 = lm(weight~fat,data)
summary(m2)
# h_0:β = 0
# h_a : β != 0
# p-value of x is equal to 1.52e-05 tiny,reject

# 将fat和diameter同时加入模型，构建多元线性回归
m3 = lm(weight~fat+diameter,data)
summary(m3)
#Multiple R-squared:  0.8035 < 0.9 这个模型不够准确

# p-value(fat) = 0.0653  > 1 - 0.95 fat is not useful
# p-value(diameter) = 5.31e-07  diameter is useful


# 构建线性回归前有一个很重要的条件，就是检查所有特征向量是否线性无关（特征值是否独立）
# R中可以使用两个方法检验独立:
cor.test(data[,2],data[,3]) 
# h_0: rho = 0 h_a:rho != 0
# p-value=8.091e-05

# 使用 car 包 ： 其中的vif方法也可以特征值的检验独立性
vif(m3) # 两个的vif值都小于 10，说明他们没有相关性

# 上面两个方法反映了两个不同的结果，但是只要这两种方法一种检验出了相关结果，这两个特征值就相关


# group test:group(fat and diameter) is useful
# H_0: β_fat = β_diameter = 0
# H_a: 两个 β 至少有一个不为零即可
# t_obs = 55.21 with p-value is tiny ，所以他们不为零，这个 group is useful,意味着至少一个变量是有用的

#  p-value(fat) = 0.0653  > 1 - 0.95 fat is not useful
# p-value(diameter) = 5.31e-07  diameter is useful
# 我们应该移除fat这个特征值


# 检验我们移除fat这个特征值是否正确
#H_0:removal was correct
#H_a:removal was incorrect
anova(m1,m3) # 检验删除是否成功
# p-value  0.06535 >  0.05 ,fail to reject null and we're saying removal of fat was correct
