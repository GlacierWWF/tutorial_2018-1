#!/usr/bin/env python2
# -*- -*coding: utf-8-s
#=================================================
# mnist_test.py                    
# @author    lhz_demo 
# @email     luhzh5@mail2.sysu.edu.cn 
# @version   2.2.7 
# @date      2018/11/11 

# Abustract: get dataset for training
#
#=================================================
import os
import numpy as np
import cv2
import time
import myCNN

#=======================================================#
#	开始定义选取的位置图片的大小录制的样本数量	#
#=======================================================#


font = cv2.FONT_HERSHEY_SIMPLEX #　
size = 0.5 
fx = 10
fy = 355
fh = 18

x0 = 300
y0 = 100

width = 200
height = 200

numofsamples = 300 
counter = 0  
gesturename = ""
path = ""


guessGesture = False 
lastgesture = -1 


binaryMode = True 
saveImg = False 

#=======================#
#	提示窗口	#
#=======================#
banner = """\n choose a number: \n
1 - Training a net work and store the net.
2 - Use pretrained model for gesture recognition
"""

# 保存ROI图像#
def saveROI(img):
    global path, counter, gesturename, saveImg
    if counter > numofsamples:
        saveImg = False
        gesturename = ''
        counter = 0
        return

    counter += 1
    name = gesturename + str(counter)
    print("Saving img: ", name)
    cv2.imwrite(path+name+'.png', img)
    time.sleep(0.05)

#掩莫#
def binaryMask(frame, x0, y0, width, height):
    global mod, guessGesture, lastgesture, saveImg
    cv2.rectangle(frame, (x0, y0), (x0+width, y0+height), (0, 255, 0))
    #提取ROI像素
    roi = frame[y0:y0+height, x0:x0+width]
    gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5, 5), 2) 
    th3 = cv2.adaptiveThreshold(blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 11, 2)
    ret, res = cv2.threshold(th3, 70, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)

    # 保存手势
    if saveImg == True and binaryMode == True:
        saveROI(res)
    elif saveImg == True and binaryMode == False:
        saveROI(roi)
    return res


#主函数：包括保存数据集，训练数据集，识别数据集#
def Main():
    global x0, y0, binaryMode, saveImg, gesturename, banner, guessGesturees, path
    while (True):
        ans = int(input(banner))
        if (ans == 1): 
            print("-------------开始训练模型-------------------")
            myCNN.TRAIN()
            input("Press any key to continue")
            break
        if (ans == 2):
            print("--------------载入保存的模型-----------------")
            break
        else:
            print("输入有误！")
            return 0

    cap = cv2.VideoCapture(0)
    gesture_copy = "caculate"
    while(True):
        k=0
        ret, frame = cap.read()
	# 图像翻转  如果不翻转，视频中看起来的刚好和我们是左右对称的
        frame = cv2.flip(frame, 2)  
        frame1 = frame.copy()
        roi = binaryMask(frame, x0, y0, width, height)
        #显示提示语句
        cv2.putText(frame, "Option: ", (fx, fy), font, size, (0, 0,255))  
        cv2.putText(frame, "b-'Binary mode'/ r- 'RGB mode' ", (fx, fy + fh), font, size, (0, 0,255))  
        cv2.putText(frame, "p-'prediction mode'", (fx, fy + 2 * fh), font, size, (0, 0,255))  
        cv2.putText(frame, "s-'new gestures(twice)'", (fx, fy + 3 * fh), font, size, (0, 0, 255)) 
        cv2.putText(frame, "q-'quit'", (fx, fy + 4 * fh), font, size, (0, 0, 255))  
        key = cv2.waitKey(1) & 0xFF
        if key == ord('b'):
            # binaryMode = not binaryMode
            binaryMode = True
            print("Binary Threshold filter active")
        elif key == ord('r'):
            binaryMode = False

        if key == ord('i'):  # 调整ROI框
            y0 = y0 - 5
        elif key == ord('k'):
            y0 = y0 + 5
        elif key == ord('j'):
            x0 = x0 - 5
        elif key == ord('l'):
            x0 = x0 + 5

        if key == ord('p'):
            Roi = np.reshape(roi, [width, height, 1])
            gesture = myCNN.Gussgesture(Roi)
            gesture_copy = gesture

        if key == ord('q'):
            break

        if key == ord('s'):
            #录制手势
            if gesturename != "":  #
                saveImg = True
            else:
                print("Enter a gesture group name first, by enter press 'n'! ")
                saveImg = False
        elif key == ord('n'):
            # 开始录制新手势
            # 首先输入文件夹名字
            gesturename = input("enter the gesture folder name: ")

            os.makedirs(gesturename)

            path = "./" + gesturename + "/" # 生成文件夹的地址  用来存放录制的手势

        #展示处理之后的视频帧
        frame1 = frame.copy()
        cv2.putText(frame1, gesture_copy, (400, 440), font, 1, (0, 255, 255))  # 标注字体
        frame = frame1.copy()
        cv2.imshow('frame', frame)
        if (binaryMode):
            cv2.imshow('ROI', roi)
        else:
            cv2.imshow("ROI", frame[y0:y0+height, x0:x0+width])


    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    Main()
