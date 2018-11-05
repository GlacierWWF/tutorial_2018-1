#!/usr/bin/env python3

"""
	file: mnist_train.py
	brief: train a mnist model

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
from keras import utils
from keras import models
from keras import layers
from keras import optimizers
from keras.datasets import mnist


# mnist data to be trained
(X_train, Y_train), _= mnist.load_data()
X_train = X_train.reshape(X_train.shape[0], -1) / 255
Y_train = utils.np_utils.to_categorical(Y_train, num_classes=10)

INPUT_SIZE = 784	# size of input
OUTPUT_SIZE = 10    # size of output
HIDDEN_SIZE = 500   # size of hidden neural layer

MODEL_FILE = 'model/mnist_model.h5'    # model save path


def train():
	"""train a mnist model.
	
	the model will be loaded if there is a model saved last time, else 
	a model will be created to train mnist. 
	"""

	# load or create model
	try:
		model = models.load_model(MODEL_FILE)
	except OSError:
		model = models.Sequential([
			layers.Dense(input_dim=INPUT_SIZE, units=HIDDEN_SIZE),	# first neural layer
			layers.Activation('relu'),
			layers.Dense(input_dim=HIDDEN_SIZE, units=OUTPUT_SIZE),	# last neural layer
			layers.Activation('softmax'),
		])

		# optimizer
		rmsprop = optimizers.RMSprop(lr=0.001, rho=0.9, epsilon=1e-8, decay=0.0)
		
		model.compile(
			optimizer=rmsprop,
			loss='categorical_crossentropy',	# cross entropy loss
			metrics=['accuracy']
		)
	else:
		print(MODEL_FILE, " is loaded.")

	print("Training ------------------------------------")
	# train 6 epochs with 100 batch each time
	start = time.time()
	model.fit(X_train, Y_train, epochs=6, batch_size=100)
	end = time.time()
	print("Using %.2f s"%(end-start))

	# save model
	model.save(MODEL_FILE)
	print()
	print("Created ", MODEL_FILE)

def main():
	"""
	main function
	"""
	train()

if __name__ == '__main__':
	main()