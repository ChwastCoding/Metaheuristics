import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import pandas as pd

headers = ['kRandom', 'extnn']
kRandom_extnn = pd.read_csv('KRandom_ExtNN2.csv', names=headers)

kRandom = kRandom_extnn.kRandom
extnn = kRandom_extnn.extnn

print(stats.wilcoxon(kRandom_extnn.kRandom, kRandom_extnn.extnn))

x = np.arange(10,210,1)

plt.subplot(2,1,1)
plt.plot(x, kRandom, label = 'kRandom')
plt.plot(x, extnn, label = 'extendedNearestNeighbour')
plt.legend()
plt.xlabel('instance number')
plt.ylabel('objective function')
plt.title('kRandom and extended nearest neighbour')

plt.subplot(2,1,2)
plt.plot(x, (kRandom-extnn)/extnn)
plt.show()