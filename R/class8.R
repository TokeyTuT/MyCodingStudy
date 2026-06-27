d1 = c(55,65,58,66,70)
d2 = c(60,63,58,65)
t.test(d1,d2,mu = 0,conf.level = 0.9)


data = read.csv(file.choose())
data
m1 = lm(y~x1+x2+x4,data)
summary(m1)
# Multiple R-squared:  0.8358 < 0,9 inadequate to predict y

# h_0: β_1 = β_2=β_4 =0
# h_a: not all are equal to 0
# p-value: 1.632e-06 tiny
# reject to null and conclude h_a,the group of these three are all useful

# use alpha = 0.001
# h_0: β=0  h_a : β!=0
# p-value=0.0443 > 0.001
# so remove x1
# x2 is same as x1 so remove x2




vif(m1) # all < 10 not correlated
