import serial
import time

ser = serial.Serial('COM11', 9600, timeout=1)
time.sleep(2)

def send(cmd):
    ser.write((cmd + "\n").encode())
    print(">>", cmd)

send("SET_PIN:4:OUTPUT")

print("Done blinking")
