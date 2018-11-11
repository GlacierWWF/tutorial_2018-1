## README

作者：张灏桓

修订：张灏桓

日期：2018-11-10

版本：1.0.0

系统：ubuntu 18.04

摘要：利用keras和LibSVM对MNIST数据集进行训练并测试



### 1 依赖库

- keras_mnist.py

keras

numpy 

- svm_mnist.py

pickle

gzip

numpy

sklearn.svm



### 2 运行方式

python3 keras_mnist.py

python3 svm_mnist.py

(由于 keras_mnist.py 在其他机器上需要联网下载数据，因此可能需在网络畅通的情况下运行，若失败需自行下载mnist。npz，并存放到~/.keras/datasets中)



### 3 结果展示

使用全连接神经网络的准确率为0.9673

使用svm的准确率为0.9172



![result2](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/1-1/result2.png)

![result1](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/1-1/result1.png)
