import cv2
import numpy as np
import os
import time
import threading
import gestureCNN as myNN

minValue = 70

x0 = 400
y0 = 200
height = 200
width = 200

saveImg = False
guessGesture = False

lastgesture = -1

kernel = np.ones((15,15),np.uint8)
kernel2 = np.ones((1,1),np.uint8)
skinkernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5))

# Which mask mode to use BinaryMask, SkinMask (True|False) OR BkgrndSubMask ('x' key)
bkgrndSubMode = False
mask = 0
bkgrnd = 0
counter = 0
# This parameter controls number of image samples to be taken PER gesture
numOfSamples = 201
gestname = ""
path = ""
mod = 0

#%%
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
    print("Saving img:",name)
    cv2.imwrite(path+name + ".png", img)
    time.sleep(0.04 )


def binaryMask(frame, x0, y0, width, height, framecount, plot ):
    global guessGesture, mod, lastgesture, saveImg
    
    cv2.rectangle(frame, (x0,y0),(x0+width,y0+height),(0,255,0),1)
    #roi = cv2.UMat(frame[y0:y0+height, x0:x0+width])
    roi = frame[y0:y0+height, x0:x0+width]
    
    gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray,(5,5),2)
    
    th3 = cv2.adaptiveThreshold(blur,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY_INV,11,2)
    ret, res = cv2.threshold(th3, minValue, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
    
    if saveImg == True:
        saveROIImg(res)
    elif guessGesture == True and (framecount % 5) == 4:
        #ores = cv2.UMat.get(res)
        t = threading.Thread(target=myNN.guessGesture, args = [mod, res])
        t.start()
    
    return res

	
def Main():
    global guessGesture, mod, binaryMode, mask, x0, y0, width, height, saveImg, gestname, path
    
    font = cv2.FONT_HERSHEY_SIMPLEX
    size = 0.5
    fx = 10
    fy = 350
    fh = 18
    
    print("Please wait a moment for loading ... ")
    mod = myNN.loadCNN(1)
    
    ## Grab camera input
    cap = cv2.VideoCapture(0)
    ##cv2.namedWindow('Original', cv2.WINDOW_NORMAL)

    # set rt size as 640x480
    ret = cap.set(3,640)
    ret = cap.set(4,480)

    framecount = 0
    fps = ""
    start = time.time()

    plot = np.zeros((512,512,3), np.uint8)
    
    while(True):
        ret, frame = cap.read()
        max_area = 0
        
        frame = cv2.flip(frame, 3)
        frame = cv2.resize(frame, (640,480))
                      
        if ret == True:
            ## show binary image
            roi = binaryMask(frame, x0, y0, width, height, framecount, plot)
            framecount = framecount + 1
            end  = time.time()
            timediff = (end - start)
            if( timediff >= 1):
                #timediff = end - start
                fps = 'FPS:%s' %(framecount)
                start = time.time()
                framecount = 0

        cv2.putText(frame,fps,(10,20), font, 0.7,(0,255,0),2,1)
        cv2.putText(frame,'Options:',(fx,fy), font, 0.7,(0,255,0),2,1)
        ##cv2.putText(frame,'b - Toggle Binary/SkinMask',(fx,fy + fh), font, size,(0,255,0),1,1)
        ##cv2.putText(frame,'g - Toggle Prediction Mode',(fx,fy + 2*fh), font, size,(0,255,0),1,1)
        cv2.putText(frame,'ESC - Exit',(fx,fy + 5*fh), font, size,(0,255,0),1,1)
        
        cv2.imshow('Detecting',frame)
        ##cv2.imshow('ROI', roi)
        
        if guessGesture == True:
            plot = np.zeros((200,200,3), np.uint8)
            plot = myNN.update(plot)
            
        cv2.imshow('The guesture you do now',plot)
        
        ## Keyboard inputs
        key = cv2.waitKey(5) & 0xff
        
        ## Use Esc key to close the program
        if key == 27:
            break
        
        ## Use b key to toggle between binary threshold or skinmask based filters
		
        ## Use g key to start gesture predictions via CNN
        elif key == ord('g'):
            guessGesture = not guessGesture
            print("Prediction Mode - {}".format(guessGesture))

        ## Use i,j,k,l to adjust ROI window
        ##elif key == ord('i'):
        ##  y0 = y0 - 5
        ##elif key == ord('k'):
        ##  y0 = y0 + 5
        ##elif key == ord('j'):
        ##  x0 = x0 - 5
        ##elif key == ord('l'):
        ##  x0 = x0 + 5
        #elif key != 255:
        #    print key
    

    #Realse & destroy
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    Main()

