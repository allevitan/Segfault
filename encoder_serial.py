import serial
import datetime
import time
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/tty.usbmodem00000001', 9600,timeout = .3)
data=[]
timed=[]
speed_sel=[]
#if you only want to send data to arduino (i.e. a signal to move a servo)
def send( theinput ):
  ser.write( theinput )
  time.sleep(0.1)

#if you would like to tell the arduino that you would like to receive data from the arduino
def send_and_receive( theinput ):
  ser.write( theinput )
  while True:
    try:
      time.sleep(0.01)
      state = ser.readline()
      print state
      return state
    except:
      pass
  time.sleep(0.1)

i=0
time.sleep(5)
send('A')
time.sleep(5)
for speed in range(5,8):
	# send(str(speed))
	while i<100 :
	  time_stamp = time.time()
	  sensor = send_and_receive('1')
	  date_stamp = datetime.datetime.fromtimestamp(time_stamp).strftime('%Y-%m-%d %H:%M:%S')
	  data.append(sensor)
	  timed.append(float(time_stamp))
	  speed_sel.append(speed)
	  # time.sleep(1)
	  i=i+1

# tdata=['-88\t44\t-159\r\n', 'a/g:\t-16200\t-2048\t2496\t-85\t24\t-131\r\n', 'a/g:\t-16204\t-2020\t2540\t-78\t11\t-136\r\n', 'a/g:\t-16168\t-2156\t2564\t-135\t31\t-163\r\n', 'a/g:\t-16232\t-2016\t2488\t-72\t19\t-133\r\n', 'a/g:\t-16212\t-2116\t2596\t-107\t24\t-140\r\n', 'a/g:\t-16232\t-2100\t2496\t-159\t33\t-110\r\n', 'a/g:\t-16268\t-2164\t2404\t-150\t42\t-113\r\n', 'a/g:\t-16344\t-2064\t2252\t-154\t87\t-110\r\n', 'a/g:\t-16192\t-2200\t2556\t-122\t55\t-135\r\n', 'a/g:\t-16148\t-2108\t2556\t-91\t32\t-153\r\n', 'a/g:\t-16192\t-2136\t2288\t-95\t-11\t-166\r\n', 'a/g:\t-16252\t-2060\t2536\t-147\t72\t-55\r\n', 'a/g:\t-16204\t-2208\t2388\t-177\t72\t-65\r\n', 'a/g:\t-16140\t-2056\t2556\t-131\t68\t-95\r\n', 'a/g:\t-16208\t-2140\t2428\t-56\t43\t-143\r\n', 'a/g:\t-16212\t-2116\t2656\t19\t-10\t-203\r\n', 'a/g:\t-16252\t-2100\t2340\t-81\t42\t-188\r\n', 'a/g:\t-16192\t-2116\t2564\t-24\t23\t-189\r\n', 'a/g:\t-16260\t-2028\t2628\t-5\t50\t-145\r\n', 'a/g:\t-16288\t-2036\t2340\t-10\t11\t-180\r\n', 'a/g:\t-16160\t-2124\t2612\t-31\t13\t-224\r\n', 'a/g:\t-16252\t-2068\t2568\t-51\t44\t-175\r\n', 'a/g:\t-16200\t-2064\t2484\t-119\t56\t-151\r\n', 'a/g:\t-16208\t-2068\t2680\t-179\t96\t-12\r\n', 'a/g:\t-16252\t-2152\t2412\t-159\t80\t-134\r\n', 'a/g:\t-16228\t-2068\t2564\t-136\t50\t-115\r\n', 'a/g:\t-16216\t-2196\t2680\t-6\t0\t-16\t84\r\n', 'a/g:\t-16248\t-2048\t2644\t-192\t106\t-45\r\n', 'a/g:\t-16368\t-2040\t2584\t73\t-97\t-287\r\n', 'a/g:\t-16132\t-2140\t2352\t-19\t-70\t-107\r\n', 'a/g:\t-16096\t-2112\t2568\t-8\t-46\t-208\r\n', 'a/g:\t-16104\t-2008\t2420\t-75\t40\t-216\r\n', 'a/g:\t-16176\t-2140\t2452\t6\t40\t-193\r\n', 'a/g:\t-16164\t-2188\t2484\t-132\t12\t-183\r\n', 'a/g:\t-16176\t-2184\t2428\t55\t-63\t-250\r\n', 'a/g:\t-16232\t-2172\t2488\t53\t-57\t-266\r\n', 'a/g:\t-16300\t-2088\t2592\t-43\t-29\t-228\r\n', 'a/g:\t-16204\t-2168\t2596\t-65\t9\t-175\r\n', 'a/g:\t-16200\t-2076\t2392\t-123\t60\t-94\r\n', 'a/g:\t-16204\t-2120\t2524\t-165\t75\t-143\r\n', 'a/g:\t-16112\t-2068\t2540\t-78\t38\t-141\r\n', 'a/g:\t-16180\t-2084\t2484\t-122\t30\t-140\r\n', 'a/g:\t-16156\t-2128\t2468\t-55\t24\t-141\r\n', 'a/g:\t-16232\t-2180\t2592\t-83\t26\t-163\r\n', 'a/g:\t-16108\t-1992\t2420\t-33\t38\t-191\r\n', 'a/g:\t-16200\t-2088\t2540\t-15\t18\t-199\r\n', 'a/g:\t-16192\t-2056\t2500\t-38\t37\t-179\r\n', 'a/g:\t-16240\t-2152\t2484\t-43\t30\t-192\r\n', 'a/g:\t-16156\t-2072\t2628\t-71\t44\t-164\r\n', 'a/g:\t-16148\t-2112\t2412\t-36\t36\t-195\r\n', 'a/g:\t-16208\t-2160\t2436\t60\t36\t-168\r\n', 'a/g:\t-16264\t-2104\t2456\t-57\t14\t-178\r\n', 'a/g:\t-16208\t-2084\t2548\t-21\t46\t-178\r\n', 'a/g:\t-16216\t-2048\t2540\t-152\t48\t-129\r\n', 'a/g:\t-16332\t-2124\t2616\t-122\t19\t-169\r\n', 'a/g:\t-16284\t-2088\t2620\t-100\t17\t-152\r\n', 'a/g:\t-16144\t-2108\t2544\t-37\t43\t-180\r\n', 'a/g:\t-16252\t-2092\t2464\t-64\t14\t-187\r\n', 'a/g:\t-16336\t-2132\t2624\t-88\t12\t-192\r\n', 'a/g:\t-16252\t-2080\t2448\t-97\t16\t-147\r\n', 'a/g:\t-16196\t-2204\t2520\t-163\t41\t-105\r\n', 'a/g:\t-16180\t-2104\t2564\t-56\t51\t-128\r\n', 'a/g:\t-16172\t-2148\t2532\t-110\t61-142\r\n', 'a/g:\t-16204\t-2156\t2488\t-46\t5\t-188\r\n', 'a/g:\t-16144\t-2068\t2496\t-25\t20\t-196\r\n', 'a/g:\t-16264\t-2108\t2468\t-55\t48\t-180\r\n', 'a/g:\t-16200\t-2020\t2476\t-71\t30\t-160\r\n', 'a/g:\t-16184\t-2088\t2500\t-82\t30\t-205\r\n', 'a/g:\t-16300\t-2148\t2600\t-68\t51\t-175\r\n', 'a/g:\t-16164\t-2056\t2552\t-73\t40\t-171\r\n', 'a/g:\t-16180\t-1996\t2592\t-93\t63\t-146\r\n', 'a/g:\t-16224\t-2140\t2516\t-87\t43\t-103\r\n', 'a/g:\t-16128\t-2128\t2540\t-105\t23\t-182\r\n', 'a/g:\t-16176\t-2164\t2504\t-146\t44\t-126\r\n', 'a/g:\t-16108\t-2104\t2548\t-167\t42\t-152\r\n', 'a/g:\t-16172\t-2152\t2508\t91\t-24\t-225\r\n', 'a/g:\t-16208\t-2104\t2460\t-92\t-13\t-199\r\n', 'a/g:\t-16164\t-2136\t2692\t-39\t-2\t-181\r\n', 'a/g:\t-16156\t-2028\t2416\t-96\t42\t-150\r\n', 'a/g:\t-16176\t-2060\t2468\t-45\t27\t-150\r\n']
RS=[]
LS=[]
def parse(data):
	for entry in data:
		
		
		sdata=entry.split(',')
		if len(sdata)>1:
			RS.append(float(sdata[0]))
			LS.append(float(sdata[1]))
		else:
			print 'bad point'
			RS.append(0)
			LS.append(0)
	return RS,LS


def plotdata(timed,RS,LS):

	plt.plot(time,RS)
	plt.plot(time,LS)
	plt.show()


LS,RS=parse(data)

plotdata(timed,LS,RS)



import csv

ofile  = open('data.csv', "wb")
writer = csv.writer(ofile, delimiter=',')

for i in range(len(timed)):
    writer.writerow([time[i],speed_sel[i],RS[i],LS[i]])

ofile.close()


