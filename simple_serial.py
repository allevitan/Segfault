import serial
import datetime
import time
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/tty.usbmodem00000001', 9600,timeout = .1)
data=[]
timed=[]
speed_sel=[]
time.sleep(2)

for speed in range(5,40):
	# if (speed==5):
	# 	ser.write(b'5')
	# if (speed==6):
	# 	ser.write(b'7')
	# if (speed==7):
	# 	ser.write(b'8')
	ser.write(str(speed))
	time.sleep(.1)
	i=0;
	while i<40 :
	  # 
	  # time_stamp = time.time()
	  # date_stamp = datetime.datetime.fromtimestamp(time_stamp).strftime('%Y-%m-%d %H:%M:%S')
	  # data.append(ser.readline())
	  time.sleep(0.1)
	  # timed.append(float(time_stamp))
	  # speed_sel.append(speed)
	  # time.sleep(1)
	  i=i+1
	  print i
print data