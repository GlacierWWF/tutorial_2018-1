#!/usr/bin/env python3

"""
    file: gesture_recognize.py
    brief: recognize the gesture image

    Details:
        author: HausinLynn
        email: linhx36@mail2.sysu.edu.cn
        version: 1.0.0.1
        date: 11/05/2018

    Change History
    <Date>     | <Version> | <Author>
    11/05/2018 | 1.0.0.1   | HausinLynn    
"""

import numpy as np 
import tensorflow as tf 
from PIL import Image
import gesture_preprocess
import gesture_train


# width of image
IMAGE_WIDTH = gesture_train.IMAGE_WIDTH
# height of image
IMAGE_HEIGHT = gesture_train.IMAGE_HEIGHT
# channels number of image
IMAGE_CHANNELS = gesture_train.IMAGE_CHANNELS

# model path
MODEL_PATH = gesture_train.MODEL_PATH

# classes of gesture
classes = ['yeah', 'OK', 'nice', 'love', 'contempt', 'right']


def pre_process(img):
	"""preprocess to the image

    Arg:
        img: image to be processed

    Return:
        image after processing
    """

    # skin_mask
	img = gesture_preprocess.skin_mask(img)
	# reshape to fit the input of the CNN
	img = img.reshape((1, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS))
	# type of float32
	img = img.astype(np.float32)

	# normalize
	img -= np.mean(img)
	img /= np.std(img)

	return img 

def recognize(img):
	"""recognize the image after processing

    Arg:
        img: image to be recognized

    Return:
        recognize result
    """

    # graph
	with tf.Graph().as_default() as graph:
		# placeholder of input
		x = tf.placeholder(tf.float32, 
			[1, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS])
		# prediction
		y = gesture_train.forward(x)
		index = tf.argmax(y, 1)

		# saver to get ckpt
		saver = tf.train.Saver()

		# session
		with tf.Session() as sess:
			# get ckpt
			checkpoint = tf.train.get_checkpoint_state(MODEL_PATH)
			if checkpoint and checkpoint.model_checkpoint_path:
				saver.restore(sess, checkpoint.model_checkpoint_path)

				index = sess.run(index, feed_dict={x: img})
				# result
				res = classes[index[0]]
				return res
			else:
				print("No checkpoint file found.")
				return -1