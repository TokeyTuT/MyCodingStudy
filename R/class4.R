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


