from mpl_toolkits.axisartist.axislines import AxesZero
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.animation as Animtion
import sys

fig = plt.figure('Coriolis')

# set x, y axis into center
ax = fig.add_subplot(axes_class = AxesZero)
for direction in ["xzero", "yzero"] :
   ax.axis[direction].set_visible(True)
for direction in ["left", "right", "bottom", "top"]:
   ax.axis[direction].set_visible(False)
# Draw a cirle background
circle = patches.Circle((0, 0), radius=20, color='deepskyblue', fill=True)
ax.add_patch(circle)
# Read data
coord = np.loadtxt(sys.path[0] + '\\coriolis1.dat', delimiter=',').T
x = coord[0]
y = coord[1]


ax.plot(x, y, color='white', linewidth=0.5)
ax.set_xlim(-25, 25)
ax.set_ylim(-25, 25)
ax.axis('equal')

# Animation part

dt = 24.0 * 3600.0 / 200.0
freq = -2 * np.pi / (24 * 3600)
# init star mark position
star = ax.scatter(20, 0, s=320, marker='*', color='gold', zorder=3)
# init point mark position
point = ax.scatter(x[0], y[0], s=200, marker='.', color='gold', zorder=3)

def update(tick) :
   theta =  dt * tick * freq     
   xx = 20 * np.cos(theta)
   yy = 20 * np.sin(theta)   
   star.set_offsets((xx, yy))
   point.set_offsets((x[tick], y[tick]))
   return star


ani = Animtion.FuncAnimation(fig, update, frames=200, interval=30)
ani.save(sys.path[0] + '\\coriolis.gif', dpi=300, writer='pillow')
# Animation part end

# plt.axis('equal') # makes x and y have the same length
plt.show()