import numpy as np
import cv2

CAP = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    RET, FRAME = CAP.read()

    # Display the resulting frame
    cv2.imshow('frame', FRAME)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
CAP.release()
cv2.destroyAllWindows()