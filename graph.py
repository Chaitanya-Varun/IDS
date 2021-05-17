import numpy as np
import matplotlib.pyplot as plt
import math

days,S,I,R = np.loadtxt('data.txt',delimiter=',',unpack=True)
plt.plot(days[:],S[:],label='Susceptible')
plt.plot(days[:],I[:],label='Infected')
plt.plot(days[:],R[:],label='Recovered')

plt.xlabel('$Days$');plt.ylabel('$People$')
plt.legend(loc='best');plt.grid()
plt.show()
