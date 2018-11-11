#!/usr/bin/env python2
# -*- -*coding: utf-8-s
#=================================================
# mnist_test.py                    
# @author    lhz_demo 
# @email     luhzh5@mail2.sysu.edu.cn 
# @version   1.1.7 
# @date      2018/11/08 

# Abustract: Training model and save model
#
#=================================================

import cv2
import numpy as np
from keras import backend as K
from keras.datasets import mnist
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.models import save_model, load_model

#=======================================#
#	 定义超参数：			#
#		batch的大小		#
#		分类的number		#
#		训练的次数		#
#=======================================#
batch_size = 128
nb_classes = 10 
nb_epoch = 12  

#==========================================#
#	定义网络的部分参数和图片参数	   #
#		图片的大小【像素】	   #
#		卷积filter的number	   #
#		卷积核，池化核的大小	   #
#==========================================#
img_rows, img_cols = 28, 28  
nb_filters = 32  
kernel_size = (3, 3) 
pool_size = (2, 2) 

# 加载数据
(X_train, y_train), (X_test, y_test) = mnist.load_data() 

if K.image_dim_ordering() == 'th':
    # 使用Theano的顺序：(conv_dim1,channels,conv_dim2,conv_dim3)
    X_train = X_train.reshape(X_train.shape[0], 1, img_rows, img_cols)
    X_test = X_test.reshape(X_test.shape[0], 1, img_rows, img_cols)
    input_shape = (1, img_rows, img_cols)
else:
    # 使用TensorFlow的顺序：(conv_dim1,conv_dim2,conv_dim3,channels)
    X_train = X_train.reshape(X_train.shape[0], img_rows, img_cols, 1)
    X_test = X_test.reshape(X_test.shape[0], img_rows, img_cols, 1)
    input_shape = (img_rows, img_cols, 1)

X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
# 都转化为小于1的数
X_train /= 255
X_test /= 255

# 将类向量转换为二进制类矩阵
Y_train = np_utils.to_categorical(y_train, nb_classes)
Y_test = np_utils.to_categorical(y_test, nb_classes)
print(y_train.shape)  # (60000,)
print(Y_train.shape)  # (60000, 10)

#==========================================#
#		 模型构建		   #
#   这里用2个卷积层、1个池化层、2个全连接层  #
#==========================================#
model = Sequential()
model.add(Convolution2D(nb_filters, kernel_size[0], kernel_size[1], border_mode='valid', input_shape=input_shape))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=pool_size))
model.add(Dropout(0.25))  # Dropout将在训练过程中每次更新参数时按一定概率（rate）随机断开输入神经元，Dropout层用于防止过拟合

model.add(Flatten())  # Flatten层用来将输入“压平”，即把多维的输入一维化，常用在从卷积层到全连接层的过渡
model.add(Dense(128))
model.add(Activation('relu'))
model.add(Dropout(0.5))
model.add(Dense(nb_classes))
model.add(Activation('softmax'))

# 模型编译
model.compile(loss='categorical_crossentropy', optimizer='adadelta', metrics=['accuracy'])

# 模型训练
model.fit(X_train, Y_train, batch_size=batch_size, nb_epoch=nb_epoch, verbose=1, validation_data=(X_test, Y_test))

# 模型评估或模型预测
score = model.evaluate(X_test, Y_test, verbose=0)
print('Test score:', score[0])  # 损失值  
print('Test accuracy:', score[1])  # 准确率  

# 保存模型，权重
fname = 'mnist_model.h5'
model.save(fname)
new_model = load_model(fname)
score = new_model.evaluate(X_test, Y_test, verbose=0)
print('Test score:', score[0])  # 损失值  
print('Test accuracy:', score[1])  # 准确率  

