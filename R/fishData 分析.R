data = read.csv(file.choose())
#a
m1 = lm(y~x1+x2+x4,data)
summary(m1)
# H_0: group is useful 
# H_a:group is not useful.
# p-value(group) = 1.632e-06 tiny


cor.test(data$x1,data$x2) # p-value = 6.374e-06
cor.test(data$x1,data$x4) # p-value = 0.4898
cor.test(data$x2,data$x4) # p-value = 0.6316

m2 = lm(y~x1,data)
summary(m2)

m3 = lm(y~x2,data)
summary(m3)

m4 = lm(y~x4,data)
summary(m4)

vif(m1)
