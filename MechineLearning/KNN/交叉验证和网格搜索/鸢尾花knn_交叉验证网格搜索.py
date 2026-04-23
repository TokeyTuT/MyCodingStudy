from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split, GridSearchCV  # 网格搜索 + 交叉验证
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

iris_data = load_iris()
x_train,x_test,y_train,y_test = train_test_split(iris_data.data,iris_data.target,test_size=0.2)

# 特征标准化
sc = StandardScaler()
x_train = sc.fit_transform(x_train)
x_test = sc.transform(x_test)

# 模型的训练
# 创建 KNN 分类对象
estimator = KNeighborsClassifier()
# 定义字典记录超参数可能出现的值
param_dict = [{'n_neighbors':[i for i in range(1,11)]}]
# 交叉验证，网格搜索
estimator = GridSearchCV(estimator, # 模型对象
                         param_dict, # 超参数字典
                         cv=4) # 交叉验证折数

estimator.fit(x_train,y_train)
print(f"最优评分:{estimator.best_score_}")
print(f"最优超参组合:{estimator.best_params_}")
print(f"最优的估计器对象:{estimator.best_estimator_}")
print(f"具体的交叉验证结果:{estimator.cv_results_}")
