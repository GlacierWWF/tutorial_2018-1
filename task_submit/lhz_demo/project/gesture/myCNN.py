#!/usr/bin/env python2
# -*- -*coding: utf-8-s
#=================================================
# mnist_test.py                    
# @author    lhz_demo 
# @email     luhzh5@mail2.sysu.edu.cn 
# @version   2.2.7 
# @date      2018/11/11 

# Abustract: cnn of training network
#
#=================================================


import sys
#导入某个库时电脑报错，用以下解决，不影响内容的运行#
defaultencoding = 'utf-8'
if sys.getdefaultencoding() != defaultencoding:
    reload(sys)
    sys.setdefaultencoding(defaultencoding)
import os
import time
import numpy as np
import tensorflow as tf
from sklearn import model_selection, utils
from PIL import Image
import cv2
import matplotlib.pyplot as plt
import random
import json  # 保存文件
import sys


img_rows = 200
img_cols = 200
img_channels = 1
batch_size = 32
nb_classes = 5 # 测试类别


# 图像保存路径
path = "./"
path2 = "./train" # 训练的样本路径

# 输出
output = ["NOTHING", "OK", "YEAH", "PUNCH", "GIVE_ME_FIVE"]

#列出所以文件【图片】
def modlistdir(path):
    listing = os.listdir(path)
    retlist = []
    for name in listing:
        if name.startswith('.'):
            continue
        retlist.append(name)
    return retlist

#此函数将数据集分为train和test数据集来训练和测试
def Initializer():
    imlist = modlistdir(path2) 
    total_images = len(imlist) 

    immatrix = np.array([np.array(Image.open(path2+'/'+image).convert('L')).flatten() for image in imlist],
                        dtype='float32')
    print(immatrix.shape)  

    #
    label = np.ones((total_images, ), dtype=int) 
    samples_per_class = total_images / nb_classes 

    print("sample_per_class - ", samples_per_class)

    s = 0
    r = samples_per_class
    for classIndex in range(nb_classes):
        label[int(s):int(r)] = classIndex
        s = r
        r = s + samples_per_class

    data, Label = utils.shuffle(immatrix, label, random_state=2)
    X = data
    y = Label
    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0, random_state=4)

    X_train = X_train.reshape(X_train.shape[0], img_rows, img_cols, img_channels)
    X_test = X_test.reshape(X_test.shape[0], img_rows, img_cols, img_channels)
    X_train = X_train.astype("float32")
    X_test = X_test.astype("float32")

    X_train /= 255 # 黑白 0 1
    X_test /= 255

    return X_train, X_test, y_train, y_test


###开始搭建网络
INPUT_NODE = img_rows * img_cols
OUTPUT_NODE = 5

Image_size = 200
NUM_LABELS = 5


# 训练用参数
LEARNING_RATE_BASE = 0.8
LEARNING_RATE_DECAY = 0.99  # 权重衰减
REGULARIZATION_RATE = 0.0001
TRAINING_STEPS = 3000
MOVING_AAVERAGE_DECAY = 0.99
MODEL_SAVE_PATH = './model'
MODEL_NAME = 'model.ckpt'

def get_batch(X, y, batch_size):
    data = []
    label = []
    m = X.shape[0]
    for _ in range(batch_size):
        index = random.randrange(m)
        data.append(X[index])
        tmp = np.zeros(NUM_LABELS, dtype=np.float32)
        tmp[y[index]] = 1.0
        label.append(tmp)
    return np.array(data), np.array(label)

#=====================================================#
#	以下开始定义cnn网络的卷积层等各层的基本参数	#
#=======================================================#

# 第一层卷积层的尺寸和深度
CONV1_DEEP = 32
CONV1_SIZE= 5

# 第二层卷积层的尺寸和深度
CONV2_DEEP = 64
CONV2_SIZE= 3

# 第一层卷积层的尺寸和深度
CONV3_DEEP = 64
CONV3_SIZE= 5

# 第二层卷积层的尺寸和深度
CONV4_DEEP = 64
CONV4_SIZE= 5

FC_SIZE1 = 512
FC_SIZE2 = 128

