"""@SVM for MNIST
    @file:      _SVM.py
    @author:    floyed shen
    @date:      2018/11/10
    @version:   0.1.0
"""
import pandas as pd
from sklearn import svm
from sklearn.decomposition import PCA
import numpy as np
import time

img_rows, img_cols = 28, 28
path='data/mnist.npz'
f = np.load(path)
train_data, train_label = f['x_train'], f['y_train']
test_data, test_label = f['x_test'], f['y_test']
f.close()

    #train_data = train_data.reshape(train_data.shape[0], 1, img_rows, img_cols)
    #test_data = test_data.reshape(test_data.shape[0], 1, img_rows, img_cols)
    #input_shape = (1, img_rows, img_cols)
t1=np.zeros([60000,784])
t2=np.zeros([10000,784])
for i in range(1,60000):
    t1[i]=train_data[i].flatten()
for i in range(1,10000):
    t2[i]=test_data[i].flatten()
train_data=t1
test_data=t2
t = time.time()
#svm方法
pca = PCA(n_components = 0.8,whiten = True)
train_x = pca.fit_transform(train_data)
test_x = pca.transform(test_data)
svc = svm.SVC(kernel = 'rbf',C = 10)
svc.fit(train_x,train_label)
pre = svc.predict(test_x)
acc = float((pre==test_label).sum())/len(test_x)
print ('准确率：%f,花费时间：%.2fs' %(acc,time.time()-t))
