# -*-coding: utf-8 -*-
'''**********************************************
 *  @file    myAudio.py
 *  @brief   code for record and play
 *
 *---------------------------------------
 *  @Author  杨卓
 *  @Version 1.0.0.1
 *  @Date    11/9/2018
 *----------------------------------------
'''
import wave
from pyaudio import PyAudio, paInt16

framerate = 8000
NUM_SAMPLES = 2000	#pyaudio内置缓冲大小
channels = 1		# 单声道
sampwidth = 2
TIME = 1	# 录音时间 = TIME * 5

def save_wave_file(filename, data):
    wf = wave.open(filename, 'wb')
    wf.setnchannels(channels)
    wf.setsampwidth(sampwidth)
    wf.setframerate(framerate)
    wf.writeframes(b"".join(data))
    wf.close()

def myRecord():
    p = PyAudio()
    stream = p.open(format=paInt16,
                    channels=1,
                    rate=framerate,
                    input=True,
                    frames_per_buffer=NUM_SAMPLES)
    my_buf = []
    count = 0

    while count < TIME*20:
        string_audio_data = stream.read(NUM_SAMPLES)
        my_buf.append(string_audio_data)
        count += 1
        print("Being recorded")

    save_wave_file('re1.wav', my_buf)	# 音频文件命名为 re1.wav
    stream.close()

CHUNK = 2014
def myPlay():
    wf=wave.open(r"re1.wav",'rb')
    p=PyAudio()
    stream=p.open(format=p.get_format_from_width(wf.getsampwidth()),
                  channels= wf.getnchannels(),
                  rate=wf.getframerate(),
                  output=True) 

    while True:
        data=wf.readframes(CHUNK)
        if data=="":break
        stream.write(data)

    stream.close()
    p.terminate()

if __name__ == '__main__':
    myRecord()
    print("End of record!")
    myPlay()
    
