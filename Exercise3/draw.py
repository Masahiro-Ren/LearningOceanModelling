from turtle import color
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.colors import ListedColormap, BoundaryNorm
import sys

plt.figure("Oscillations of a buoyant object with friction")

obj_path = np.loadtxt(sys.path[0] + "\\buoyant-fric.dat").T
time = np.arange(0, 1800, 1)

# code for draw different color in single line
# select how to colr
cmap = ListedColormap(['r', 'b'])
norm = BoundaryNorm([-100.0, -50.0], cmap.N)
# get segments
points = np.array([time, obj_path]).T.reshape(-1, 1, 2)
segments = np.hstack([points[:-1], points[1:]])
# make line collection
lc = LineCollection(segments, cmap=cmap, norm=norm)
lc.set_array(obj_path)
plt.gca().add_collection(lc)
# code end

plt.axhline(-50.0, color='black')

plt.legend()
plt.title('Oscilliations fo a buoyant object with friction')
plt.xlabel('Time(minutes)')
plt.ylabel('z(m)')
plt.ylim(-100, 0)
plt.xticks([0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800], ['0','','','10','','','20','','','30'])
plt.show()