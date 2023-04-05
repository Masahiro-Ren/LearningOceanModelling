from mpl_toolkits.axisartist.axislines import AxesZero
import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure('Coriolis')

# set x, y origin
ax = fig.add_subplot(axes_class = AxesZero)
for direction in ["xzero", "yzero"] :
   ax.axis[direction].set_visible(True)
for direction in ["left", "right", "bottom", "top"]:
   ax.axis[direction].set_visible(False)

coord = np.loadtxt(sys.path[0] + '\\coriolis1.dat', delimiter=',').T
x = coord[0]
y = coord[1]

ax.plot(x, y, color='black')
ax.set_xlim(-15, 15)
ax.set_ylim(-15, 15)


plt.show()