"""@video_capture docstring
    @file:      video_capture.py
    @brief:     capture video and recognize the gestures
    @author:    atlanswer
    @date:      2018/11/10
    @version:   debug
"""
import os
import time
# video capture
import cv2
# image precessing
import numpy as np
# CNN model
import CNN_for_gesture as CNN

MIN_VALUE = 70

x0 = 400
y0 = 200
height = 200
width = 200

saveImg = False
guessGesture = False
visualize = False

lastgesture = -1

kernel = np.ones((15, 15), np.uint8)
kernel2 = np.ones((1, 1), np.uint8)
skinkernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))

# Which mask mode to use BinaryMask, SkinMask (True|False) OR BkgrndSubMask ('x' key)
binaryMode = True
bkgrndSubMode = False
mask = 0
bkgrnd = 0
counter = 0
# This parameter controls number of image samples to be taken PER gesture
numOfSamples = 201
gestname = ""
path = ""
mod = 0

prompt = """\nActions:
    1- Use pretrained model for gesture recognition
    2- Train the model
    3- Exit	
    """

def saveROIImg(img):
    global counter, gestname, path, saveImg
    if counter > (numOfSamples - 1):
        # Reset the parameters
        saveImg = False
        gestname = ''
        counter = 0
        return

    counter = counter + 1
    name = gestname + str(counter)
    print("Saving img: ", name)
    cv2.imwrite(path + name + ".png", img)
    time.sleep(0.04)

def skinMask(frame, x0, y0, width, height, framecount, plot):
    global guessGesture, visualize, mod, lastgesture, saveImg
    # HSV values
    low_range = np.array([0, 50, 80])
    upper_range = np.array([30, 200, 255])
    # frame area
    cv2.rectangle(frame, (x0, y0), (x0 + width, y0 + height), (0, 255, 0), 1)
    # ROI area
    roi = frame[y0:y0+height, x0:x0+width]
    # process image
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)    
    mask = cv2.inRange(hsv, low_range, upper_range)
    mask = cv2.erode(mask, skinkernel, iterations = 1)
    mask = cv2.dilate(mask, skinkernel, iterations = 1)
    mask = cv2.GaussianBlur(mask, (15,15), 1)
    # bitwise and mask original frame
    res = cv2.bitwise_and(roi, roi, mask=mask)
    # convert to grayscale
    res = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)

    if saveImg == True:
        saveROIImg(res)
    elif guessGesture == True and (framecount % 5) == 4:
        t = threading.Thread(target=CNN.guess_gesture, args=[mod, res])
        t.start()
    
    return res

