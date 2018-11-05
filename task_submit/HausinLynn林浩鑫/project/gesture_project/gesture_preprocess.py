#!/usr/bin/env python3

"""
    file: gesture_preprocess.py
    brief: preprocess the source image

    Details:
        author: HausinLynn
        email: linhx36@mail2.sysu.edu.cn
        version: 1.0.0.1
        date: 11/01/2018

    Change History
    <Date>     | <Version> | <Author>
    11/01/2018 | 1.0.0.1   | HausinLynn    
"""

import cv2
import numpy as np 


def skin_mask(img):
    """get the skin mask and sweep the background

    Arg:
        img: image to be processed

    Return:
        image after processing
    """

    # BGR to HSV
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # skin color range
    lower_skin = np.array([0, 50, 80])
    upper_skin = np.array([30, 200, 255])
    
    # apply skin color range
    mask = cv2.inRange(hsv, lower_skin, upper_skin)
    
    # open
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
    
    # blur
    mask = cv2.GaussianBlur(mask, (15, 15), 1)
    
    # mask background
    res = cv2.bitwise_and(img, img, mask=mask)
    # BGR to GRAY
    res = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
    
    return res

def binarize(img):
    """get the skin mask and sweep the background

    Arg:
        img: image to be processed

    Return:
        image after processing
    """

    block_size = 11
    binary = cv2.adaptiveThreshold(img, 255,
        cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, block_size, 2)
    _, res = cv2.threshold(binary, 70, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    return res