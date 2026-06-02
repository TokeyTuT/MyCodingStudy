data1=c(190,181,200)
data2=c(194,181,175)

avg1 = mean(data1)
avg2 = mean(data2)
n1 = length(data1)
n2 = length(data2)
v1 = var(data1)m1
v2 = var(data2)

spooled = sqrt(((n1-1)*v1 + (n2-1)*v2)/(n1 + n2 - 2))

t = ((avg1 - avg2) - 0) / spooled*sqrt(1/n1 + 1/n2)

pValue = pt(t,n1 + n2 - 2,lower.tail=FALSE)

# or User a function
t.test(data1,data2,mu=0,alternative = "greater") # order matters ——> mu1 - mu2 > mu0
# the order means mu(data1) - mu
# if t.test(data2,data1,mu=0,alternative = "greater"),it means mu2 - mu1 > mu0
t.test(data1,data2,mu=0,alternative = "greater",conf.level = 0.9)
t.test(data2,data1,mu=0,alternative = "less")


bg1=c(105,135,120,145)
bg2=c(134,110,100,144)

mean(bg1)
mean(bg2)

t.test(bg1)
t.test(bg2)

t.test(bg1,bg2,mu=0,conf.level = 0.95,alternative = "greater")# true difference in means is greater than 0
# so bg1 is stronger than bg2



data = c(120,130,324,314)
t.test(data,mu=0,conf.level=0.9)



# test
tire1=c(55,65,58,66,70)
tire2=c(60,63,58,65)

t.test(tire1,tire2,mu=0,conf.level = 0.95,alternative = "two.sided")
0.3472 * 2


mu1 = mean(tire1)
mu2 = mean(tire2)
mu = mu1 - mu2


