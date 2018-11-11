#coding:utf-8
'''
Author:zhanghaohuan
Revised:zhanghaohuan
Date:2018_11_3
Version:v1.0.0
Abstract:train the cnn model, input = rbg gesture image, output = number 0~6
'''

import tensorflow as tf
import time
from skimage import data_dir,io,transform,color
import numpy as np



def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev = 0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape = shape)
    return tf.Variable(initial)


#read the rgb image, and convert it to a 28*28 gray image
def convert_gray(f):
    rgb=io.imread(f)   
    gray=color.rgb2gray(rgb) 
    dst=transform.resize(gray,(28,28))
    one_dist_dst = np.reshape(dst, (1,-1))[0]
    return one_dist_dst

#pre_deal the format of train_data
def generate_lab(word):
    res = np.zeros((len(word),6))
    for i in range(len(word)):
        res[i][int(word[i][0])] = 1
    return res
    
#read the train data and the test data, and generate the real label
str1='pic/*.jpg'
train_data = io.ImageCollection(str1,load_func=convert_gray)
str2='test_pic/*.jpg'
test_data = io.ImageCollection(str2,load_func=convert_gray)
temp = np.array([np.ones(100)*1,np.ones(100)*2,np.ones(100)*3,np.ones(100)*4,np.ones(100)*5,np.zeros(100)])
train_answer = np.reshape(temp, (-1,1))
test_answer = np.array([[0,1,0,1,2,2,3,3,4,4,5,5]]).transpose()
train_label = generate_lab(train_answer)
print(train_label)
test_label = generate_lab(test_answer)
print(train_data)










"""
卷积和池化，使用卷积步长为1（stride size）,0边距（padding size）
池化用简单传统的2x2大小的模板做max pooling
"""
def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding = 'SAME')
    # tf.nn.conv2d(input, filter, strides, padding, use_cudnn_on_gpu=None, data_format=None, name=None)
    # x(input)  : [batch, in_height, in_width, in_channels]
    # W(filter) : [filter_height, filter_width, in_channels, out_channels]
    # strides   : The stride of the sliding window for each dimension of input.
    #             For the most common case of the same horizontal and vertices strides, strides = [1, stride, stride, 1]

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize = [1, 2, 2, 1],
                          strides = [1, 2, 2, 1], padding = 'SAME')
    # tf.nn.max_pool(value, ksize, strides, padding, data_format='NHWC', name=None)
    # x(value)              : [batch, height, width, channels]
    # ksize(pool大小)        : A list of ints that has length >= 4. The size of the window for each dimension of the input tensor.
    # strides(pool滑动大小)   : A list of ints that has length >= 4. The stride of the sliding window for each dimension of the input tensor.






#define the stride size with 1, and the pool layer with size of 2*2
def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding = 'SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize = [1, 2, 2, 1], strides = [1, 2, 2, 1], padding = 'SAME')



#define the first Convolutional layer
x = tf.placeholder(tf.float32,[None, 784])
x_image = tf.reshape(x, [-1, 28, 28, 1])
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])

h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

#define the second Convolutional layer
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

#define the Connected Layer
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)

keep_prob = tf.placeholder("float")
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

#define the output layer
W_fc2 = weight_variable([1024, 6])
b_fc2 = bias_variable([6])

y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)



#define the loss function, optimizer and step
y_ = tf.placeholder("float", [None, 6])
cross_entropy = -tf.reduce_sum(y_ * tf.log(y_conv))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy) 


#cal the accuracy of output
correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction,"float"))

sess = tf.Session() 
sess.run(tf.initialize_all_variables())



saver=tf.train.Saver(max_to_keep=3)
max_acc=0
is_train=True



model_file=tf.train.latest_checkpoint('ckpt/')
saver.restore(sess,model_file)
f=open('ckpt/acc.txt','w')

for i in range(1000): #开始训练模型，循环训练5000次
    r = np.random.randint(1,550)
    batch_xs = train_data[r:r+50]
    batch_ys = train_label[r:r+50, :]
    if i % 1 == 0:
        train_accuracy = accuracy.eval(session = sess,
                                       feed_dict = {x:test_data, y_:test_label, keep_prob:1.0})
        print("step %d, train_accuracy %g" %(i, train_accuracy))
        f.write(str(i+1)+', val_acc: '+str(train_accuracy)+'\n')
        if train_accuracy>max_acc:
            max_acc=train_accuracy
            saver.save(sess,'ckpt/cnn.ckpt',global_step=i+1)
           
    train_step.run(session = sess, feed_dict = {x:batch_xs , y_:batch_ys ,
                   keep_prob:0.5}) #神经元输出保持不变的概率 keep_prob 为0.5

f.close()





sess.close()
