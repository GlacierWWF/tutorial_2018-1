#coding:utf-8
'''
Author:zhanghaohuan
Revised:zhanghaohuan
Date:2018_11_4
Version:v1.0.0
Abstract:Use the trained cnn model to judge the gesture taken by camera
         Under the condition of white background
'''



import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import time
from skimage import data_dir,io,transform,color
import numpy as np
import cv2
import threading
from time import sleep
from queue import Queue
import time


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
     
#convert the rgb image to a 28*28 gray image
def pre_deal(pic):
    gray=color.rgb2gray(pic)
    dst=transform.resize(gray,(28,28))
    one_dist_dst = np.reshape(dst, (1,-1))[0]
    return [one_dist_dst]




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

ans = tf.argmax(y_conv,1)
saver=tf.train.Saver(max_to_keep=3)
max_acc=0
is_train=False




que = Queue(maxsize=200)
exitq = Queue(maxsize=2)
capture = cv2.VideoCapture(0)


#take photo from the camera
def photograph(myque,exitq):
	time_start=time.time()
	while(True): 
		ret, frame = capture.read()
		cv2.imshow('frame', frame)
		time_end=time.time()
		if time_end-time_start>1:
			myque.put(frame)
			time_start = time_end
		if cv2.waitKey(1) == ord('q'):
			exitq.put(1)
			break

#judge the image by using it as the input of cnn
def test(myque,exitq):
	while(True): 
		model_file=tf.train.latest_checkpoint('ckpt/')
		saver.restore(sess,model_file)
		result = ans.eval(session = sess, feed_dict = {x:pre_deal(myque.get()), keep_prob:1.0})
		print(result)
		if exitq.qsize() > 0:
			break
		

tsk = []
thread = threading.Thread(target=photograph, args=(que,exitq))
thread.start()
tsk.append(thread)
thread = threading.Thread(target=test, args=(que,exitq))
thread.start()
tsk.append(thread)

for t in tsk:
    t.join()

sess.close()


