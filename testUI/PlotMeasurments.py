import os
import matplotlib.pyplot as plt
import Calculation as clc


# folder = 'C:/Users/201011805/Documents/perso'
folder = "/home/kama/applications/_myAppli/QMotorTest/recorders/"
rec1path = "rec 30.txt"
rec2path = "rec 31.txt"
rec3path = "rec 32.txt"

file1Path = os.path.join(folder,rec1path)
file2Path = os.path.join(folder,rec2path)
file3Path = os.path.join(folder,rec3path)

data1 = clc.getCalculations(file1Path)
data2 = clc.getCalculations(file2Path)
data3 = clc.getCalculations(file3Path)

speedEngine1 = data1[0]
speedEngine2 = data2[0]
speedEngine3 = data3[0]

power_hp1 = data1[1]
power_hp2 = data2[1]
power_hp3 = data3[1]

lambda1 = data1[2]
lambda2 = data2[2]
lambda3 = data3[2]

speedEngine1.pop(0)
speedEngine2.pop(0)
speedEngine3.pop(0)

lambda1.pop(0)
lambda2.pop(0)
lambda3.pop(0)

fig, ax = plt.subplots()
ax.plot(speedEngine1, power_hp1, color='tab:red')
ax.plot(speedEngine2, power_hp2, color='tab:blue')
ax.plot(speedEngine3, power_hp3, color='tab:green')



ax.set(xlabel='rpm', ylabel='puissance (ch)',
       title=rec1path)

ax.minorticks_on()
plt.grid(which='major', color='grey', linewidth=0.7)
plt.grid(which='minor', color='blue', linewidth=0.2)

ax2 = ax.twinx()
ax2.plot(speedEngine1, lambda1, color='tab:red')
ax2.plot(speedEngine1, lambda1, color='tab:blue')
ax2.plot(speedEngine1, lambda1, color='tab:green')

# fig.savefig("test.png")
plt.show()

res= ""


for i in speedEngine1:
    res += str(i) + ";"

res = res[:-1]   
res += "_"

for i in power_hp1:
    res += str(i) + ";"
    

print(res[:-1])