def inference(input_tensor, train, regularizer):
    with tf.name_scope('layer1-conv1'):
        conv1_weights = tf.get_variable("weight", [CONV1_SIZE, CONV1_SIZE, img_channels, CONV1_DEEP],
                                        initializer=tf.truncated_normal_initializer(stddev=0.1))
        conv1_biases = tf.get_variable("bias", [CONV1_DEEP], initializer=tf.constant_initializer(0.0))
        conv1 = tf.nn.conv2d(input_tensor, conv1_weights, strides=[1, 1, 1, 1], padding="VALID")

        relu1 = tf.nn.relu(tf.nn.bias_add(conv1, conv1_biases))

    with tf.name_scope('layer2-pool1'):
        pool1 = tf.nn.max_pool(relu1, ksize=[1,2,2,1], strides=[1, 2, 2, 1], padding="SAME") 


    with tf.variable_scope('layer3-conv2'):
        conv2_weight = tf.get_variable("weight", [CONV2_SIZE, CONV2_SIZE, CONV1_DEEP, CONV2_DEEP],
                                       initializer=tf.truncated_normal_initializer(stddev=0.1))
        conv2_biases = tf.get_variable('bias', [CONV2_DEEP], initializer=tf.constant_initializer(0.0))

        conv2 = tf.nn.conv2d(pool1, conv2_weight, strides=[1,1,1,1], padding="VALID") 

        relu2 = tf.nn.relu(tf.nn.bias_add(conv2, conv2_biases))

    with tf.name_scope('layer4-pool2'):
        pool2 = tf.nn.max_pool(relu2, ksize=[1,2,2,1], strides=[1,2,2,1], padding="SAME") 

    with tf.variable_scope('layer5-conv3'):
        conv3_weight = tf.get_variable("weight", [CONV3_SIZE, CONV3_SIZE, CONV2_DEEP, CONV3_DEEP],
                                      initializer=tf.truncated_normal_initializer(stddev=0.1))
        conv3_biases = tf.get_variable('bias', [CONV3_DEEP], initializer=tf.constant_initializer(0.0))

        conv3 = tf.nn.conv2d(pool2, conv3_weight, strides=[1,1,1,1], padding="VALID") 

        relu3 = tf.nn.relu(tf.nn.bias_add(conv3, conv3_biases))

    with tf.name_scope('layer6-pool3'):
        pool3 = tf.nn.max_pool(relu3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding="SAME") 

    with tf.variable_scope('layer7-conv4'):
        conv4_weight = tf.get_variable("weight", [CONV4_SIZE, CONV4_SIZE, CONV3_DEEP, CONV4_DEEP],
                                       initializer=tf.truncated_normal_initializer(stddev=0.1))
        conv4_biases = tf.get_variable('bias', [CONV4_DEEP], initializer=tf.constant_initializer(0.0))

        conv4 = tf.nn.conv2d(pool3, conv4_weight, strides=[1, 1, 1, 1], padding="VALID")  
        relu4 = tf.nn.relu(tf.nn.bias_add(conv4, conv4_biases))

    with tf.name_scope('layer8-pool4'):
        pool4 = tf.nn.max_pool(relu4, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding="SAME")  

    pool_shape = pool4.get_shape().as_list()
    nodes = pool_shape[1] * pool_shape[2] * pool_shape[3]
    reshaped = tf.reshape(pool4, [pool_shape[0], nodes])

    with tf.variable_scope('layer9-fc1'):
        fc1_weights = tf.get_variable("weight", [nodes, FC_SIZE1],
                                      initializer=tf.truncated_normal_initializer(stddev=0.1))

        # 只有全连接层加入正则化
        if regularizer != None:
            tf.add_to_collection('loss', regularizer(fc1_weights))
        fc1_biases = tf.get_variable('bias', [FC_SIZE1], initializer=tf.constant_initializer(0.1))
        fc1 = tf.nn.relu(tf.matmul(reshaped, fc1_weights) + fc1_biases)
        if train:
            fc1 = tf.nn.dropout(fc1, 0.5)

    with tf.variable_scope('layer10-fc2'):
        fc2_weights = tf.get_variable("weight", [FC_SIZE1, FC_SIZE2],
                                      initializer=tf.truncated_normal_initializer(stddev=0.1))

        # 只有全连接层加入正则化
        if regularizer != None:
            tf.add_to_collection('loss', regularizer(fc2_weights))
        fc2_biases = tf.get_variable('bias', [FC_SIZE2], initializer=tf.constant_initializer(0.1))
        fc2 = tf.nn.relu(tf.matmul(fc1, fc2_weights) + fc2_biases)
        if train:
            fc2 = tf.nn.dropout(fc2, 0.5)

    with tf.variable_scope('layer11-fc3'):
        fc3_weights = tf.get_variable("weight", [FC_SIZE2, NUM_LABELS],
                                      initializer=tf.truncated_normal_initializer(stddev=0.1))

        # 只有全连接层加入正则化
        if regularizer != None:
            tf.add_to_collection('losses', regularizer(fc3_weights))
            print(regularizer(fc3_weights))
        fc3_biases = tf.get_variable('bias', [NUM_LABELS], initializer=tf.constant_initializer(0.1))
        logit = tf.matmul(fc2, fc3_weights) + fc3_biases

    return logit


