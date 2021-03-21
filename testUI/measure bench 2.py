import os
import matplotlib.pyplot as plt
import numpy

PI = 3.14159265
INERTIA = 0.806
TOPS = 2500
PERIM = 0.71
SAMPLE = 0.01
WINDOW_SIZE = 30
RATIO = 5


folder = 'C:/Users/ama/Documents/qt-projects/QMotorTest/recorders'
# folder = "/home/kama/applications/_myAppli/QMotorTest"
rec1path = "rec 16.txt"

file1path = os.path.join(folder,rec1path)

list1 = []
with open(file1path,mode='r') as f1:
    list1 = f1.readlines()

list1int = [int(v) for v in list1 ]

values = [int(v) for v in list1 if int(v) > 200 ]
time = numpy.arange(0, len(values), 1)
time_s = [val / 100 for val in time]
speed_kmh = [3.6 * (v / TOPS) * PERIM / SAMPLE for v in values]

speed_rps = [(v / TOPS) / SAMPLE for v in values]
speed_rpm = [v * 60 for v in speed_rps]
speed_rads = [v * 2 * PI for v in speed_rps]

##############################################################################################

speed_filt_max = []
speed_filt_min = []

for i in range(0, len(speed_rads)):
    window = speed_rads[i:i + WINDOW_SIZE]
    speed_filt_min.append(sum(window) / len(window))
    # speed_filt_min.append(min(window))
   
speed_rads.reverse()
for i in range(0, len(speed_rads)):
    window = speed_rads[i:i + WINDOW_SIZE]
    speed_filt_max.append(sum(window) / len(window))
    # speed_filt_max.append(max(window))

speed_filt_max.reverse()
speed_rads.reverse()
   
speed_avg = []
for i in range(0, len(speed_filt_max)):
    speed_avg.append((speed_filt_max[i] + speed_filt_min[i] ) / 2)

##############################################################################################

WINDOW_SIZE2 = 20

accel = []
for i in range(0, len(speed_avg) - 1):
    delta = (speed_avg[i + 1] - speed_avg[i]) / SAMPLE
    accel.append(delta)
 

accel_filt1 = []
for i in range(0, len(accel)):
    window = accel[i:i + WINDOW_SIZE2]
    accel_filt1.append(sum(window) / len(window))

accel_filt2 = []  
accel.reverse()
for i in range(0, len(accel)):
    window = accel[i:i + WINDOW_SIZE2]
    accel_filt2.append(sum(window) / len(window))

accel.reverse()
accel_filt2.reverse()

accel_avg = []
for i in range(0, len(accel_filt2)):
    accel_avg.append((accel_filt1[i] + accel_filt2[i] ) / 2)
    
##############################################################################################


torqueWheel_nm = [2 * val * INERTIA for val in accel_avg]
torqueEngine_nm = [val / RATIO for val in torqueWheel_nm]
power_kw = []

for i in range(0, len(torqueEngine_nm)):
    power_kw.append(torqueWheel_nm[i] * speed_avg[i] / 1000)

power_hp = [val / 0.736 for val in power_kw]

speedEngine_rpm = [val * RATIO * 60 / (2 * PI) for val in speed_avg]
correction_ramp_hp = [val * -0.0006 + 2 for val in speedEngine_rpm]

power_corr_hp = []
for i in range(0, len(correction_ramp_hp) - 1):
    power_corr_hp.append(power_hp[i] - correction_ramp_hp[i])
    
##############################################################################################

speedEngine_rpm.pop(0)
correction_ramp_hp.pop(0)

xValues = speedEngine_rpm
yValues = power_corr_hp
yValues2 = power_hp
yValues3 = correction_ramp_hp

fig, ax = plt.subplots()
ax.plot(xValues, yValues, color='tab:grey')
ax.plot(xValues, yValues2, color='tab:red')
ax.plot(xValues, yValues3, color='tab:green')


ax.set(xlabel='rpm', ylabel='puissance (ch)',
       title=rec1path)
ax.grid()

# fig.savefig("test.png")
plt.show()
    
