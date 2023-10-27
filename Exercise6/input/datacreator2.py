import sys
import numpy as np

nx = 102
hzero = np.zeros(nx)
eta = np.zeros(nx)

for k in range(1, nx) :
    hzero[k] = -20. + 10. * k / (nx - 1)

hzero[0] = hzero[1]
hzero[nx - 1] = hzero[nx - 2]

pit_st = int((nx - 1) / 2 - 5)
pit_ed = int((nx - 1) / 2 + 5)
for k in range(pit_st, pit_ed + 1) :
    hzero[k] = -14

for k in range(nx) : 
    eta[k] = -min(0.0, hzero[k])

for k in range(2, 21) : 
    eta[k] += 1.0

hz = np.array2string(hzero, separator=',').replace('[', '').replace(']', '')
et = np.array2string(eta, separator=',').replace('[', '').replace(']', '')

file = open(sys.path[0] + "\\scenario2.dat", 'w')
file.write("hzero\n")
file.write(hz)
file.write("\n\n")
file.write("eta\n")
file.write(et)
file.write("\n\n")
file.close()