import numpy as np
from scipy.integrate import solve_ivp

'''To calculate the derivative(change) of velocity and acceleration over time '''
def rates(t, f):
    x, y, z, vx, vy, vz = f
    r = np.linalg.norm([x, y, z])
    #acceleration in x , y ,z directions 
    ax = -mu * x / r**3                
    ay = -mu * y / r**3
    az = -mu * z / r**3
    #output 
    return [vx, vy, vz, ax, ay, az]

def output(t, y):
    # y contains 6 elements ((x,y,z vx,vy,vz) * number of time steps ) 
    r = np.linalg.norm(y[:, :3], axis=1)         # it's selecting the first three elements of each row in y and get their norm put them in an array r ([r1,r2,r3]) 
    imax = np.argmax(r)                          # This line finds the index of the maximum value in the array r
    imin = np.argmin(r)                          # finds the index of the minimum value 
    rmax = r[imax]                               # the maximum value 
    rmin = r[imin]                               # the mimimum value 
    v_at_rmax = np.linalg.norm(y[imax, 3:6])
    v_at_rmin = np.linalg.norm(y[imin, 3:6])
    

    print("\n\n––––––––––––––––––––––––––––––––––––––--–––––––––––––––––––––––\n")
    print("\n Earth Orbit")
    #print(" {}".format(datetime.now()))
    print("\n The initial position is [{}, {}, {}] (km).".format(*r0))
    print(" Magnitude = {} km\n".format(np.linalg.norm(r0)))
    print("\n The initial velocity is [{}, {}, {}] (km/s).".format(*v0))
    print(" Magnitude = {} km/s\n".format(np.linalg.norm(v0)))
    print("\n Initial time = {} h.\n Final time = {} h.\n".format(t[0]/3600, t[-1]/3600))
    print("\n The minimum altitude is {} km at time = {} h.".format(rmin-R, t[imin]/3600))
    print(" The speed at that point is {} km/s.\n".format(v_at_rmin))
    print("\n The maximum altitude is {} km at time = {} h.".format(rmax-R, t[imax]/3600))
    print(" The speed at that point is {} km/s\n".format(v_at_rmax))
    print("\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n\n")

# Constants and input data
hours = 3600
G = 6.6742e-20
m1 = 5.974e24
R = 6378
m2 = 1000
r0 = np.array([8000, 0, 6000])
v0 = np.array([0, 7, 0])
t0 = 0
tf = 4 * hours
mu = G * (m1 + m2)
y0 = np.concatenate([r0, v0])

# Solve using solve_ivp
sol = solve_ivp(rates, [t0, tf], y0, method='RK45', t_eval=np.linspace(t0, tf, 1000))

# Output the results
output(sol.t, sol.y)

# Plot the orbit
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(sol.y[0], sol.y[1], sol.y[2], 'k')
ax.plot([0, r0[0]], [0, r0[1]], [0, r0[2]], 'r--')
ax.text(sol.y[0, 0], sol.y[1, 0], sol.y[2, 0], 'o')
ax.text(sol.y[0, -1], sol.y[1, -1], sol.y[2, -1], 'f')
ax.set_xlabel('X (km)')
ax.set_ylabel('Y (km)')
ax.set_zlabel('Z (km)')
ax.set_title('Orbit')
plt.show()
