"""@video_capture docstring
    @file:      video_capture.py
    @brief:     capture video and recognize the gestures
    @author:    atlanswer
    @date:      2018/11/14
    @version:   debug
"""
import os
import time
import cv2
import numpy as np
import send2trash
import gst_model
from tensorflow import keras

ROI_SIZE = 200
CAP_WIDTH = 640
CAP_HEIGHT = 360

MODEL_PATH = r".\saved_model"
GST_PATH = r".\training_images"
DO_SAVE = False
GST_TYPE = ""
GST_ORD = 1
NUM_TYPE = 1
BACKGROUND_SET = False
BACKGROUND = 0
PREDICT_STATE = False
GST_LIST = ["OK", "fist", "five", "nothing", "plan C", "scissor", "stop"]

def main():
    """
        main
    """
    global DO_SAVE, GST_TYPE, GST_ORD, NUM_TYPE, BACKGROUND_SET, PREDICT_STATE, model
    action = int(input("Action: 1 for capture gestures\n2 for train the model\n3 for predict gestures\nEnter: "))

    if action == 1:
        NUM_TYPE = 1
        # clear images
        send2trash.send2trash(GST_PATH)
        os.makedirs(GST_PATH)
        # zero for a single camera
        cap = cv2.VideoCapture(0)
        # resize video for love of the puny CPU
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, CAP_WIDTH)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, CAP_HEIGHT)

        print("Press b to set background.")
        print("Press s to record a new gesture.")
        print("6 different gestures including nothing:\nOK, fist, five, nothing, plan C, scissor, stop.\nPress Esc to exit.")
        cv2.namedWindow("Camera", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("ROI", cv2.WINDOW_AUTOSIZE)
        while True:
            retval, image = cap.read()
            image = cv2.resize(image, (CAP_WIDTH, CAP_HEIGHT))
            if retval == True:
                roi = subtract(image)

            cv2.imshow("Camera", image)
            cv2.imshow("ROI", roi)
            cv2.resizeWindow("ROI", 200, 200)

            keyboard = cv2.waitKey(5) & 0xff
            if keyboard == 27:
                break
            if keyboard == ord("b"):
                BACKGROUND_SET = True
            if keyboard == ord("s"):
                DO_SAVE = True
                GST_TYPE = str(input("Gesture " + str(GST_ORD) + "'s name: "))

        # exit
        cap.release()
        cv2.destroyAllWindows()
    elif action == 2:
        gst_model.train_model()
    elif action == 3:
        # load model
        try:
            saved_model = keras.models.load_model(MODEL_PATH + r"\gesture_model.hdf5")
            print("Model loaded")
        except OSError:
            print("Model not found")

        # zero for a single camera
        cap = cv2.VideoCapture(0)
        # resize video for love of the puny CPU
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, CAP_WIDTH)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, CAP_HEIGHT)
        cv2.namedWindow("Camera", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("ROI", cv2.WINDOW_AUTOSIZE)

        print("Press b to set background.")
        print("Press c to predict the gesture. Press Esc to exit.")
        while True:
            retval, image = cap.read()
            image = cv2.resize(image, (CAP_WIDTH, CAP_HEIGHT))
            if retval == True:
                roi = get_gesture(image, saved_model)

            cv2.imshow("Camera", image)
            cv2.imshow("ROI", roi)
            cv2.resizeWindow("ROI", 200, 200)

            keyboard = cv2.waitKey(5) & 0xff
            if keyboard == 27:
                break
            if keyboard == ord("b"):
                BACKGROUND_SET = True
            if keyboard == ord("c"):
                PREDICT_STATE = True
    
    print("Exiting...")

def subtract(img):
    """
        save ROI
    """
    global DO_SAVE, GST_TYPE, GST_ORD, NUM_TYPE, BACKGROUND, BACKGROUND_SET
    # draw ROI
    cv2.rectangle(img, (220, 80), (420, 280), (0, 255, 0), 2)
    roi = cv2.cvtColor(img[80:280, 220:420], cv2.COLOR_BGR2GRAY)
    roi = cv2.resize(roi, (50, 50))

    if BACKGROUND_SET == True:
        BACKGROUND = roi
        BACKGROUND_SET = False

    mask = cv2.absdiff(roi, BACKGROUND)
    mask = cv2.threshold(mask, 5, 255, cv2.THRESH_BINARY)[1]
    mask = cv2.GaussianBlur(mask, (3, 3), 3)
    mask = cv2.erode(mask, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3)), iterations=1)
    # mask = cv2.dilate(mask, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (2, 2)))
    roi = cv2.bitwise_and(roi, roi, mask=mask)

    if DO_SAVE == True and NUM_TYPE <= gst_model.NUM_PER_TYPE:
        cv2.imwrite((GST_PATH + "\\" + GST_TYPE + "_" + str(NUM_TYPE) + ".png"), roi)
        NUM_TYPE += 1
    elif NUM_TYPE > gst_model.NUM_PER_TYPE:
        DO_SAVE = False
        NUM_TYPE = 1
        print("Gesture " + str(GST_ORD) + " recorded.")
        GST_ORD += 1
    time.sleep(0.01)
    roi = cv2.resize(roi, (200, 200))
    return roi

def get_gesture(img, saved_model):
    """
        get gesture type
    """
    global NUM_TYPE, PREDICT_STATE, BACKGROUND, BACKGROUND_SET
    # draw ROI
    cv2.rectangle(img, (220, 80), (420, 280), (0, 255, 0), 2)
    roi = cv2.cvtColor(img[80:280, 220:420], cv2.COLOR_BGR2GRAY)
    roi = cv2.resize(roi, (50, 50))

    if BACKGROUND_SET == True:
        BACKGROUND = roi
        BACKGROUND_SET = False

    mask = cv2.absdiff(roi, BACKGROUND)
    mask = cv2.threshold(mask, 5, 255, cv2.THRESH_BINARY)[1]
    mask = cv2.GaussianBlur(mask, (3, 3), 3)
    mask = cv2.erode(mask, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3)), iterations=1)
    # mask = cv2.dilate(mask, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (2, 2)))
    roi = cv2.bitwise_and(roi, roi, mask=mask)

    if PREDICT_STATE == True:
        result = gst_model.predict(roi, saved_model)
        ans = GST_LIST[result]
        cv2.putText(img, ans, (20, 80), cv2.FONT_HERSHEY_TRIPLEX, 2, (0, 0, 255), 2, 1)

    time.sleep(0.05)
    roi = cv2.resize(roi, (200, 200))
    return roi

if __name__ == "__main__":
    main()
