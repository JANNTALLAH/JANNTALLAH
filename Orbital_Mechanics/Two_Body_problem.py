import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Define the function to compute the derivatives of the state vector
def f(t, y):
    G = 6.67259e-20  # Universal gravitational constant (km^3/kg/s^2)
    # Extracting the positions and velocities of bodies 1 and 2 from the state vector y
    R1 = y[:3]
    R2 = y[3:6]
    V1 = y[6:9]
    V2 = y[9:]

    # Calculating the relative position vector
    r_rel = R2 - R1
    
    # Calculating the magnitude of the relative position vector
    r_rel_mag = np.linalg.norm(r_rel)
    
    # Calculating the acceleration of body 1 due to gravitational force from body 2
    a1 = G * m2 / (r_rel_mag ** 3) * r_rel
    
    # Calculating the acceleration of body 2 due to gravitational force from body 1
    a2 = -G * m1 / (r_rel_mag ** 3) * r_rel
    
    # Return the derivatives
    return np.concatenate((V1, V2, a1, a2))

# Define initial conditions
m1 = 1.0e26  # mass of body 1 (kg)
m2 = 1.0e26  # mass of body 2 (kg)
R1_0 = np.array([0, 0, 0])   # initial position (km) of body 1
R2_0 = np.array([3000, 0, 0])   # initial position (km) of body 2
V1_0 = np.array([10, 20, 30])   # initial velocity (km/s) of body 1
V2_0 = np.array([0, 40, 0])     # initial velocity (km/s) of body 2
y0 = np.concatenate((R1_0, R2_0, V1_0, V2_0))  # initial state vector

# Define time span
t_span = (0, 480)  # initial and final time (s)

# Use RKF4(5) method to integrate the equations of motion
sol = solve_ivp(f, t_span, y0, method='RK45', t_eval=np.linspace(0, 480, 1000))

# Extract the solution
t = sol.t
y = sol.y

# Extract the positions and velocities of bodies 1 and 2
R1 = y[:3]
R2 = y[3:6]

# Plot the motion of mass m1 and mass m2 relative to the inertial frame
plt.figure(figsize=(10, 6))
plt.plot(R1[0], R1[1], label='m1')
plt.plot(R2[0], R2[1], label='m2')
plt.xlabel('X (km)')
plt.ylabel('Y (km)')
plt.title('Motion of Mass m1 and Mass m2 Relative to the Inertial Frame')
plt.legend()
plt.grid(True)
plt.show()

# Calculate the motion of mass m2 and the center of mass G relative to mass m1
RG = (m1 * R1 + m2 * R2) / (m1 + m2)
R2_rel = R2 - R1
GRG_rel = RG - R1

# Plot the motion of mass m2 and G relative to m1
plt.figure(figsize=(10, 6))
plt.plot(R2_rel[0], R2_rel[1], label='m2 relative to m1')
plt.plot(GRG_rel[0], GRG_rel[1], label='G relative to m1')
plt.xlabel('X (km)')
plt.ylabel('Y (km)')
plt.title('Motion of Mass m2 and G Relative to Mass m1')
plt.legend()
plt.grid(True)
plt.show()

# Calculate the motion of m1 and m2 relative to the center of mass G
m1_G_rel = R1 - RG
m2_G_rel = R2 - RG

# Plot the motion of m1 and m2 relative to the center of mass G
plt.figure(figsize=(10, 6))
plt.plot(m1_G_rel[0], m1_G_rel[1], label='m1 relative to G')
plt.plot(m2_G_rel[0], m2_G_rel[1], label='m2 relative to G')
plt.xlabel('X (km)')
plt.ylabel('Y (km)')
plt.title('Motion of Mass m1 and Mass m2 Relative to the Center of Mass G')
plt.legend()
plt.grid(True)
plt.show()

