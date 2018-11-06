#!/usr/bin/env python3

"""
	file: gesture_test.py
	brief: test the CNN with gesture data

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 11/04/2018

	Change History
	<Date>     | <Version> | <Author>
	11/01/2018 | 1.0.0.1   | HausinLynn
"""

import numpy as np 
import tensorflow as tf 
import gesture_data
import gesture_train

# parameter of image
IMAGE_WIDTH = gesture_train.IMAGE_WIDTH
IMAGE_HEIGHT = gesture_train.IMAGE_HEIGHT
IMAGE_CHANNELS = gesture_train.IMAGE_CHANNELS

# parameter of neural networks
OUTPUT_SIZE = gesture_train.OUTPUT_SIZE
HIDDEN_SIZE = gesture_train.HIDDEN_SIZE

# model path
MODEL_PATH = gesture_train.MODEL_PATH

def test():
	"""using test data to test the CNN after training, 
	mainly accuracy.

	Arg:
		None

	Return:
		None
	"""

	# graph
	with tf.Graph().as_default() as graph:
		# placeholder
		xs = tf.placeholder(tf.float32, 
			[100, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS])
		ys = tf.placeholder(tf.float32, [100, OUTPUT_SIZE])

		# prediction
		prediction = gesture_train.forward(xs)
		correct_prediction = tf.equal(tf.argmax(prediction, 1), tf.argmax(ys, 1))
		# accuracy
		accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

		# saver
		saver = tf.train.Saver()
		# test data
		dataset = gesture_data.read_tfRecord(isTrain=False)

		# session
		with tf.Session() as sess:
			# ckpt
			checkpoint = tf.train.get_checkpoint_state(MODEL_PATH)
			if checkpoint and checkpoint.model_checkpoint_path:
				saver.restore(sess, checkpoint.model_checkpoint_path)
				global_step = checkpoint.model_checkpoint_path.split('/')[-1].split('-')[-1]

				# get test data
				x_data, y_data = gesture_data.data_batch(dataset, 100)
				# feed and run
				accuracy_value = sess.run(accuracy, feed_dict={xs: x_data, ys: y_data})
				print("Training Step: %s, Test Accuracy: %g" % (global_step, accuracy_value))
			else:
				print("No checkpoint file found.")
				return

if __name__ == '__main__':
	test()