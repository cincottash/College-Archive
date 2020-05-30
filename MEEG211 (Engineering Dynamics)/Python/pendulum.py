import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint


def pendulum(X, t):
    return [X[1], - np.sin(X[0])]

t = np.linspace(0, 5 * np.pi, 1000)

theta_init = np.linspace(0, np.pi, 20)

plt.figure(figsize=(6, 6))

for theta0 in theta_init:
    Xvalues = odeint(pendulum, (theta0, 0), t)
    plt.plot(Xvalues[:,0], Xvalues[:,1])

plt.xlabel(u'$\\theta$', fontsize=26)
plt.ylabel(u'$\dot{\\theta}$', fontsize=26)
plt.axis('equal')
plt.xlim(-np.pi, np.pi)
plt.ylim(-2, 2)
plt.title('phase diagram')
plt.tight_layout()
plt.show()


