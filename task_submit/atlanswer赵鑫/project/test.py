'''
    Tensorflow test
'''
# For loading cifar-10 dataset from local hard drive only
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
import os
# from tensorflow.python.keras.datasets.cifar import load_batch
from tensorflow.python.keras import backend as K
# Import tensorflow and keras frameworks
from tensorflow import keras
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Activation, Dropout, Dense, Flatten
from tensorflow.keras.preprocessing.image import ImageDataGenerator
# Import cifar-10 dataset
# from tensorflow.keras.datasets import cifar10
# import time
import numpy as np
import matplotlib.pyplot as plt

BATCH_SIZE = 8
NUM_CLASSES = 10
EPOCHES = 5

def unpickle(file):
    """
    Unpickle data
    """
    import pickle
    with open(file, 'rb') as fo:
        dic = pickle.load(fo, encoding='bytes')
        d_decoded = {}
        for k, v in dic.items():
            d_decoded[k.decode('utf8')] = v
        dic = d_decoded
    data = dic['data']
    data = data.reshape(data.shape[0], 3, 32, 32)
    labels = dic['labels']
    return data, labels

def load_cifar10():
    """
    Load local cifar-10 dataset
    """
    path = r"task_submit\atlanswer赵鑫\project\cifar-10-batches-py"
    num_train_samples = 50000

    x_train = np.empty((num_train_samples, 3, 32, 32), dtype='uint8')
    y_train = np.empty((num_train_samples,), dtype='uint8')

    for i in range(1, 6):
        fpath = os.path.join(path, 'data_batch_' + str(i))
        (x_train[(i - 1) * 10000:i * 10000, :, :, :],
         y_train[(i - 1) * 10000:i * 10000]) = unpickle(fpath)

    fpath = os.path.join(path, 'test_batch')
    x_test, y_test = unpickle(fpath)

    y_train = np.reshape(y_train, (len(y_train), 1))
    y_test = np.reshape(y_test, (len(y_test), 1))

    if K.image_data_format() == 'channels_last':
        x_train = x_train.transpose(0, 2, 3, 1)
        x_test = x_test.transpose(0, 2, 3, 1)

    return (x_train, y_train), (x_test, y_test)

def load_model():
    """
    Load or train model
    """
    model_path = r"saved_model"
    model_name = r'saved_model.hd5'
    try:
        model = keras.models.load_model(os.path.join(model_path, model_name))
    except OSError:
        (train_features, train_labels), (test_features, test_labels) = load_cifar10()

        # Convert class vectors to binary class matrices.
        train_labels = keras.utils.to_categorical(train_labels, NUM_CLASSES)
        test_labels = keras.utils.to_categorical(test_labels, NUM_CLASSES)

        model = keras.models.Sequential()
        model.add(Conv2D(32, (3, 3), padding='same',
                                      input_shape=train_features.shape[1:]))
        model.add(Activation('relu'))
        model.add(Conv2D(32, (3, 3)))
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))
        model.add(Dropout(0.25))

        model.add(Conv2D(64, (3, 3), padding='same'))
        model.add(Activation('relu'))
        model.add(Conv2D(64, (3, 3)))
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))
        model.add(Dropout(0.25))

        model.add(Flatten())
        model.add(Dense(512))
        model.add(Activation('relu'))
        model.add(Dropout(0.5))
        model.add(Dense(NUM_CLASSES))
        model.add(Activation('softmax'))

        # Initiate RMSprop optimizer
        opt = keras.optimizers.RMSprop(lr=0.0001, decay=1e-6)

        # Train the model
        model.compile(loss='categorical_crossentropy', optimizer=opt,
                      metrics=['accuracy'])

        train_features = train_features.astype('float32')
        test_features = test_features.astype('float32')
        train_features /= 255
        test_features /= 255

        # This will do preprocessing and realtime data augmentation:
        datagen = ImageDataGenerator(
            featurewise_center=False,  # set input mean to 0 over the dataset
            samplewise_center=False,  # set each sample mean to 0
            featurewise_std_normalization=False,  # divide inputs by std of the dataset
            samplewise_std_normalization=False,  # divide each input by its std
            zca_whitening=False,  # apply ZCA whitening
            zca_epsilon=1e-06,  # epsilon for ZCA whitening
            rotation_range=0,  # randomly rotate images in the range (degrees, 0 to 180)
            # randomly shift images horizontally (fraction of total width)
            width_shift_range=0.1,
            # randomly shift images vertically (fraction of total height)
            height_shift_range=0.1,
            shear_range=0.,  # set range for random shear
            zoom_range=0.,  # set range for random zoom
            channel_shift_range=0.,  # set range for random channel shifts
            # set mode for filling points outside the input boundaries
            fill_mode='nearest',
            cval=0.,  # value used for fill_mode = "constant"
            horizontal_flip=True,  # randomly flip images
            vertical_flip=False,  # randomly flip images
            # set rescaling factor (applied before any other transformation)
            rescale=None,
            # set function that will be applied on each input
            preprocessing_function=None,
            # image data format, either "channels_first" or "channels_last"
            data_format=None,
            # fraction of images reserved for validation (strictly between 0 and 1)
            validation_split=0.0)

        # Compute quantities required for feature-wise normalization
        # (std, mean, and principal components if ZCA whitening is applied).
        datagen.fit(train_features)

        # Fit the model on the batches generated by datagen.flow().
        model.fit_generator(datagen.flow(train_features, train_labels,
                                        batch_size=BATCH_SIZE),
                            epochs=EPOCHES,
                            validation_data=(test_features, test_labels),
                            workers=4)

        # Save model
        model.save(os.path.join(model_path, model_name))
        print("Model saved.")

    else:
        print(model + "loaded.")

# def main():
    """
    Train CIFAR-10
    """
    class_names = ["airplane", "automobile", "bird", "cat", "deer",
                   "dog", "frog", "horse", "ship", "truck"]

    (train_features, train_labels) = load_cifar10()[0:2]

    # Print figure with 10 random images from each classes
    fig = plt.figure(figsize=(8, 3))
    for i in range(NUM_CLASSES):
        ax = fig.add_subplot(2, 5, 1 + i, xticks=[], yticks=[])
        idx = np.where(train_labels[:] == i)[0]
        features_idx = train_features[idx, ::]
        img_num = np.random.randint(features_idx.shape[0])
        im = features_idx[img_num, ::]
        ax.set_title(class_names[i])
        plt.imshow(im)
    plt.show()

load_model()
