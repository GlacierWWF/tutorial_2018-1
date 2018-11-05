#!/usr/bin/env python3

"""
    file: generate_images.py
    brief: generate gesture images from 
    camera.

    Details:
        author: HausinLynn
        email: linhx36@mail2.sysu.edu.cn
        version: 1.0.0.1
        date: 11/01/2018

    Change History
    <Date>     | <Version> | <Author>
    11/01/2018 | 1.0.0.1   | HausinLynn    
"""

import os
import cv2
import gesture_preprocess


# parameter of a rect
X0 = 100
Y0 = 200
WIDTH = 200
HEIGHT = 200

def capture():
	"""capture the gesture images

	the camera of laptop will be opened to capture
	the image, then the rect of the image will be
	stored, that means that you need to put your
	gesture on the rect you see.

    Arg:
        img: image to be captured
    """

    # capture
	cap = cv2.VideoCapture(0)

	# gesture image type, 'yeah', 'OK', 'nice', 'love', 'contempt' or 'right'
	gesture_type = input('Which type of gesture are you going to capture?\n' + 
		'"yeah", "OK", "nice", "love", "contempt" or "right"\n')
	image_path = './gesture_images/' + gesture_type + '_images'
	count = len([image for image in os.listdir(image_path)])
	
	# loop
	while(1):
	    # get a frame
	    _, frame = cap.read()
	    cv2.rectangle(frame, (X0, Y0), (X0+WIDTH, Y0+HEIGHT), (255, 0, 255), 1)
	    # show a frame
	    cv2.imshow("capture", frame)

	    # when press 's', store
	    if cv2.waitKey(1) & 0xFF == ord('s'):
	    	# path to save the image
		    image_name = '/' + gesture_type + '_' + str(count) + '.png'
		    save_path = os.path.join(image_path + image_name)

		    # get gesture
		    img = frame[Y0:Y0+HEIGHT, X0:X0+WIDTH]
		    img = gesture_preprocess.skin_mask(img)
		    cv2.imwrite(save_path, img)
		    count += 1

		# when press 'q', over
	    if cv2.waitKey(1) & 0xFF == ord('q'):
	        break

	cap.release()
	cv2.destroyAllWindows()

if __name__ == '__main__':
	capture()