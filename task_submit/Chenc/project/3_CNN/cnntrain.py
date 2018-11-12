import cv2
import numpy as np
import os
import time
import threading
import gestureCNN as myNN
def Main():
    global mod
    ##loading CNN and train the data;
    mod = myNN.loadCNN(-1)
    myNN.trainModel(mod)
    input("Press any key to continue")
    cv2.destroyAllWindows()
if __name__ == "__main__":
    Main()

