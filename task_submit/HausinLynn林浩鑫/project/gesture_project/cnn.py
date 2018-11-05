#!/usr/bin/env python3

"""
	file: cnn.py
	brief: functions to build up CNN

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 11/01/2018

	Change History
	<Date>     | <Version> | <Author>
	11/01/2018 | 1.0.0.1   | HausinLynn    
"""

import tensorflow as tf 


def get_weight(shape):
	"""get a weight value with a designated shape

	the weight will be initialize as an array whose element
	follow the normal distribution with standard deviation
	of 0.1.

	Arg:
		shape: shape of weight

	Return:
		weight
	"""
	Weight_initial = tf.truncated_normal(shape, stddev=0.1)
	return tf.Variable(Weight_initial)

def get_bias(shape):
	"""get a bias value with a designated shape

	the bias will be initialize as an array whose element
	is all 0.

	Arg:
		shape: shape of bias

	Return:
		bias
	"""
	bias_initial = tf.zeros(shape) + 0.1
	return tf.Variable(bias_initial)

def conv2d(input_data, Weight):
	"""execute a convolution to input_data 

	input_data will be executed a convolution with Weight
	which decide on the size of kernel, channels number of
	input and output.

	Arg:
		input_data: input to be executed a convolution
		Weight: weight parameter of vonvolution

	Return:
		result after convolution
	"""
	conv_result = tf.nn.conv2d(input_data, Weight,
		strides=[1, 1, 1, 1], padding='SAME')
	return conv_result 

def max_pool_2x2(input_data):
	"""max pool input_data every 2x2 pixels

	Arg:
		input_data: input to be pooled

	Return:
		result after pool operation
	"""
	pool_result = tf.nn.max_pool(input_data, ksize=[1, 2, 2, 1],
		strides=[1, 2, 2, 1], padding='SAME')
	return pool_result

def Conv2d_and_MaxPool2x2(input_data, kernel_size, input_channels, output_channels):
	"""execute a convolution to input_data, then max pool it

	input_data will be executed a convolution according to kernel_size, 
	input_channels and output_channels, then will be max pooled every
	2x2 pixels.

	Arg:
		input_data: input to be executed a convolution and max pooled
		kernel_size: size of convolution kernel
		input_channels: channels number of input
		output_channels: channels number of output after convolution

	Return:
		result after convolution and max pool operation
	"""

	# get weight
	conv_weight = get_weight([kernel_size, kernel_size, input_channels, output_channels])
	# get bias
	conv_bias = get_bias([output_channels])
	# execute convolution
	conv_result = conv2d(input_data, conv_weight)
	conv_act = tf.nn.relu(tf.nn.bias_add(conv_result, conv_bias))
	# max pool every 2x2 pixels
	pool_result = max_pool_2x2(conv_act)
	return pool_result

def neural_layer(x_data, in_size, out_size, keep_prob=1, activation_function=None):
	"""build up one layer of neural networks

	Arg:
		x_data: input of this layer
		in_size: size of input in this layer
		out_size: size of output in this layer
		keep_prob: keep probability when dropout
		activation_function: activation function of this layer

	return:
		output of this neural layer
	"""

	# get weight
	Weight = get_weight([in_size, out_size])
	# get bias
	bias = get_bias([out_size])
	# w*x+b
	Wx_plus_b = tf.matmul(x_data, Weight) + bias

	# activation function
	if activation_function is None:
		output = Wx_plus_b
	else:
		output = activation_function(Wx_plus_b)

	# dropout
	output = tf.nn.dropout(output, keep_prob)
	return output