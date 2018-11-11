#!/usr/bin/env python2
# -*- -*coding: utf-8-s
#=================================================
# mnist_test.py                    
# @author    lhz_demo 
# @email     luhzh5@mail2.sysu.edu.cn 
# @version   1.2.1 
# @date      2018/11/08 

# Abustract: Test the photo writed by myself
#
#=================================================

import numpy as np
from keras.models import load_model
import skimage.io
import matplotlib.pyplot as plt

#========================================#
#	导入想要预测的图片		#
#========================================#
img = skimage.io.imread('mnist_test_image/9.png',as_grey = True)
image =img

#==================================#
#	导入train号的模型	   #
#==================================#
model = load_model('mnist_model.h5')

img = np.reshape(img,(1,28,28,1)).astype('float32')
#==================================#
#	传入模型中返回预测结果	   #
#==================================#
predict = model.predict_classes(img)
print ('识别为：')
print (predict[0])
skimage.io.imshow(image)
plt.show()
