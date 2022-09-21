from tkinter import W
import numpy as np
import matplotlib.pyplot as plt;
import matplotlib.animation as animation
import sys

X = np.arange(0, 1000, 1)

def draw_sinwave(_amplitude, _lambda, _period, _X) :
    fig, ax = plt.subplots()
    ax.set_title('Sin wave Animation')
    ax.set_xlim(0, 500)
    ax.set_xlabel('Distance')
    ax.set_ylim(-2, 2)
    ax.set_ylabel('Surface Elevation')
    
    init_y = _amplitude * np.sin( 2 * np.pi * _X / _lambda )
    line, = ax.plot(_X, init_y)

    def update(time) :
        Y = _amplitude * np.sin( 2 * np.pi * (_X / _lambda - time / _period) )
        line.set_data(_X, Y)
        return line
    
    ani = animation.FuncAnimation(fig, update, frames=100, interval=50)
    ani.save(sys.path[0] + '\\wave.gif', dpi=300, writer='pillow')
    plt.show()

def draw_waveinterference(_amplitude1, _lambda1, _period1, _amplitude2, _lambda2, _period2, _X) :
    fig, ax = plt.subplots(3,1, figsize=(6.5, 6))
    fig.tight_layout()
    for i in range(3) :
        ax[i].set_title('Wave' + str(i + 1))
        ax[i].set_xlim(0, 1000)
        ax[i].set_ylim(-2, 2)

    ax[1].set_ylabel("Surface Elevation")
    y1 = _amplitude1 * np.sin( 2 * np.pi * _X / _lambda1 )
    y2 = _amplitude2 * np.sin( 2 * np.pi * _X / _lambda2 )
    y3 = _amplitude1 * ( np.sin( 2 * np.pi * _X / _lambda1 ) + np.sin( 2 * np.pi * _X / _lambda2 ) )
    
    line1, = ax[0].plot(_X, y1)
    line2, = ax[1].plot(_X, y2)
    line3, = ax[2].plot(_X, y3)

    def update(time) :
        Y1 = _amplitude1 * np.sin( 2 * np.pi * (_X / _lambda1 - time / _period1))
        Y2 = _amplitude2 * np.sin( 2 * np.pi * (_X / _lambda2 - time / _period2))
        Y3 = _amplitude1 * ( np.sin( 2 * np.pi * (_X / _lambda1 - time / _period1) ) + np.sin( 2 * np.pi * (_X / _lambda2 - time / _period2) ))
        line1.set_data(_X, Y1)
        line2.set_data(_X, Y2)
        line3.set_data(_X, Y3)
        return line1, line2, line3
    
    ani = animation.FuncAnimation(fig, update, frames=100, interval=50)
    ani.save(sys.path[0] + '\\waves.gif', dpi=300, writer='pillow')
    plt.xlabel("Distance")
    plt.show()

def main() : 
    draw_waveinterference(1, 100, 50, 1, 90, 60, X)

if __name__ == "__main__" :
    main()