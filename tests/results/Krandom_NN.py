import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import pandas as pd

headers = ['kRandom', 'nn']
kRandom_extnn = pd.read_csv('KRandom_NN.csv', names=headers)

kRandom = kRandom_extnn.kRandom
extnn = kRandom_extnn.nn

print(stats.wilcoxon(kRandom_extnn.kRandom, kRandom_extnn.nn))

x = np.arange(0,1000,1)

plt.plot(x, kRandom, label = 'kRandom')
plt.plot(x, extnn, label = 'NearestNeighbour')
plt.legend()
plt.xlabel('instance number size 550')
plt.ylabel('objective function')
plt.title('kRandom and nearest neighbour')
plt.show()