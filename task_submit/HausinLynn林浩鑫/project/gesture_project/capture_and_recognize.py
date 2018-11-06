#!/usr/bin/env python3

"""
    file: capture_and_recognize.py
    brief: capture and recognize the gesture
    image in real time

    Details:
        author: HausinLynn
        email: linhx36@mail2.sysu.edu.cn
        version: 1.0.0.1
        date: 11/05/2018

    Change History
    <Date>     | <Version> | <Author>
    11/05/2018 | 1.0.0.1   | HausinLynn    
"""

import os
import cv2
import time
import threading
import numpy as np 
import gesture_preprocess
import gesture_recognize


# window name
Main_Window_Name = "video"
Gesture_Window_Name = "gesture"
Recognization_Window_Name = "recognization"

# blank image
blank_img = np.zeros([200, 200, 3], np.uint8)
blank_img += 255
src_img = blank_img.copy()


def result_demo():
	"""process and recognize src_img,
	then demo the result.

    Arg:
        None

    Return:
        None
    """

    # blank
	demo_img = blank_img.copy()
	# message
	msg = 'Identify...'
	# put text
	cv2.putText(
		demo_img, msg, (18, 100),
		cv2.FONT_HERSHEY_DUPLEX,
		fontScale=1,
		color=(208, 32, 144),
		thickness=2
		)
	# show
	cv2.imshow(Recognization_Window_Name, demo_img)

	# preprocess
	processed_img = gesture_recognize.pre_process(src_img)
	# recognize
	result = gesture_recognize.recognize(processed_img)

	# calculate the text location
	text_size = cv2.getTextSize(
		result,
		cv2.FONT_HERSHEY_DUPLEX,
		fontScale=1,
		thickness=2
		)
	origin_point = (100 - int(text_size[0][0]/2), 100)

	# result demo
	demo_img = blank_img.copy()
	cv2.putText(
		demo_img, result, origin_point,
		cv2.FONT_HERSHEY_DUPLEX,
		fontScale=1,
		color=(208, 32, 144),
		thickness=2
		)
	cv2.imshow(Recognization_Window_Name, demo_img)


# parameter of a rect
X0 = 100
Y0 = 200
WIDTH = 200
HEIGHT = 200

def capture_and_recognize():
	"""capture and recognize the gesture
    image in real time.

    Arg:
        None

    Return:
        None
    """

    # initialize
	cap = cv2.VideoCapture(0)
	_, frame = cap.read()
	cv2.rectangle(frame, (X0, Y0), (X0+WIDTH, Y0+HEIGHT), (255, 0, 255), 1)
	msg = 'Time: 0s'
	cv2.putText(
		frame, msg, (0, 20),
		cv2.FONT_HERSHEY_SIMPLEX,
		fontScale=0.8,
		color=(255, 0, 255),
		thickness=2
		)
	msg = "Please press 's' to start."
	cv2.putText(
		frame, msg, (0, 48),
		cv2.FONT_HERSHEY_SIMPLEX,
		fontScale=0.8,
		color=(255, 0, 255),
		thickness=2
		)
	cv2.imshow(Main_Window_Name, frame)

	# wait key to start
	while True:
		if cv2.waitKey(1) & 0xFF == ord('s'):
			break

	# timer
	start = time.time()
	origin = start

	cv2.imshow(Gesture_Window_Name, blank_img)
	cv2.imshow(Recognization_Window_Name, blank_img)

	# loop of capturing and regnizing
	while True:
		_, frame = cap.read()
		cv2.rectangle(frame, (X0, Y0), (X0+WIDTH, Y0+HEIGHT), (255, 0, 255), 1)
		# show time
		msg = 'Time: ' + str(int(time.time()-origin)) + 's'
		cv2.putText(
			frame, msg, (0, 20),
			cv2.FONT_HERSHEY_SIMPLEX,
			fontScale=0.8,
			color=(255, 0, 255),
			thickness=2
			)
		# prompt
		msg = "Please press 'q' to exit."
		cv2.putText(
			frame, msg, (0, 48),
			cv2.FONT_HERSHEY_SIMPLEX,
			fontScale=0.8,
			color=(255, 0, 255),
			thickness=2
			)
		cv2.imshow(Main_Window_Name, frame)

		# each 5 seconds
		if time.time() - start > 5:
			start = time.time()

			# prompt
			demo_img = blank_img.copy()
			msg = 'Capture...'
			cv2.putText(
				demo_img, msg, (18, 100),
				cv2.FONT_HERSHEY_DUPLEX,
				fontScale=1,
				color=(208, 32, 144),
				thickness=2
				)
			cv2.imshow(Recognization_Window_Name, demo_img)

			# get gesture and show
			gesture_img = frame[Y0:Y0+HEIGHT, X0:X0+WIDTH]
			global src_img
			src_img = gesture_img.copy()
			gesture_img = gesture_preprocess.skin_mask(gesture_img)
			cv2.imshow(Gesture_Window_Name, gesture_img)

			# start thread to recognize
			mythread = threading.Thread(target=result_demo)
			mythread.start()

		# when press 'q', over
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break

	# release
	cap.release()
	# destroy
	cv2.destroyAllWindows()

if __name__ == '__main__':
	capture_and_recognize()