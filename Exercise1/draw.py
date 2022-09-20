from cProfile import label
import numpy as np
import matplotlib.pyplot as plt
import sys

plt.figure("Decay Problem")

res_explicit = np.loadtxt(sys.path[0] + '\\res_explicit.txt').T
res_implicit = np.loadtxt(sys.path[0] + '\\res_implicit.txt').T
res_hybrid = np.loadtxt(sys.path[0] + '\\res_hybrid.txt').T
analytical = np.loadtxt(sys.path[0] + '\\res_analytical.txt').T

time = np.arange(0, 16, 1)
plt.plot(time, analytical, color='black', linestyle='dashed')
plt.plot(time, res_explicit, color='red', label='explicit')
plt.plot(time, res_implicit, color='blue', label='implicit')
plt.plot(time, res_hybrid, color='green', label='hybrid')

plt.legend()
plt.title('Decay Problem')
plt.xlabel('Time(hours)')
plt.ylabel('Concentration (100%)')
plt.ylim(0, 100)
plt.xlim(0, 15)
plt.xticks(time)
plt.grid(True)

plt.show()
