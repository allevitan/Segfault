import matplotlib.pyplot as plt
import csv


time=[]
speed=[]
RS=[]
LS=[]
speed_steps=[]
LS_avg=[]
RS_avg=[]
with open('raw_data.csv', 'rb') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	for row in spamreader:
		# print len(row)
		if len(row) ==4:
			time.append(float(row[0]))
			speed.append(float(row[1]))
			RS.append(float(row[2]))
			LS.append(float(row[3]))


i=0
j=0
go=1
print len(speed)
cur_speed=0
while cur_speed < 38:
	cur_speed=speed[i]
	print cur_speed
	j=0
	temp_RS=[]
	temp_LS=[]
	print i+j
	while speed[i+j]==cur_speed:
		temp_RS.append(RS[i+j])
		temp_LS.append(LS[i+j])
		# print 'j',j
		j=j+1


	speed_steps.append(cur_speed)
	# print temp_RS
	RS_avg.append(sum(temp_RS)/len(temp_RS))
	LS_avg.append(sum(temp_LS)/len(temp_LS))
	i=i+j
	print 'i',i

print speed_steps
print RS_avg


# plt.plot(time,RS)
# plt.plot(time,LS)
# plt.show()

# plt.plot(speed,RS,'x')
# plt.plot(speed,LS,'x')
# plt.show()

plt.plot(speed_steps,RS_avg, 'g')
plt.plot(speed_steps,LS_avg,'r')
plt.show()