#!/usr/bin/env python3

"""
	file: mnist_t.est
	brief: test the mnist model

	Details:
		author: HausinLynn
		email: linhx36@mail2.sysu.edu.cn
		version: 1.0.0.1
		date: 10/27/2018

	Change History
	<Date>     | <Version> | <Author>
	10/27/2018 | 1.0.0.1   | HausinLynn    
"""

from keras import utils
from keras import models
from keras.datasets import mnist

# mnist data to be tested
_, (X_test, Y_test) = mnist.load_data()
X_test = X_test.reshape(X_test.shape[0], -1) / 255
Y_test = utils.np_utils.to_categorical(Y_test, num_classes=10)

MODEL_FILE = 'model/mnist_model.h5'    # model save path

def test():
	"""test the mnist model.
	
	the model will be loaded if there is a model saved last time, and then
	tested with mnist test data.
	"""

	try:
		model = models.load_model(MODEL_FILE)
	except OSError:
		print(MODEL_FILE, " is not found.")
	else:
		print(MODEL_FILE, " is loaded.")

		# test
		print("\nTesting -----------------------------------------------")
		loss, accuracy = model.evaluate(X_test, Y_test)
		print()
		print("loss:", loss)	# loss
		print("acc:", accuracy) # accuracy   

def main():
	"""
	main function
	"""
	test()

if __name__ == '__main__':
	main()