#!/usr/bin/env python3

"""
	file: gesture_train.py
	brief: train the CNN with gesture data

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.4
		date: 11/04/2018

	Change History
	<Date>     | <Version> | <Author>
	11/01/2018 | 1.0.0.1   | HausinLynn    
	11/02/2018 | 1.0.0.2   | HausinLynn
	11/03/2018 | 1.0.0.3   | HausinLynn
	11/04/2018 | 1.0.0.4   | HausinLynn
"""

import os
import numpy as np
import tensorflow as tf 
import cnn
import gesture_data


# convolution layer 1
CONV1 = {
	'kernel_size': 3,		# size of convolution kernel
	'input_channels': 1,    # channels number of input
	'output_channels': 32,  # channels number of output
}

# convolution layer 2
CONV2 = {
	'kernel_size': 3,		# size of convolutin kernel
	'input_channels': 32,	# channels number of input
	'output_channels': 64,	# channels number of output
}

#CONV3 = {
#	'kernel_size': 3,
#	'input_channels': 64,
#	'output_channels': 128,
#}

IMAGE_WIDTH = 200	# width of input image
IMAGE_HEIGHT = 200	# height of input image
IMAGE_CHANNELS = 1  # channels number of input image

HIDDEN_SIZE = 256	# size of hidden layer
OUTPUT_SIZE = 6		# size of output layer

BATCH_SIZE = 10		# size of a batch of data
STEPS = 10000		# train steps
LEARNING_RATE = 1e-4	# learning rate
#LEARNING_RATE_BASE = 0.5
#LEARNING_RATE_DECAY = 0.99

# path to save the model
MODEL_PATH = "./model/"	
MODEL_NAME = "gesture_model.ckpt"

def forward(input_data):
	"""forward process to input data

	the struct is following:
		conv1    [200, 200, 1]	->	[200, 200, 32]
		pool1    [200, 200, 32] ->  [100, 100, 32]
		conv2    [100, 100, 32] ->  [100, 100, 64]
		pool2    [100, 100, 64] ->  [50, 50, 64]
		dropout1 ...
		reshape  [50, 50, 64]   ->  [1, 50x50x64]
		hidden   [1, 50x50x64]  ->  [1, 256]
		output   [1, 256]       ->  [1, 6]

	Arg:
		input_data: input image data

	Return:
		output after a series of layers
	"""

	# convolution and pool frist time
	conv_and_pool1 = cnn.Conv2d_and_MaxPool2x2(input_data, CONV1['kernel_size'],
		CONV1['input_channels'], CONV1['output_channels'])
	# convolution and pool second time
	conv_and_pool2 = cnn.Conv2d_and_MaxPool2x2(conv_and_pool1, CONV2['kernel_size'],
		CONV2['input_channels'], CONV2['output_channels'])
	# dropout
	convout = tf.nn.dropout(conv_and_pool2, 0.5)

	#Weight2 = cnn.get_weight([CONV2['kernel_size'], CONV2['kernel_size'],
	#	 CONV2['input_channels'], CONV2['output_channels']])
	#convout2 = cnn.conv2d(convout1, Weight2)

	#conv3_and_pool = cnn.Conv2d_and_MaxPool2x2(convout2, CONV3['kernel_size'],
	#	 CONV3['input_channels'], CONV3['output_channels'])
	#conv_and_pool_2 = cnn.Conv2d_and_MaxPool2x2(conv_and_pool_1, CONV2['kernel_size'],
	#	 CONV2['input_channels'], CONV2['output_channels'])

	# convert each data to a 1xn array
	conv_shape = convout.get_shape().as_list()
	in_size = conv_shape[1] * conv_shape[2] * conv_shape[3]
	x_data = tf.reshape(convout, [conv_shape[0], in_size])

	# hidden layer
	hidden = cnn.neural_layer(x_data, in_size, HIDDEN_SIZE,
		keep_prob=0.5, activation_function=tf.nn.relu)
	# output layer
	output = cnn.neural_layer(hidden, HIDDEN_SIZE, OUTPUT_SIZE)

	return output 

def backward():
	"""feed back the loss between prediction and real, and
	adjust the parameter of neural networks

	Arg:
		None

	Return:
		None
	"""

	# placeholder of x data
	xs = tf.placeholder(tf.float32,
		[BATCH_SIZE, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS])
	# placeholder of y data
	ys = tf.placeholder(tf.float32, [None, OUTPUT_SIZE])
	# prediction
	prediction = forward(xs)

	# cross entropy cost
	cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(
		logits=prediction, labels=tf.argmax(ys, 1))
	cross_entropy_mean = tf.reduce_mean(cross_entropy)

	# step
	global_step = tf.Variable(0, trainable=False)
	#learning_rate = tf.train.exponential_decay(
	#	 LEARNING_RATE_BASE,
	#	 global_step,
	#	 600 / BATCH_SIZE,
	#	 LEARNING_RATE_DECAY,
	#	 staircase=True
	#)
	# AdamOptimizer
	optimizer = tf.train.AdamOptimizer(LEARNING_RATE)
	# train: minimize the cost
	train_step = optimizer.minimize(cross_entropy_mean, global_step=global_step)

	# saver to save the ckpt
	saver = tf.train.Saver()
	# dataset
	dataset = gesture_data.read_tfRecord()

	# session
	with tf.Session() as sess:
		# init variables
		init = tf.global_variables_initializer()
		sess.run(init)

		# get ckpt
		checkpoint = tf.train.get_checkpoint_state(MODEL_PATH)
		if checkpoint and checkpoint.model_checkpoint_path:
			saver.restore(sess, checkpoint.model_checkpoint_path)

		# train
		for i in range(STEPS):
			# get data
			x_data, y_data = gesture_data.data_batch(dataset, BATCH_SIZE)
			# run train step
			_, y, loss, step = sess.run([train_step, prediction, cross_entropy_mean, global_step],
				feed_dict={xs: x_data, ys: y_data})
			print("Step: %d, Loss: %g"%(step, loss))
			print(y)
			# save ckpt each 50 steps
			if i % 50 == 0:
				saver.save(sess, os.path.join(MODEL_PATH, MODEL_NAME), global_step=global_step)

if __name__ == '__main__':
	backward()