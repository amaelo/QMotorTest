import Calculation as clc
import sys


# folder = 'C:/Users/201011805/Documents/perso'
# folder = "/home/kama/applications/_myAppli/QMotorTest/recorders/"
# rec1path = "rec 30.txt"
# file1Path = os.path.join(folder,rec1path)

file1Path = sys.argv[1]

# file1Path = "C:/Users/ama/Documents/qt-projects/QMotorTest/recorders/toto2"

data1 = clc.getCalculations(file1Path)

speedEngine1 = data1[0]

power_hp1 = data1[1]

lambda1 = data1[2]

speedEngine1.pop(0)

lambda1.pop(0)


res= ""
speedEngine2 = []

for i in speedEngine1:
    res += str(i) + ";"

res = res[:-1]   
res += "_"

n = 0

for i in power_hp1:
    res += str(i) + ";"
    if i > 0: speedEngine2.append(speedEngine1[n])
    n += 1
    
res = res[:-1]   
res += "_"

n2 = 0

for i in lambda1:
    if n2 < n: res += str(i) + ";"
    else : break
    n2 += 1
    
   

print(res[:-1])
