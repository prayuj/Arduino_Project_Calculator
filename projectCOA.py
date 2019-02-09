from math import *
import serial
from time import sleep
from decimal import Decimal


ser = serial.Serial('com3', 9600, timeout = 0.5)

connected = False

print(ser.name)

def evalUpd(eqn):
    numb = eval(eqn)
    numb = round(numb, 4)
    numbstr = str(numb)
    x = len(numbstr)
    if(x>=12):
        print("Making it Smaller")
        ans = '%.2E' % Decimal(numbstr)
        print("Smaller number is",ans);
        ansstr = str(ans)
        ansstr = "Ans:" + ansstr + "\n"
        return ansstr
    else:
        numbstr = "Ans:" + numbstr + "\n"
        return numbstr

while not connected:
    serin = ser.read()
    connected = True

while True:
    ser.flush()
    var = ser.readline()#byte type
    varS = var.decode() #string type
    print('Waiting for input...')
    if varS is not "":
        posOfNextLine = varS.find('\n')
        varS = varS[:posOfNextLine:]
        print('Recieved')
        print(varS)
        try:
            answer = evalUpd(varS)
            print(answer)
            ser.write(answer.encode())
        except:
            ser.write(b"Invalid Syntax")
        sleep(.1)
    del var, varS

