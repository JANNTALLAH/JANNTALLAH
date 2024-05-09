import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

'''3 BODY PEOBLEM ''' 
'''Define the function to compute the derivatives(the change) of the state vector''' 
def rates(t, y):
    
    G = 6.67259e-20
    m1 = 1.e29             # mass body 1 
    m2 = 1.e29             # mas body 2 
    m3 = 1.e29             # mas body 3
    # Extracting the positions and velocities of bodies 1 and 2 from the state vector y
    X1 = y[0]
    Y1 = y[1]
    X2 = y[2]
    Y2 = y[3]
    X3 = y[4]
    Y3 = y[5]
    VX1 = y[6]
    VY1 = y[7]
    VX2 = y[8]
    VY2 = y[9]
    VX3 = y[10]
    VY3 = y[11]

    # Calculating the relative position vector
    R12 = np.linalg.norm([X2-X1 , Y2-Y1])**3 
    R13 = np.linalg.norm([X3-X1 , Y3-Y1])**3 
    R23 = np.linalg.norm([X3-X2 , Y3-Y2])**3 
    
    # Calculating the acceleration of body 1,2,3 due to gravitational force from each other
    AX1 = G*m2*(X2 - X1)/R12 + G*m3*(X3 - X1)/R13
    AY1 = G*m2*(Y2 - Y1)/R12 + G*m3*(Y3 - Y1)/R13
    AX2 = G*m1*(X1 - X2)/R12 + G*m3*(X3 - X2)/R23
    AY2 = G*m1*(Y1 - Y2)/R12 + G*m3*(Y3 - Y2)/R23
    AX3 = G*m1*(X1 - X3)/R13 + G*m2*(X2 - X3)/R23
    AY3 = G*m1*(Y1 - Y3)/R13 + G*m2*(Y2 - Y3)/R23
    
    # Return the derivatives
    return [VX1,VY1,VX2,VY2,VX3,VY3,AX1,AY1,AX2,AY2,AX3,AY3]



'''initial condition ''' 
m1 = 1.e29
m2 = 1.e29
m3 = 1.e29
m = m1 + m2 + m3
t_initial = 0   
t_final = 67000 

X1 = 0              # initial position (km) of body 1 in x dir 
Y1 = 0              # initial position (km) of body 1 in y dir
X2 =  300000        # initial position (km) of body 2 in x dir 
Y2 = 0              # initial position (km) of body 2 in y dir
X3 = 2*X2         # initial position (km) of body 3 in x dir 
Y3 = 0              # initial position (km) of body 3 in y dir

VX1 = 0             # initial velocity (km/s) of body 1 in x dir
VY1 = 0             # initial velocity (km/s) of body 1 in y dir
VX2 = 250           # initial velocity (km/s) of body 2 in x dir
VY2 = 250           # initial velocity (km/s) of body 2 in y dir
VX3 = 0             # initial velocity (km/s) of body 3 in x dir
VY3 = 0             # initial velocity (km/s) of body 3 in y dir
y0 = [X1 ,Y1 ,X2 ,Y2 ,X3 ,Y3 ,VX1 ,VY1 ,VX2 ,VY2 ,VX3 ,VY3]  # initial state vector


'''solve the ODE''' 
sol = solve_ivp(rates, [t_initial, t_final], y0, method='RK45',t_eval=np.linspace(t_initial, t_final, 100))

''' Extract the solution ''' 
t = sol.t
y = sol.y

'''undate the initial conditioins'''
X1 = y[0]
Y1 = y[1]
X2 = y[2]
Y2 = y[3]
X3 = y[4]
Y3 = y[5]
'''locate the center of mass at each time step''' 
XG = np.zeros_like(t)          # to make sure they has the same length and there is no index error
YG = np.zeros_like(t)
for i, ti in enumerate(t):
    XG[i] = (m1 * X1[i] + m2 * X2[i] + m3 * X3[i]) / m
    YG[i] = (m1 * Y1[i] + m2 * Y2[i] + m3 * Y3[i]) / m


'''Coordinates of each particle relative to the center of mass''' 
X1G = X1 - XG
Y1G = Y1 - YG
X2G = X2 - XG
Y2G = Y2 - YG
X3G = X3 - XG
Y3G = Y3 - YG

'''Plot results''' 
plt.figure(figsize=(10,5))
plt.plot(XG,YG,'--',label='Center of mass')
plt.plot(X1,Y1,'r',label='Body 1')
plt.plot(X2,Y2,'g',label='Body 2')
plt.plot(X3,Y3,'b',label='Body 3')
plt.xlabel('X IN KM')
plt.ylabel('Y IN KM')
plt.title('Motion relative to the inertial frame O')
plt.grid(True)
plt.legend()
plt.axis('equal')
plt.show()

'''second plot''' 
plt.figure(figsize=(10,5))
plt.plot(X1G, Y1G, 'r', label='Body 1')
plt.plot(X2G, Y2G, '--g', label='Body 2')
plt.plot(X3G, Y3G, 'b', label='Body 3')
plt.xlabel('X (km)')
plt.ylabel('Y (km)')
plt.title('Motion relative to the center of mass')
plt.grid(True)
plt.legend()
plt.axis('equal')
plt.show()