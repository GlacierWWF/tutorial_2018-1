#!/usr/bin/env python3

"""
	file: mnist_classify.py
	brief: test of mnist classification
	with libsvm.

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 10/27/2018

	Change History
	<Date>     | <Version> | <Author>
	10/27/2018 | 1.0.0.1   | HausinLynn    
"""

from tensorflow.examples.tutorials.mnist import input_data
import numpy as np 
import svmutil
import time

def classify():
	"""classify mnist data with libsvm

	using libsvm to classify mnist data, time the process, 
	and test the training model at the last 
	"""

	# get mnist data
	mnist = input_data.read_data_sets("MNIST_data", one_hot=False)

	train_image = mnist.train.images  # image to be trained
	train_label = mnist.train.labels  # label to be trained

	test_image = mnist.test.images    # image to be tested
	test_label = mnist.test.labels    # label to be tested

	# get list
	X_train_data = train_image.tolist()
	Y_train_data = train_label.tolist()
	X_test_data = test_image.tolist()
	Y_test_data = test_label.tolist()

	# train with linear SVM
	print("Training -------------------------")
	start = time.time()
	model = svmutil.svm_train(Y_train_data, X_train_data, '-t 0')
	end = time.time()
	print("Using %.2f s"%(end-start))

	# test
	prediction, accuracy, _ = svmutil.svm_predict(
		Y_test_data, X_test_data, model)

	# to int
	prediction = [int(element)for element in prediction]

	#列表阵列
	prediction_array = np.asarray(prediction)
	reality_array = np.asarray(Y_test_data)

	# 准确性
	accuracy = np.mean(prediction_array == reality_array)
	print("accuracy:%0.4f."%accuracy)

def main():
	"""
	main function
	"""
	classify()

if __name__ == '__main__':
	main()