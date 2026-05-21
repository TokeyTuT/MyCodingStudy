price = c(1.99,2.99,3,6,7,5)

mean(price) 
sd =(price)


# 90% confidence interval of price
t.test(price,conf.level=0.9)
# CI is (2.709303,5.950697)

# test H_a:mu > 3.5 provide p-value:
t.test(price,mu=3.5,alternative="greater")


# test H_a mu < 6 provide p-value
t.test(price,mu=6,alternative="less")

# answer the new H_a : mu < 3.5
t.test(price,mu = 3.5,alternative="less")
# p-value = 0.8253 

# conf.level = 90%
data = c(3,4,3,3,5,6)

t.test(data,conf.level=0.9) # (2.959433 5.040567)
t.test(data,mu=5,alternartive="greater") 
# p-value = 0.1106  
# alternative hypothesis: true mean is not equal to 5


