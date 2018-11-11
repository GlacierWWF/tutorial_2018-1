"""@CNN_for_gesture docstring
    @file:      CNN_for_gesture.py
    @brief:     train and load CNN model for gesture recognizing
    @author:    atlanswer
    @date:      2018/11/10
    @version:   debug
"""
import os
# import sequential model
from tensorflow.keras.models import Sequential
from tensorflow.keras import backend as K
# import CNN
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D, ZeroPadding2D
from tensorflow.keras.optimizers import SGD, RMSprop
# image precessing
import numpy as np
from PIL import Image
# training tools
from tensorflow.python.keras import utils
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split
import json
# video capture
import cv2
import matplotlib
# draw pictures
from matplotlib import pyplot as plt

# set gesture box size (pixels)
GST_SIZE = 200
# train setting
BATCH_SIZE = 4
EPOCHES = 5
NUM_CLASSES = 5

# Total number of convolutional filters to use
NUM_FILTERS = 32
# Max pooling
NUM_POOLING = 2
# Size of convolution kernel
CONV_SIZE = 3

# training data path
training_images_path = './training_images'

# weight files
WeightFileName = ["saved_model\gesture_model.hdf5"]

# outputs
output = ["OK", "NOTHING", "PEACE", "PUNCH", "STOP"]

JSONARRAY = {}

def update(plot):
    """update()
    """
    global JSONARRAY
    h = 450
    y = 30
    w = 45
    font = cv2.FONT_HERSHEY_SIMPLEX

    #plot = np.zeros((512,512,3), np.uint8)

    #array = {"OK": 65.79261422157288, "NOTHING": 0.7953541353344917, "PEACE": 5.33270463347435, "PUNCH": 0.038031660369597375, "STOP": 28.04129719734192}

    for items in JSONARRAY:
        mul = (JSONARRAY[items]) / 100
        #mul = random.randint(1,100) / 100
        cv2.line(plot, (0, y), (int(h * mul), y), (255, 0, 0), w)
        cv2.putText(plot, items, (0, y+5), font, 0.7, (0, 255, 0), 2, 1)
        y = y + w + 30

    return plot

# This function can be used for converting colored img to Grayscale img
# while copying images from path1 to path2
def convertToGrayImg(path1, path2):
    """convert
    """
    listing = os.listdir(path1)
    for file in listing:
        if file.startswith('.'):
            continue
        img = Image.open(path1 +'/' + file)
        grayimg = img.convert('L')
        grayimg.save(path2 + '/' +  file, "PNG")

def dir_list(path):
    """dir_list()
        return dir list
    """
    listing = os.listdir(path)
    retlist = []
    for name in listing:
        retlist.append(name)
    return retlist

# Load CNN model
def load_model(model_index):
    global MODEL_OUTPUT
    model = Sequential()

    model.add(Conv2D(NUM_FILTERS, (CONV_SIZE, CONV_SIZE),
                     padding='valid',
                     input_shape=(GST_SIZE, GST_SIZE, 1)))
    convout1 = Activation('relu')
    model.add(convout1)
    model.add(Conv2D(NUM_FILTERS, (CONV_SIZE, CONV_SIZE)))
    convout2 = Activation('relu')
    model.add(convout2)
    model.add(MaxPooling2D(pool_size=(NUM_POOLING, NUM_POOLING)))
    model.add(Dropout(0.5))

    model.add(Flatten())
    model.add(Dense(128))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(NUM_CLASSES))
    model.add(Activation('softmax'))

    model.compile(loss='categorical_crossentropy', optimizer='adadelta', metrics=['accuracy'])

    # Model summary
    model.summary()
    # Model conig details
    model.get_config()

    # pretrained model exists
    if model_index >= 0:
        #Load pretrained weights
        fname = WeightFileName[int(model_index)]
        print("loading ", fname)
        model.load_weights(fname)

    layer = model.layers[11]
    MODEL_OUTPUT = K.function([model.layers[0].input, K.learning_phase()], [layer.output,])

    return model

