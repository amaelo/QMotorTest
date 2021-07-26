import os
import matplotlib.pyplot as plt
import Calculation as clc


# folder = 'C:/Users/201011805/Documents/perso'
# folder = "/home/kama/applications/_myAppli/QMotorTest/recorders/"
folder = "C:/Users/ama/Documents/qt-projects/QMotorTest/recorders"
rec1path = "toto12"
rec2path = "toto11"
rec3path = "toto10"
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
ax.plot(speedEngine1, power_hp1, color='tab:red', linewidth=3)
ax.plot(speedEngine2, power_hp2, color='tab:blue', linewidth=3)
ax.plot(speedEngine3, power_hp3, color='tab:green', linewidth=3)



ax.set(xlabel='rpm', ylabel='puissance (ch)',
       title=rec1path)

ax.minorticks_on()
plt.grid(which='major', color='grey', linewidth=0.7)
plt.grid(which='minor', color='blue', linewidth=0.2)

ax2 = ax.twinx()
ax2.plot(speedEngine1, lambda1, color='tab:red', linewidth=0.5)
ax2.plot(speedEngine2, lambda2, color='tab:blue', linewidth=0.5)
ax2.plot(speedEngine3, lambda3, color='tab:green', linewidth=0.5)

ax2.set_ylim([0, 1])

# fig.savefig("test.png")
plt.show()

res= ""


# for i in speedEngine1:
#     res += str(i) + ";"

# res = res[:-1]   
# res += "_"

# for i in power_hp1:
#     res += str(i) + ";"
    

# print(res[:-1])
