"""@recognize docstring
    @file:      recognize.py
    @brief:     to recognize given handwriten digit image
    @author:    atlanswer
    @date:      2018/11/10
    @version:   debug
"""
# for image processing
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
# import keras model
from keras_training import load_model

def resize_img(img_src):
    """resize_img
        reshape the image to the format that can be accepted by model
    """
    img_src.load()
    img_rsz = np.asarray(img_src.convert("L"), dtype="float32").reshape(1, 28, 28, 1)
    img_dst = img_rsz.astype("float32") / 255
    return img_dst

def classcification():
    """classcification()
        classcify image
    """
    # prompt for image path
    img_path = input("Enter image path: ")
    # find image
    try:
        img_src = Image.open(img_path)
    except FileNotFoundError:
        print("Image ", img_path, "not found.")
    else:
        # pridict the result
        model = load_model()
        result_array = model.predict(resize_img(img_src))
        result = np.argmax(result_array)
        print("Result: ", result)
        
        plt.figure("Result: " + str(result))
        plt.imshow(img_src)
        plt.show()

classcification()
