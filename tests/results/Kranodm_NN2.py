import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import pandas as pd

headers = ['kRandom', 'nn']
kRandom_nn = pd.read_csv('KRandom_NN2.csv', names=headers)

kRandom = kRandom_nn.kRandom
nn = kRandom_nn.nn

headers2 = ['kRandom', 'ext_nn']
extnn = pd.read_csv('KRandom_ExtNN2.csv', names=headers2).ext_nn

print(stats.wilcoxon(kRandom_nn.kRandom, kRandom_nn.nn))

x = np.arange(10,210,1)

plt.subplot(2,1,1)
plt.plot(x, kRandom, label = 'kRandom')
plt.plot(x, nn, label = 'NearestNeighbour')
plt.legend()
plt.xlabel('instance number size 550')
plt.ylabel('objective function')
plt.title('kRandom and nearest neighbour')

plt.subplot(2,1,2)
plt.plot(x, (kRandom-extnn)/extnn, label = 'kRandom')
plt.plot(x, (nn-extnn)/extnn, label = 'NearestNeighbour')
plt.legend()
plt.show()