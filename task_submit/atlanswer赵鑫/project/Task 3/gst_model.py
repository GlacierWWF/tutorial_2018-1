"""@video_capture docstring
    @file:      video_capture.py
    @brief:     capture video and recognize the gestures
    @author:    atlanswer
    @date:      2018/11/14
    @version:   debug
"""
import os
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D, ZeroPadding2D
from tensorflow.keras.optimizers import SGD, RMSprop
from tensorflow.keras.utils import to_categorical
# from tensorflow.keras import backend as K
import numpy as np
from PIL import Image
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split

MODEL_PATH = r".\saved_model"
GST_PATH = r".\training_images"
NUM_PER_TYPE = 300
ROI_SIZE = 50
BATCH_SIZE = 32
NUM_CLASSES = 7
EPOCHS = 10
CLASSES = []

def load_data():
    gst_list = os.listdir(GST_PATH)
    img_mat = np.array([np.array(Image.open(GST_PATH + "\\" + images)).flatten()
                        for images in sorted(gst_list)], dtype="f")
    label = np.zeros((NUM_CLASSES * NUM_PER_TYPE,), dtype=int)

    cur_label = 0
    next_label = NUM_PER_TYPE
    for index in range(NUM_CLASSES):
        label[cur_label: next_label] = index
        cur_label = next_label
        next_label = cur_label + NUM_PER_TYPE

    feature, label = shuffle(img_mat, label, random_state=2)
    training_data = [feature, label]
    feature_train, feature_test, label_train, label_test = train_test_split(training_data[0], training_data[1], test_size=0.15, random_state=3)
    feature_train = feature_train.reshape(feature_train.shape[0], ROI_SIZE, ROI_SIZE, 1)
    feature_test = feature_test.reshape(feature_test.shape[0], ROI_SIZE, ROI_SIZE, 1)
    feature_train = feature_train.astype("float32") / 255
    feature_test = feature_test.astype("float32") / 255

    label_train = to_categorical(label_train, NUM_CLASSES)
    label_test = to_categorical(label_test, NUM_CLASSES)

    return feature_train, feature_test, label_train, label_test

def train_model():
    feature_train, feature_test, label_train, label_test = load_data()

    model = Sequential()
    model.add(Conv2D(16, kernel_size=(3, 3), activation="relu",
                     input_shape=(ROI_SIZE, ROI_SIZE, 1)))
    model.add(Conv2D(16, kernel_size=(3, 3), activation="relu"))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    # model.add(Dropout(0.25))
    model.add(Flatten())
    model.add(Dense(49, activation="relu"))
    model.add(Dense(NUM_CLASSES, activation="softmax"))

    model.compile(loss="categorical_crossentropy", optimizer="adadelta", metrics=["accuracy"])

    print(feature_train.shape)
    model.fit(feature_train, label_train,
              batch_size=BATCH_SIZE, epochs=EPOCHS, verbose=1,
              validation_split=0.15)

    model.save((MODEL_PATH + r"\gesture_model.hdf5"), overwrite=True)

def predict(img, model):
    img = np.array(img).flatten().reshape(ROI_SIZE, ROI_SIZE, 1).astype("float32") / 255
    feature = img.reshape(1, ROI_SIZE, ROI_SIZE, 1)

    result_array = model.predict(feature)
    result = np.argmax(result_array)

    return result
