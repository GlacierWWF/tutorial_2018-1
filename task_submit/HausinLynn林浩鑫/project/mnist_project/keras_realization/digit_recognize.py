#!/usr/bin/env python3

"""
	file: digit_recognize.py
	brief: recognize the input handwritten digit

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 10/27/2018

	Change History
	<Date>     | <Version> | <Author>
	10/27/2018 | 1.0.0.1   | HausinLynn    
"""

import time
import numpy as np 
from PIL import Image
from keras import models
import matplotlib.pyplot as plt

MODEL_FILE = 'model/mnist_model.h5'    # model save path

def pre_process(source_img):
	"""preprocess the input image.

	the input image will be processed, and then the image can input
	to the trained mnist model.

	Arg:
		source_img: the image to be processed.

	Return:
		the image after preprocessing
	"""

	# resize the source_img as 28*28, 
	# because the image in mnist is 28*28
	resize_img = source_img.resize((28, 28), Image.ANTIALIAS)

	# gray
	img = np.array(resize_img.convert('L'))

	# binarize
	threshold = 50
	for row in range(28):
		for col in range(28):
			img[row][col] = 255 - img[row][col]
			if img[row][col] < threshold:
				img[row][col] = 0
			else:
				img[row][col] = 255

	# reshape the image as 1*784,
	# because the input data in mnist model is 1*784
	img_array = img.reshape([1, 784])

	# change type as float32
	img_array = img_array.astype(np.float32)
	# 0.0 and 255.0 to 0.0 and 1.0
	processed_img = np.multiply(img_array, 1.0/255.0)

	return processed_img

def digit_recognize(test_img):
	"""recognize the image after preprocessing

	the image can input to the model if it fit the requirement
	of the input data, and then can get the output.

	Arg:
		test_img: image to be recognized

	Return:
		the digit on the image, 0 to 9

	Raised:
		OSError: maybe the model is not found
	"""

	try:
		model = models.load_model(MODEL_FILE)
	except OSError:
		print(MODEL_FILE, "is not found.")
		return -1
	else:
		y_array = model.predict(test_img)	# prediction y
		result = np.argmax(y_array)			# result, 0 to 9
		return result

def test():
	"""test the accuracy of the model.
	
	get an input image, and recognize the image with the mnist model,
	then we can see the accuracy of the model.

	Raised:
		FileNotFoundError: maybe the image is not found.
	"""

	# get image path and name
	img_name = input("input the path of the image: ")

	try:
		source_img = Image.open(img_name)
	except FileNotFoundError:
		print(img_name, "is not found.")
	else:
		# show image
		plt.figure("digit")
		plt.imshow(source_img)
		plt.ion()
		plt.show()

		# preprocess
		print("Processing -------------------------------")
		processed_img = pre_process(source_img)

		# recognize
		print("Recognizing ------------------------------")
		digit = digit_recognize(processed_img)	# result
		if digit != -1:
			print("Recognize result:", digit)
		else:
			print("Recognize failed.")

		key = input("input q to exit")
		while key != 'q':
			key = input("input q to exit")

def main():
	"""
	main function
	"""
	test()

if __name__ == '__main__':
	main()