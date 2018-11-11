#!/usr/bin/env python2
# -*- -*coding: utf-8-

#=========================================================
# mnist_test.py                    
# @author    lhz_demo 
# @email     luhzh5@mail2.sysu.edu.cn 
# @version   1.1.2
# @date      2018/11/07 

# Abustract: 使用光流算法检测视频的平均像素位移
#		当然只能检测到部分移动物体，因为用系数算法
#=========================================================
import numpy as np
import cv2
import sys

#捕捉摄像头
cap = cv2.VideoCapture(0)


feature_params = dict(maxCorners=10,
                      qualityLevel=0.1,
                      minDistance=1,
                      blockSize=9)

# LK光流法相关参数
lk_params = dict(winSize=(30, 30),
                 maxLevel=2,
                 criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# 创建随机颜色
color = np.random.randint(0, 255, (100, 3))

# 获取视频第一帧
ret, old_frame = cap.read()
# 转换为灰度
old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
# ST检测角点，注意这里参数传递的方法
p0 = cv2.goodFeaturesToTrack(old_gray, mask=None, **feature_params)

# 创建一个新的图片用于绘制
mask = np.zeros_like(old_frame)

while 1:
    ret, frame = cap.read()

    if frame is None:
        cv2.waitKey(0)
        break
    else:
        frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        # 计算光流
        p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

        # 选择好的特征点
        if p1 is None:
            pass
        elif p0 is None:
            pass
        else:
	    #保存两镇之间的像素点
            good_new = p1[st == 1]
            good_old = p0[st == 1]
	    #返回像素位移
            shift = good_new - good_old

            total_shift = 0
            # 绘制轨迹
            for i, (new, old) in enumerate(zip(good_new, good_old)):
                #计算总共像素位移
                total_shift = (shift[i][0]*shift[i][0]+shift[i][1]*shift[i][1])**0.5 + total_shift
                #取平均值，得到平均像素位移
                average_shift = total_shift/(i+1)
                a, b = new.ravel()
                c, d = old.ravel()
                mask = cv2.line(mask, (a, b), (c, d), color[i].tolist(), 2)
                frame = cv2.circle(frame, (a, b), 5, color[i].tolist(), -1)
            #控制输出格式
            average_shift = ("%3.5f"% average_shift)
            img1 = frame.copy()
	    #把数据显示在图片上
            cv2.putText(img1,"average_shift is : "+str(average_shift)+"pixel",(0,50),cv2.FONT_HERSHEY_COMPLEX,1,(255,23,0),2);
            
            img = cv2.add(img1, mask)
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        write = cv2.VideoWriter('output2.avi', fourcc,3.0,(640,480))
        cv2.imshow('frame', img)
        k = cv2.waitKey(20) & 0xff
        if k == 27:
            break
        else:
            frame1 = cv2.flip(img,0)
            write.write(frame1)
        # 更新上一帧以及特征点
        old_gray = frame_gray.copy()
        p0 = good_new.reshape(-1, 1, 2)

cv2.destroyAllWindows()
cap.release()
