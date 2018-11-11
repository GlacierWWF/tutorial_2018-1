## 技术报告

作者：张灏桓

修订：张灏桓

日期：2018-11-10

版本：1.0.0

系统：ubuntu 18.04

摘要：使用tensorflow构建cnn进行手势识别（0~6），训练集为自拍的600个手势图片，测试需在白色说背景下才能保证较高的准确率。



### 1 依赖库

tensorflow

time

scikit_image

numpy



### 2 运行方式

- 训练

python3 cnn_train.py

- 使用

python cnn_pro.py

（在图片界面上按q停止）



### 3 实现方法

​	这个项目的代码文件分为两部分，第一部分为 cnn_train.py，用于神经网络的训练。由于不是最初的训练版本，这个版本的 cnn_train.py  包含了以下两行代码：

```python
model_file=tf.train.latest_checkpoint('ckpt/')
saver.restore(sess,model_file)
```

​	这是读取了我先前训练出来的结果，latest 的版本是第848代（总代数为1000），其准确率在测试集上达到了75%。运行这个新版本（加载了75%准确率的网络模型）的结果1000代中，也并没有出现如此高的准确率了（可查看./ckpt/acc.txt），因此在后面的测试系统中使用了这一代的模型参数。

​	首先要对训练的数据进行预处理，这里使用 scikit_image 库对图像进行批量读取，并将得到的图片转成大小为28*28的灰度图。

​	接下来构建cnn网络模型，包括以下几层：

​	输入层，size 为 [, 28*28]；

​	第一层卷积层步长为1，核数为32，第一层池化层步长为2，核数为32；

​	第二层卷积层步长为1，核数为64，第一层池化层步长为2，核数为64；

​	全连接层，输入维度为7 * 7 * 64，输出维度为1024，激活函数为relu；

​	输出层，输入维度为1024，输出维度为6，激活函数为softmax。

​	损失函数为交叉熵，激活函数为AdamOptimizer，学习率为0.0001。

​	经过训练之后，这个保存下来的模型运用于  cnn_pro.py 文件中。这一部分主要内容为建立两个线程，第一个线程负责读取摄像头的数据，每隔1s将摄像头获取的图像数据传进消息队列中；第二个线程从消息队列里读取图片，并通过已加载的训练好的 cnn 进行判断，并输出判断结果到终端。



### 4 结果展示

​	由于训练集有限，以及我的笔记本用不了TensorFlow-GPU进行快速训练，所以训练的结果准确率并没有那么高。其中在干净背景（白色墙壁）的条件下，对手势 0，1，2，3，5 有较高的准确率，但无法识别手势4。大概的效果如下各图所示：

​	

![result1](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result1.png)

![result2](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result2.png)

![result3](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result3.png)

![result4](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result4.png)

![result5](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result5.png)

![result6](/home/zhh/桌面/tutorial_2018/task_submit/zhanghh_张灏桓/project/3/result6.png)