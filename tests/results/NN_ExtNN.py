import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import pandas as pd

headers = ['nn', 'extnn']
nn_extnn = pd.read_csv('NN_ExtNN.csv', names=headers)

nn = nn_extnn.nn
extnn = nn_extnn.extnn

print(stats.wilcoxon(nn_extnn.nn, nn_extnn.extnn))

x = np.arange(0,1000,1)

plt.plot(x, nn, label = 'nearestNeighbour')
plt.plot(x, extnn, label = 'extendedNearestNeighbour')
plt.legend()
plt.xlabel('instantce number')
plt.ylabel('funkcja celu')
plt.show()



