#coding:utf8
from keras.models import Sequential  
from keras.layers import Input, Dense, Dropout, Activation
from keras.models import Model
from keras.optimizers import SGD
from keras.datasets import mnist
import numpy as np
 
tBatchSize = 128
#define 
model = Sequential()
 
#define the input layer with 784 nodes and the first hidden layyer with 512 nodes
#Activation function is tanh, 
model.add(Dense(512,input_shape=(784,)))
model.add(Activation('tanh'))
model.add(Dropout(0.5))
 
#define the second hidden layyer with 512 nodes, activation function is tanh
model.add(Dense(512))
model.add(Activation('tanh'))
model.add(Dropout(0.5))
 
#define the third hidden layyer with 512 nodes, activation function is tanh
model.add(Dense(512))
model.add(Activation('tanh'))
model.add(Dropout(0))
 
#define the output layyer with 10 nodes, activation function is softmax
model.add(Dense(10))
model.add(Activation('softmax')) 
 
#define Optimizer and compile
model.compile(loss='categorical_crossentropy', optimizer='rmsprop')
 



(X_train, y_train), (X_test, y_test) = mnist.load_data() 
 
# reshape input mnist data from 2-dim to 1-dim
X_train = X_train.reshape(X_train.shape[0], X_train.shape[1] * X_train.shape[2])
X_test = X_test.reshape(X_test.shape[0], X_test.shape[1] * X_test.shape[2])
Y_train = (np.arange(10) == y_train[:, None]).astype(int)
Y_test = (np.arange(10) == y_test[:, None]).astype(int)
model.fit(X_train, Y_train, batch_size=tBatchSize, epochs=60, shuffle=True, verbose=2, validation_split=0.3)

 
#judge the accuracy of result
result_max = np.argmax(model.predict(X_test,batch_size=tBatchSize,verbose=1), axis = 1)
result = np.equal(result_max, np.argmax(Y_test, axis = 1))

print("The accuracy of the model is %f" % (np.sum(result)/len(result))) 
 
 
