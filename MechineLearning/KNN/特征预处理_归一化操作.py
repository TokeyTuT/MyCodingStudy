# 导包
from sklearn.preprocessing import MinMaxScaler
# 准备数据
x_train = [[10,20],[20,30],[30,40]]
# 对元数据进行归一化操作
transfer = MinMaxScaler(feature_range=(3,5))
# 对元数据进行归一化操作
x_train = transfer.fit_transform(x_train)

print(x_train)