def guess_gesture(model, img):
    """guess_gesture()
        predict result
    """
    global output, MODEL_OUTPUT, JSONARRAY
    # load image
    image = np.array(img).flatten().reshape(GST_SIZE, GST_SIZE, 1)
    # normalize
    image = image.astype("float32")
    image /= 255
    # convert to cnn data
    img_data = image.reshape(1, GST_SIZE, GST_SIZE, 1)
    # get result
    prob_array = MODEL_OUTPUT([img_data, 0])[0]
    # print result
    d = {}
    i = 0
    for items in output:
        d[items] = prob_array[0][i] * 100
        i += 1
    # get the best guess
    import operator
    guess = max(d.items(), key=operator.itemgetter(1))[0]
    prob = d[guess]

    if prob > 60.0:
        JSONARRAY = d
        return output.index(guess)
    else:
        return 1

def prepare():
    """prepare()
        prepare training data
    """
    imlist = dir_list(training_images_path)
    sample_img = np.array(Image.open(training_images_path +'/' + imlist[0]))
    # get image size
    row, col = sample_img.shape[0:2]
    # get training image number
    num_img = len(imlist)

    # matrix that cover all the image
    img_matrix = np.array([np.array(Image.open(training_images_path+ '/' + images).convert('L')).flatten()
                           for images in sorted(imlist)], dtype='f')

    # set labels
    labels = np.ones((num_img,), dtype=int)

    samples_per_class = int(num_img / NUM_CLASSES)
    print("samples_per_class - ", samples_per_class)
    s = 0
    r = samples_per_class
    for class_index in range(NUM_CLASSES):
        labels[s:r] = class_index
        s = r
        r = s + samples_per_class

    '''
    # eg: For 301 img samples/gesture for 4 gesture types
    label[0:301]=0
    label[301:602]=1
    label[602:903]=2
    label[903:]=3
    '''
    data, Label = shuffle(img_matrix, labels, random_state=2)
    train_data = [data, Label]

    (X, y) = (train_data[0], train_data[1])
    # Split X and y into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=4)
    #
    X_train = X_train.reshape(X_train.shape[0], GST_SIZE, GST_SIZE, 1)
    X_test = X_test.reshape(X_test.shape[0], GST_SIZE, GST_SIZE, 1)
    # normalize data
    X_train = X_train.astype('float32')
    X_train /= 255
    X_test = X_test.astype('float32')
    X_test /= 255
    # convert class vectors to binary class matrices
    Y_train = utils.to_categorical(y_train, NUM_CLASSES)
    Y_test = utils.to_categorical(y_test, NUM_CLASSES)
    return X_train, X_test, Y_train, Y_test

def train_model(model):
    """train_model()
    """
    # Split X and y into training and testing sets
    X_train, X_test, Y_train, Y_test = prepare()
    # Now start the training of the loaded model
    hist = model.fit(X_train, Y_train, batch_size=BATCH_SIZE, epochs=EPOCHES,
                     verbose=1, validation_split=0.2)

    visualizeHis(hist)
    # save model
    model_name = "gesture_model.hdf5"
    model_path = "saved_model"
    model.save_weights(os.path.join(model_path, model_name), overwrite=True)

def visualizeHis(hist):
    # visualizing losses and accuracy

    train_loss = hist.history['loss']
    val_loss = hist.history['val_loss']
    train_acc = hist.history['acc']
    val_acc = hist.history['val_acc']
    xc = range(EPOCHES)

    plt.figure(1, figsize=(7,5))
    plt.plot(xc, train_loss)
    plt.plot(xc, val_loss)
    plt.xlabel('num of Epochs')
    plt.ylabel('loss')
    plt.title('train_loss vs val_loss')
    plt.grid(True)
    plt.legend(['train', 'val'])
    #print plt.style.available # use bmh, classic,ggplot for big pictures
    #plt.style.use(['classic'])

    plt.figure(2, figsize=(7, 5))
    plt.plot(xc, train_acc)
    plt.plot(xc, val_acc)
    plt.xlabel('num of Epochs')
    plt.ylabel('accuracy')
    plt.title('train_acc vs val_acc')
    plt.grid(True)
    plt.legend(['train', 'val'], loc=4)

    plt.show()
