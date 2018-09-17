# pysimplexnoise
Simplex noise for python, python bindings for SRombauts/SimplexNoise

## Installation 

```
git clone --recurse-submodules https://github.com/henriasv/pysimplexnoise.git
cd pysimplexnoise
pip3 install . 
```

## Basic usage 

```
octaves = 4 
frequency = 2.0 
amplitude = 2.0 
lacunarity = 2.0 
persistence=0.5

import numpy as np
import pysimplexnoise as psn
x = np.linspace(0, 10, 100)
y = np.linspace(0, 10, 100)

X, Y = np.meshgrid(x, y)
noise = psn.simplexnoise2d(X, Y)
fractalnoise = psn.fractalnoise2d(X, Y, octaves, frequency, amplitude, lacunarity, persistence)
import matplotlib.pyplot as plt
plt.subplot(121)
plt.pcolormesh(X, Y, noise)
plt.subplot(122)
plt.pcolormesh(X, Y, fractalnoise)
plt.show()
```

