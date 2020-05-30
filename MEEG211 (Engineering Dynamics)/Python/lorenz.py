from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from scipy.integrate import odeint
import numpy as np

sigma , rho , b = 10 ,30 ,2
fig = plt.figure()
ax = fig.gca(projection='3d')

def  Lorenz (v , t ):
    return ([ sigma*( v[1] - v[0]) , rho*v[0] - v[1] - v[0]* v[2] ,v[0]* v[1] - b * v[2]])

def OrbitLorenz( IC ,n , T ):
    t = np.linspace (0 ,T , n +1)
    for y0 in IC:
        values = odeint (Lorenz , y0 , t )
        ax.plot( values [: ,0] , values [: ,1] , values [: ,2] , label = str ( y0 ))
        
OrbitLorenz ([[20 ,0 ,0] ,[10 ,0 ,0] ,[0.1 ,0 ,0]] ,5000 ,10)
ax.legend()
plt.savefig('Lorenz.pdf')
plt.show()
