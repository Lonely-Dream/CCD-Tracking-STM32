import serial
import numpy
import time
from matplotlib import pyplot as plt

def OpenPort(port,bps,ttimeout):
    ret=False
    try:
        ser=serial.Serial(port,bps,timeout=ttimeout)
        if ser.is_open:
            ret=True
    except Exception as e:
        print(e)
    return ser,ret

def ClosePort(ser):
    ser.close()
    return

#main
lPixel=[]
sum=0
x=numpy.arange(1,129)
ser,ret=OpenPort("COM4",38400,10)
print("OpenPort："+str(ret))
if ret:
    plt.figure(figsize=(8,6),dpi=80)
    plt.ion()
    plt.axis([0,129,0,256])
    while True:
        if ser.in_waiting<128:
            print("waiting")
            time.sleep(1)
            continue
        lPixel.clear()
        plt.cla()
        for i in range(128):
            pixel=int.from_bytes(ser.read(),byteorder='big')
            lPixel+=[pixel]
        print(lPixel)
        y=numpy.asarray(lPixel)

        plt.plot(x,y)
        plt.pause(0.01)
            
