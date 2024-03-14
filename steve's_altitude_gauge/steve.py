# This code is adapted from https://forum.arduino.cc/t/pc-arduino-comms-using-python-updated/574496 and https://jeremypedersen.com/posts/2022-03-28-mcpi-macos/

import serial
import time
from mcpi.minecraft import Minecraft

startMarker = '<'
endMarker = '>'
dataStarted = False
dataBuf = ""
messageComplete = False

mc = Minecraft.create(address="localhost", port=4711)

#========================
#========================
    # retrieving change in Steve's y-position




#========================
#========================
    # functions for serial communication

def setupSerial(baudRate, serialPortName):
    
    global  serialPort
    
    serialPort = serial.Serial(port= serialPortName, baudrate = baudRate, timeout=0, rtscts=True)

    print("Serial port " + serialPortName + " opened  Baudrate " + str(baudRate))

    waitForArduino()

#========================

def sendToArduino(stringToSend):
    
    # this adds the start- and end-markers before sending
    global startMarker, endMarker, serialPort
    
    stringWithMarkers = (startMarker)
    stringWithMarkers += stringToSend
    stringWithMarkers += (endMarker)

    serialPort.write(stringWithMarkers.encode('utf-8')) # encode needed for Python3


#==================

def recvLikeArduino():

    global startMarker, endMarker, serialPort, dataStarted, dataBuf, messageComplete

    if serialPort.inWaiting() > 0 and messageComplete == False:
        x = serialPort.read().decode("utf-8") # decode needed for Python3
        
        if dataStarted == True:
            if x != endMarker:
                dataBuf = dataBuf + x
            else:
                dataStarted = False
                messageComplete = True
        elif x == startMarker:
            dataBuf = ''
            dataStarted = True
    
    if (messageComplete == True):
        messageComplete = False
        return dataBuf
    else:
        return "XXX" 

#==================

def waitForArduino():

    # wait until the Arduino sends 'Arduino is ready' - allows time for Arduino reset
    # it also ensures that any bytes left over from a previous message are discarded
    
    print("Waiting for Arduino to reset")
     
    msg = ""
    while msg.find("Arduino is ready") == -1:
        msg = recvLikeArduino()
        if not (msg == 'XXX'): 
            print(msg)



#====================
#====================
    # the program


setupSerial(9600, "/dev/cu.usbmodem1101")
# count = 0

yPos = mc.player.getPos().y + 200
prevTime = time.time()

sendToArduino("-5000")

goUp = False

while True:
    # check for a reply
    arduinoReply = recvLikeArduino()
    if not (arduinoReply == 'XXX'):
        print ("Reply: %s" %(arduinoReply))
        
    # send a message at intervals
    if time.time() - prevTime > 3.0:
        prevTime = time.time()

        print("send")
        if goUp:
            sendToArduino("500")
        else:
            sendToArduino("-500")
        
        goUp = not goUp

        # sendToArduino("50") 


        
        prevPos = yPos
        yPos = mc.player.getPos().y + 200
        yDiff = (yPos - prevPos)

        yTranslate = yDiff * (10500/229)

        # if abs(yDiff) > 1:
        #     print("send")
        #     sendToArduino(str(yTranslate))


        # count += 100