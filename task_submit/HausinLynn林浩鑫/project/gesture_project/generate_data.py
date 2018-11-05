#!/usr/bin/env python3

"""
    file: generate_data.py
    brief: generate gesture data(tfRecord)

    Details:
        author: HausinLynn
        email: linhx36@mail2.sysu.edu.cn
        version: 1.0.0.1
        date: 11/01/2018

    Change History
    <Date>     | <Version> | <Author>
    11/01/2018 | 1.0.0.1   | HausinLynn    
"""

import os 
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf


# image save path
IMAGE_PATH = './gesture_images/'

# classes
classes = ['yeah', 'OK', 'nice', 'love', 'contempt', 'right']

def generate_tfRecord():
	writer = tf.python_io.TFRecordWriter('./gesture_data/tfRecord_train')

	# get each class of images
	for index in range(len(classes)):
		# the class of images' save path
		class_path = IMAGE_PATH + classes[index] + '_images/'
		num = 0

		# write each image
		for img_name in os.listdir(class_path):
			img_path = class_path + img_name

			img = Image.open(img_path)
			#img = img.resize((100, 100), Image.ANTIALIAS)
			img_raw = img.tobytes()

			label = [0] * 6
			label[index] = 1

			# store as tfRecord
			example = tf.train.Example(features=tf.train.Features(feature={
				'img_raw': tf.train.Feature(bytes_list=tf.train.BytesList(value=[img_raw])),
				'label': tf.train.Feature(int64_list=tf.train.Int64List(value=label))
				}))
			writer.write(example.SerializeToString())

			# count
			num += 1
			print('Written %d %s pictures'%(num, classes[index]))

	writer.close()

if __name__ == '__main__':
	generate_tfRecord()