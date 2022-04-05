import matplotlib.pyplot as plt

import numpy as np
import pandas as pd

headers = ['K_Random']
kRandom = pd.read_csv('KRandom_quality.csv', names=headers)
y = kRandom.K_Random

x = np.arange(0,1000,1)

a = np.empty(1000)
a.fill(6110)

plt.subplot(2,1,1)
ax = plt.gca()
ax.set_ylim([0, 46000])
plt.plot(x, y, label = 'kRandom')
plt.plot(x, a, label = 'optimal solution')
plt.legend()
plt.xscale("log")
plt.xlabel('number of repeats')
plt.ylabel('objective function')
plt.title('quality of KRandom ch130.tsp solution - mean of k repeats ascending linearly')

plt.subplot(2,1,2)
plt.title('quality of solution compared to optimal solution')
ax = plt.gca()
plt.plot(x, (y-a)/a)
plt.xscale("log")
plt.tight_layout()
plt.show()
