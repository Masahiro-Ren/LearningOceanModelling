import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as Animation
import sys

# 1 for island; 2 for hillside
MODE=1
DATA_PATH = ""
# create a figuer object
fig, ax = plt.subplots()

nx = 102
hzero = np.zeros(nx)

if (MODE == 1) :
    # Init island data
    for k in range(1, 52) :
        hzero[k] = 10.5 * k / 51.

    for k in range(52, nx) :
        k2 = nx - k
        hzero[k] = 10.5 * k2 / 51.
    hzero[0] = 0.

    DATA_PATH = sys.path[0] + "\\island.dat"
    # set up y limit
    ax.set_ylim(5, 15)
else :
    # Init hillside data
    for k in range(1, nx) :
        hzero[k] = 20. - 10. * k / (nx - 1)

    hzero[0] = hzero[1]
    hzero[nx - 1] = hzero[nx - 2]
    pit_st = int((nx - 1) / 2 - 5)
    pit_ed = int((nx - 1) / 2 + 5)
    for k in range(pit_st, pit_ed + 1) :
        hzero[k] = 14
    DATA_PATH = sys.path[0] + "\\hillside.dat"

    ax.set_ylim(10, 25)

ax.set_xlim(0, 100)
ax.set_ylabel("Sea Level (meter)")
ax.set_xlabel("Channel Length (1000m)")
ax.set_xticklabels([])
ax.set_title("Flood")

waves = np.loadtxt(DATA_PATH, delimiter=',')
x = np.arange(0, 102, 1)

ax.plot(x, hzero, color="black", linewidth=0.5)

wave, = ax.plot(x, waves[0], color="blue", linewidth=0.5)


def update(tick) :
    wave.set_data(x, waves[tick])
    return wave

ani = Animation.FuncAnimation(fig, update, frames=1000, interval=5)
# Save animation to gif
# ani.save(sys.path[0] + "\\island.gif", dpi=300, writer='pillow')

plt.show()