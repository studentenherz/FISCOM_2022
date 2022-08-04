import numpy as np
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

ff = 3
trail = 80

def upadte_line(i, x, y, line, spring, ball):
	line.set_data(x[max(0, ff*(i - trail)):ff * i], y[max(0, ff*(i - trail)):ff * i])
	spring.set_data([0, x[ff * i]], [0, y[ff * i]])
	ball.set_data(x[ff * i], y[ff * i])
	return line, spring

fig, ax = plt.subplots()

data = np.loadtxt('3.dat')
x = data[:,1]
y = data[:,2]

line, = plt.plot(x, y)
spring, = plt.plot([0, x[-1]], [0, y[-1]], c='#AAA')
ball, = plt.plot(x[-1], y[-1], 'o', markersize=10, c='k')

anim = FuncAnimation(fig, upadte_line, len(x) // ff, fargs=(x, y, line, spring, ball), interval=1)
ax.set_aspect('equal')

plt.show()