from sklearn.preprocessing import StandardScaler

x_train = [[10,20],[20,30],[30,40],[40,50]]

# 创建标准化化对象
transfer = StandardScaler()

# 对数据集进行标准化操作
x_train = transfer.fit_transform(x_train)

print(x_train)

print(transfer.mean_) # 平均值
print(transfer.var_) #  方差
print(transfer.scale_) # 标准差