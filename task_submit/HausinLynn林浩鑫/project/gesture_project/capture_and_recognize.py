import os
import cv2
import time
import threading
import numpy as np 
import gesture_preprocess
import gesture_recognize

Main_Window_Name = "video"
Gesture_Window_Name = "gesture"
Recognization_Window_Name = "recognization"

blank_img = np.zeros([200, 200, 3], np.uint8)
blank_img += 255

#def result_demo(img):


# parameter of a rect
X0 = 100
Y0 = 200
WIDTH = 200
HEIGHT = 200

def capture_and_recognize():
	cap = cv2.VideoCapture(0)

	start = time.time()

	cv2.imshow(Gesture_Window_Name, blank_img)
	cv2.imshow(Recognization_Window_Name, blank_img)

	while True:
		_, frame = cap.read()
		cv2.rectangle(frame, (X0, Y0), (X0+WIDTH, Y0+HEIGHT), (255, 0, 255), 1)
		cv2.imshow(Main_Window_Name, frame)

		if time.time() - start > 5:
			start = time.time()

			# get gesture
			gesture_img = frame[Y0:Y0+HEIGHT, X0:X0+WIDTH]
			gesture_img = gesture_preprocess.skin_mask(gesture_img)
			cv2.imshow(Gesture_Window_Name, gesture_img)

		# when press 'q', over
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break

	cap.release()
	cv2.destroyAllWindows()

if __name__ == '__main__':
	capture_and_recognize()