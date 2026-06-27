data = read.csv(file.choose())

m1 = lm(y~x1+x2+x3+x4,data)
summary(m1)
# Multiple R-squared:  0.5815 <  0.9 so is inadequate to predict y
# p-value: 8.195e-09 tiny so the group of four is useful

#h_0 : β2 = 0 ,h_a :β2 != 0
# p-value = 0.021146 > 0.01
# reject h_a remove x2

m2 = lm(y~x1+x3+x4,data)
summary(m2)

# h_0:removal was correct h_a:removal is incorrect
anova(m1,m2) # 0.02115  > 0.01 fail to reject null


cor(data$x1,data$x2)
vif(m1)

cor.test(data[,2],data[,3])$p.value




