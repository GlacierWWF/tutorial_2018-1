"""@LibSVM_training docstring
    @file:      LibSVM_Training.py
    @brief:     Train svm model with MNIST
    @author:    atlanswer
    @date:      2018/11/10
    @version:   debug
"""
# preprocess MNIST database
import struct
# for timing
import time
# for image processing
import numpy as np
# import LibSVM
from sklearn import svm

TRAIN_SIZES = 60000
TEST_SIZES = 10000

def load_mnist():
    """load_mnist()
        convert MNIST data to ndarray format
    """
    mnist_data = []
    for feature_file, label_file, items in zip([r"MNIST\train-images.idx3-ubyte", r"MNIST\t10k-images.idx3-ubyte"],
                                               [r"MNIST\train-labels.idx1-ubyte", r"MNIST\t10k-labels.idx1-ubyte"],
                                               [TRAIN_SIZES, TEST_SIZES]):
        data_feature = open(feature_file, 'rb').read()
        data_label = open(label_file, 'rb').read()
        #mnist_format of struct unpack, > means big endian, iiii mean 4 integers
        mnist_format = '>iiii'
        offset = 0
        magic_number, feature_number, height, width = struct.unpack_from(mnist_format, data_feature, offset)
        #slide over the 2 numbers above
        offset += struct.calcsize(mnist_format)
        #28x28
        feature_size = height * width
        #B means unsigned char
        mnist_format = '>{}B'.format(feature_size)
        #because gemfield has insufficient memory resource
        if items > feature_number:
            items = feature_number
        images = np.empty((items, feature_size))
        for i in range(items):
            images[i] = np.array(struct.unpack_from(mnist_format, data_feature, offset))
            #0~255 to 0~1
            images[i] = images[i]/256
            offset += struct.calcsize(mnist_format)

        #mnist_format of struct unpack, > means big endian, i means integer, well, ii mean 2 integers
        mnist_format = '>ii'
        offset = 0
        magic_number, label_number = struct.unpack_from(mnist_format, data_label, offset)
        #slide over the 2 numbers above
        offset += struct.calcsize(mnist_format)
        #B means unsigned char
        mnist_format = '>B'
        #because gemfield has insufficient memory resource
        if items > label_number:
            items = label_number
        labels = np.empty(items)
        for i in range(items):
            labels[i] = struct.unpack_from(mnist_format, data_label, offset)[0]
            offset += struct.calcsize(mnist_format)
        
        mnist_data.append((images, labels.astype(int)))
    return mnist_data

def train_SVM():
    start_time = time.time()
    training_data, test_data = load_mnist()

    model = svm.SVC()
    model.fit(training_data[0], training_data[1])
    end_time = time.time()

    predictions = [int(item) for item in model.predict(test_data[0])]
    currect_items = sum(int(item == label) for item, label in zip(predictions, test_data[1]))

    print("SVM training takes %.4f s"%(end_time - start_time), end='')
    print(", with accuracy of", (currect_items / len(test_data[1])))

train_SVM()
