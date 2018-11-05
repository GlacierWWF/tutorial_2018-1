#!/usr/bin/env python3

"""
	file: gesture_data.py
	brief: get gesture data

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 11/01/2018

	Change History
	<Date>     | <Version> | <Author>
	11/01/2018 | 1.0.0.1   | HausinLynn    
"""

import numpy as np 
import tensorflow as tf


# data store path
DATA_PATH = './gesture_data/'

def _parse_data(example_proto):
	"""parse function which preprocess the data

	Arg:
		example_proto: serialized sample

	Return:
		image data and label data
	"""

	features = tf.parse_single_example(example_proto,
		features={
			'img_raw': tf.FixedLenFeature([], tf.string),
			'label': tf.FixedLenFeature([6], tf.int64)
		})

	# image
	img = tf.decode_raw(features['img_raw'], tf.uint8)
	img = tf.reshape(img, [200, 200, 1])
	img = tf.cast(img, tf.float32)

	# label
	label = tf.cast(features['label'], tf.float32)

	return img, label 

def read_tfRecord(isTrain=True):
	"""read tfRecord data

	Arg:
		isTrain: whether the data is gotten to be trained

	Return:
		tfRecord data after parsing and shuffling
	"""

	if isTrain:
		# train data is stored as tfRecord_train
		tfRecord_path = DATA_PATH + 'tfRecord_train'
	else:
		# test data is stored as tfRecord_test
		tfRecord_path = DATA_PATH + 'tfRecord_test'

	# read
	dataset = tf.data.TFRecordDataset(tfRecord_path)
	# parse
	dataset = dataset.map(_parse_data)
	# repeat
	dataset = dataset.repeat()

	# shuffle the data
	dataset = dataset.shuffle(buffer_size=10000)

	return dataset

def data_batch(dataset, batch_size):
	"""get a batch of data

	Arg:
		dataset: tfRecord data after parsing
		batch_size: the size of batch

	Return:
		img_batch: a batch of image data
		label_batch: a batch of label data
	"""

	# get a batch of data
	dataset = dataset.batch(batch_size)

	# iterator to get sample of data
	iterator = dataset.make_one_shot_iterator()
	# next
	data_batch = iterator.get_next()

	# Session
	sess = tf.InteractiveSession()
	image_batch, label_batch = sess.run(data_batch)
	sess.close()

	image_batch -= np.mean(image_batch)
	image_batch /= np.std(image_batch) 
	
	return image_batch, label_batch