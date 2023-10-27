import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as Animation
import sys

fig, ax = plt.subplots()
ax.set_ylim(5, 15)
ax.set_xlim(0, 103)
ax.set_ylabel("Sea Level (meter)")
ax.set_xlabel("Channel Length (1000m)")
ax.set_xticklabels([])
ax.set_title("Long Waves in a Channel")

waves = np.loadtxt(sys.path[0] + "\\dam_break.dat", delimiter=',')
x = np.arange(0, 102, 1)


wave, = ax.plot(x, waves[0], color="blue", linewidth=0.5)


def update(tick) :
    wave.set_data(x, waves[tick])
    return wave

ani = Animation.FuncAnimation(fig, update, frames=200, interval=30)
# Save animation to gif
ani.save(sys.path[0] + "\\dam_break.gif", dpi=300, writer='pillow')

plt.show()