def binaryMask(frame, x0, y0, width, height, framecount, plot ):
    global guessGesture, visualize, mod, lastgesture, saveImg

    cv2.rectangle(frame, (x0, y0), (x0 + width, y0 + height), (0, 255, 0), 1)
    roi = frame[y0:y0+height, x0:x0+width]

    gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5, 5), 2)

    th3 = cv2.adaptiveThreshold(blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 11, 2)
    ret, res = cv2.threshold(th3, MIN_VALUE, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    if saveImg == True:
        saveROIImg(res)
    elif guessGesture == True and (framecount % 5) == 4:
        t = threading.Thread(target=CNN.guess_gesture, args=[mod, res])
        t.start()

    return res

def Main():
    global guessGesture, mod, binaryMode, mask, x0, y0, width, height, saveImg, gestname, path

    font = cv2.FONT_HERSHEY_SIMPLEX
    size = 0.5
    fx = 10
    fy = 350
    fh = 18
        
    #Call CNN model loading callback
    while True:
        ans = int(input(prompt))
        if ans == 2:
            mod = CNN.load_model(-1)
            CNN.train_model(mod)
            input("Press any key to continue")
            break
        elif ans == 1:
            print("Will load default weight file")
            mod = CNN.load_model(0)
            break
        else:
            print("Exiting...")
            return 0

    ## Capture camera input
    cap = cv2.VideoCapture(0)
    cv2.namedWindow("Camera", cv2.WINDOW_NORMAL)
    # set rt size as 640x480
    ret = cap.set(3, 640)
    ret = cap.set(4, 480)

    framecount = 0
    fps = ""
    start = time.time()

    plot = np.zeros((512, 512, 3), np.uint8)

    while(True):
        ret, frame = cap.read()
        max_area = 0

        frame = cv2.flip(frame, 3)
        frame = cv2.resize(frame, (640, 480))

        if ret == True:
            if binaryMode == True:
                roi = binaryMask(frame, x0, y0, width, height, framecount, plot)
            else:
                roi = skinMask(frame, x0, y0, width, height, framecount, plot)

            framecount = framecount + 1
            end = time.time()
            timediff = (end - start)
            if(timediff >= 1):
                fps = "FPS:%s"%(framecount)
                start = time.time()
                framecount = 0

        cv2.putText(frame, fps, (10, 20), font, 0.7, (0, 255, 0), 2, 1)
        cv2.putText(frame, "Options:", (fx, fy), font, 0.7, (0, 255, 0), 2, 1)
        cv2.putText(frame, "b - Toggle Binary/SkinMask", (fx, fy + fh), font, size, (0, 255, 0), 1, 1)
        cv2.putText(frame,'x - Toggle Background Sub Mask',(fx,fy + 2*fh), font, size,(0,255,0),1,1)		
        cv2.putText(frame,'g - Toggle Prediction Mode',(fx,fy + 3*fh), font, size,(0,255,0),1,1)
        cv2.putText(frame,'q - Toggle Quiet Mode',(fx,fy + 4*fh), font, size,(0,255,0),1,1)
        cv2.putText(frame,'n - To enter name of new gesture folder',(fx,fy + 5*fh), font, size,(0,255,0),1,1)
        cv2.putText(frame,'s - To start capturing new gestures for training',(fx,fy + 6*fh), font, size,(0,255,0),1,1)
        cv2.putText(frame,'ESC - Exit',(fx,fy + 7*fh), font, size,(0,255,0),1,1)

        if guessGesture == True:
            plot = np.zeros((512, 512, 3), np.uint8)
            plot = CNN.update(plot)
        
        cv2.imshow('Gesture Probability', plot)
        
        # gat keyboard input
        key = cv2.waitKey(5) & 0xff
        # Exit when ESC is pressed
        if key == 27:
            break
        ## Use b key to toggle between binary threshold or skinmask based filters
        elif key == ord('b'):
            binaryMode = not binaryMode
            bkgrndSubMode = False
            if binaryMode:
                print("Binary Threshold filter active")
            else:
                print("SkinMask filter active")
        
		## Use g key to start gesture predictions via CNN
        elif key == ord('x'):
            takebkgrndSubMask = True
            bkgrndSubMode = True
            print("BkgrndSubMask filter active")

        ## Start predicting when g is pressed
        elif key == ord('g'):
            guessGesture = not guessGesture
            print("Prediction Mode - {}".format(guessGesture))

        ## Use i,j,k,l to adjust ROI window
        elif key == ord('i'):
            y0 = y0 - 5
        elif key == ord('k'):
            y0 = y0 + 5
        elif key == ord('j'):
            x0 = x0 - 5
        elif key == ord('l'):
            x0 = x0 + 5

        # Use s key to start/pause/resume taking snapshots
        # numOfSamples controls number of snapshots to be taken PER gesture
        elif key == ord('s'):
            saveImg = not saveImg

            if gestname != '':
                saveImg = True
            else:
                print("Enter a gesture group name first, by pressing 'n'")
                saveImg = False

        ## Use n key to enter gesture name
        elif key == ord('n'):
            gestname = input("Enter the gesture folder name: ")
            try:
                os.makedirs(gestname)
            except OSError as e:
                # if directory already present
                if e.errno != 17:
                    print('Some issue while creating the directory named -' + gestname)

            path = "./"+gestname+"/"

    # Release camera and close window
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    Main()
