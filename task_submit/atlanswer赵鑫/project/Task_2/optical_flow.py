"""@optical_flow docstring
    @file:      optical_flow.py
    @brief:     optical flow algorithm demo
    @author:    atlanswer
    @date:      2018/11/13
    @version:   debug
"""
from __future__ import print_function

import time
# for image processing
import numpy as np
# for camera capture
import cv2

help_message = """Usage: optical_flow.py [<video_path>]
                  Keyboard Action:
                  1 - toggle HSV flow visualization
                  2 - toggle glitch
               """

count = 0

def draw_flow(src_img, flow, step=16):
    """draw_flow()
    """
    #from the beginning to position 2 (excluded channel info at position 3)
    h, w = src_img.shape[:2]
    y, x = np.mgrid[step/2:h:step, step/2:w:step].reshape(2,-1).astype(int)
    fx, fy = flow[y,x].T
    lines = np.vstack([x, y, x+fx, y+fy]).T.reshape(-1, 2, 2)
    lines = np.int32(lines + 0.5)
    vis = cv2.cvtColor(src_img, cv2.COLOR_GRAY2BGR)
    cv2.polylines(vis, lines, 0, (0, 255, 0))
    for (x1, y1), (x2, y2) in lines:
        cv2.circle(vis, (x1, y1), 1, (0, 255, 0), -1)
    return vis

def draw_hsv(flow):
    """
    """
    (h, w) = flow.shape[:2]
    (fx, fy) = (flow[:, :, 0], flow[:, :, 1])
    ang = np.arctan2(fy, fx) + np.pi
    v = np.sqrt(fx * fx + fy * fy)
    hsv = np.zeros((h, w, 3), np.uint8)
    hsv[..., 0] = ang * (180 / np.pi / 2)
    hsv[..., 1] = 0xFF
    hsv[..., 2] = np.minimum(v * 4, 0xFF)
    bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
    cv2.imshow('hsv', bgr)
    return bgr


def warp_flow(img, flow):
    (h, w) = flow.shape[:2]
    flow = -flow
    flow[:, :, 0] += np.arange(w)
    flow[:, :, 1] += np.arange(h)[:, np.newaxis]
    res = cv2.remap(img, flow, None, cv2.INTER_LINEAR)
    return res

def main():
    """
    """
    # for getting the arguement list
    import sys
    print(help_message)
    if len(sys.argv) == 1:
        print("[info] Loading video.")
        video_path = sys.argv[1]
    elif len(sys.argv) > 1:
        print("[Error] Too many arguements. Switch to camera input now.")
        video_path = 0
    else:
        print("[info] Using camera input.")
        video_path = 0

    cap = cv2.VideoCapture(video_path)
    (retval, frame) = cap.read()

    if cap.isOpened() == False:
        print("[Error] Unable to fetch VideoCapture data.")

    pre_frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    show_hsv = True
    show_glitch = False
    cur_glitch = frame.copy()

    while True:
        (retval, frame) = cap.read()
        vis = frame.copy()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        flow = cv2.calcOpticalFlowFarneback(pre_frame_gray,gray,None,0.5,5,15,3,5,1.1,cv2.OPTFLOW_FARNEBACK_GAUSSIAN)
        pre_frame_gray = gray
        cv2.imshow('flow', draw_flow(gray, flow))
        if show_hsv:
            gray1 = cv2.cvtColor(draw_hsv(flow), cv2.COLOR_BGR2GRAY)
            thresh = cv2.threshold(gray1, 25, 0xFF,
                                   cv2.THRESH_BINARY)[1]
            thresh = cv2.dilate(thresh, None, iterations=2)
            cv2.imshow('thresh', thresh)
            gray2, cnts, hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

            # loop over the contours
            for c in cnts:
                # if the contour is too small, ignore it
                (x, y, w, h) = cv2.boundingRect(c)
                if w > 100 and h > 100 and w < 900 and h < 680:
                    cv2.rectangle(vis, (x, y), (x + w, y + h), (0, 0xFF, 0), 4)
                    cv2.putText(vis,str(time.time()),(x, y),cv2.FONT_HERSHEY_SIMPLEX,1,(0, 0, 0xFF),1)
            cv2.imshow('Image', vis)
        if show_glitch:
            cur_glitch = warp_flow(cur_glitch, flow)
            cv2.imshow('glitch', cur_glitch)
        ch = 0xFF & cv2.waitKey(5)
        if ch == 27:
            break
        if ch == ord('1'):
            show_hsv = not show_hsv
            print ('HSV flow visualization is', ['off', 'on'][show_hsv])
        if ch == ord('2'):
            show_glitch = not show_glitch
            if show_glitch:
                cur_glitch = frame.copy()
            print ('glitch is', ['off', 'on'][show_glitch])
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()