def train(X_train, y_train):
    x = tf.placeholder(tf.float32, [None, img_rows, img_cols, img_channels], name='x-input')
    y = tf.placeholder(tf.float32, [None, OUTPUT_NODE], name='y-input')

    regularizer = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)

    y_ = inference(x, train=True, regularizer=regularizer) # 预测值
    global_step = tf.Variable(0, trainable=False) # 不可训练

    #计算交叉山和loss
    cross_entropy = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(labels=tf.arg_max(y, 1), logits=y_))
    loss = cross_entropy + tf.add_n(tf.get_collection('losses')) # 计算总loss

    train_step = tf.train.AdamOptimizer(0.0005).minimize(loss, global_step=global_step)
    # 保存模型
    saver = tf.train.Saver()
    with tf.Session() as sess:
        init = tf.global_variables_initializer()
        sess.run(init)

        for i in range(TRAINING_STEPS):
            xs, ys = get_batch(X_train, y_train, batch_size=batch_size)
            _, loss_value, step = sess.run([train_step, loss, global_step], feed_dict={x: xs, y: ys})
            print("----------------------", i, " : ", loss_value,  "-------------------------------")
            if step % 1000 == 0:
                print("After %d training step(s), loss on training batch is %g." % (step, loss_value))
                saver.save(sess, os.path.join(MODEL_SAVE_PATH, MODEL_NAME), global_step=global_step)

def test(X_test, y_test):
    with tf.Graph().as_default() as g:
        x = tf.placeholder(tf.float32, [None, img_rows, img_cols, img_channels], name='x-input')
        y = tf.placeholder(tf.float32, [None, OUTPUT_NODE], name='y-input')

        y_ = inference(x, train=None, regularizer=None)

        # 开始计算正确率
        correct_prediction = tf.equal(tf.arg_max(y, 1), tf.arg_max(y_, 1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

        # 加载模型
        saver = tf.train.Saver()
        with tf.Session() as sess:
            # tf.train.get_checkpoint_state会自动找到目录中的最新模型文件名
            ckpt = tf.train.get_checkpoint_state(MODEL_SAVE_PATH)
            if ckpt and ckpt.model_checkpoint_path:
                saver.restore(sess, ckpt.model_checkpoint_path)

                for _ in range(X_test.shape[0]):
                    xs, ys = get_batch(X_test, y_test, batch_size=1) # 测试batchsize = 1
                    label, accuracy_score = sess.run([y_, accuracy], feed_dict={x: xs, y: ys})
                    print("实际手势： %s，  预测手势： %s" % (output[np.argmax(ys)], output[np.argmax(label)]))
                    print("After %s training steps(s), test accuracy = %f" % (global_step, accuracy_score))

            else:
                print("No checkpoint, Training Firstly.")
                return
def Gussgesture(X_test):
    with tf.Graph().as_default() as g: 

        x = tf.placeholder(tf.float32, [None, img_rows, img_cols, img_channels], name='x-input')
        y_ = inference(x, train=None, regularizer=None) 
        # 加载模型
        saver = tf.train.Saver()
        with tf.Session() as sess:
            # tf.train.get_checkpoint_state会自动找到目录中的最新模型文件名
            ckpt = tf.train.get_checkpoint_state(MODEL_SAVE_PATH)
            if ckpt and ckpt.model_checkpoint_path:
                saver.restore(sess, ckpt.model_checkpoint_path)
                label = sess.run(y_, feed_dict={x: X_test.reshape(1, X_test.shape[0], X_test.shape[1], X_test.shape[2])})
                print("预测手势： %s" % (output[np.argmax(label)]))

                return output[np.argmax(label)]
            else:
                print("No checkpoint, Training Firstly.")
                return


def TRAIN():
    X_train, X_test, y_train, y_test = Initializer()
    train(X_train, y_train)
    test(X_test, y_test)

if __name__ == '__main__':
     TRAIN()

