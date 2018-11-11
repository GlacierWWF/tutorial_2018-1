"""@mnist_training docstring
    @file:      mnist_training.py
    @brief:     training model for MNIST database
    @author:    atlanswer
    @date:      2018/11/10
    @version:   debug
"""
from __future__ import print_function
import os
# import keras
from tensorflow import keras
# import layers preset
from tensorflow.keras.layers import Dense, Dropout, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D
# for preprocessing data
from tensorflow.keras import backend
import numpy as np

# model setting
MODEL_DIC = "saved_model"
MODEL_NAME = "mnist_model.hdf5"
MODEL_PATH = os.path.join(MODEL_DIC, MODEL_NAME)

def load_model():
    """load_model()
        load model from local hard drive
    """
    # try to load model from local
    try:
        # there is an existing model
        model = keras.models.load_model(MODEL_PATH)
        print("Model loaded successfully.")
    except OSError:
        # train the model
        print("Prepare to train the model.")
        model = train_model()

    return model

def train_model():
    """train_model()
        train model for MNIST database
    """
    # load mnist database
    (train_features, train_labels), (test_features, test_labels) = keras.datasets.mnist.load_data()
    # training configuation
    batch_size = 12
    num_classes = 10
    epochs = 5
    # input image dimensions
    (img_rows, img_cols) = train_features.shape[1:3]

    # adjust the matrix structure if necessary
    if backend.image_data_format() == "channels_first":
        train_features = train_features.reshape(train_features.shape[0], 1, img_rows, img_cols)
        test_features = test_features.reshape(test_features.shape[0], 1, img_rows, img_cols)
        input_shape = (1, img_rows, img_cols)
    else:
        train_features = train_features.reshape(train_features.shape[0], img_rows, img_cols, 1)
        test_features = test_features.reshape(test_features.shape[0], img_rows, img_cols, 1)
        input_shape = (img_rows, img_cols, 1)

    # normalize the pixel to [0, 1]
    train_features = train_features.astype("float32")
    test_features = test_features.astype("float32")
    train_features /= 255
    test_features /= 255

    # convert class vectors to binary class matrices
    train_labels = keras.utils.to_categorical(train_labels, num_classes)
    test_labels = keras.utils.to_categorical(test_labels, num_classes)

    # create the cnn according to keras team
    model = keras.models.Sequential()
    model.add(Conv2D(4, kernel_size=(3, 3), activation='relu',
                     input_shape=input_shape))
    model.add(Conv2D(8, (3, 3), activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.5))
    model.add(Flatten())
    model.add(Dense(16, activation='relu'))
    model.add(Dropout(0.25))
    model.add(Dense(num_classes, activation='softmax'))

    # complie the model
    model.compile(loss=keras.losses.categorical_crossentropy,
                  optimizer=keras.optimizers.Adadelta(),
                  metrics=['accuracy'])

    # start training
    model.fit(train_features, train_labels,
              batch_size=batch_size,
              epochs=epochs,
              verbose=1,
              validation_data=(test_features, test_labels))

    # evaluate performance
    evaluate(model, test_features, test_labels)

    # save the model
    model.save(MODEL_PATH)
    return model

def evaluate(model, test_features, test_labels):
    """evaluate()
        evaluate the model's performance
    """
    score = model.evaluate(test_features, test_labels, verbose=0)
    print("Preformance:")
    print('Test loss:', score[0])
    print('Test accuracy:', score[1])
