import sys
import numpy as np

nx = 102
hzero = np.zeros(nx)
eta = np.zeros(nx)

for k in range(1, 52) :
    hzero[k] = 10. - 10.5 * k / 51.

for k in range(52, nx) :
    k2 = nx - k
    hzero[k] = 10. - 10.5 * k2 / 51.

hzero[0] = -10.
hzero[nx - 1] = -10.

for k in range(nx) : 
    eta[k] = -min(0.0, hzero[k])

for k in range(1, 21) : 
    eta[k] = 1.0

hz = np.array2string(hzero, separator=',').replace('[', '').replace(']', '')
et = np.array2string(eta, separator=',').replace('[', '').replace(']', '')

file = open(sys.path[0] + "\\scenario1.dat", 'w')
file.write("hzero\n")
file.write(hz)
file.write("\n\n")
file.write("eta\n")
file.write(et)
file.write("\n\n")
file.close()