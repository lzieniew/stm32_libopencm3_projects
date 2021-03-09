# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from numpy import arange
from math import pi, sin, cos
import matplotlib.pyplot as plt

MAX_DAC_VALUE = 512
STEPS = 64

x_tab = arange(0, 2 * pi, 0.1)
traingle = []


counter = 0.
step = (MAX_DAC_VALUE - 1) / STEPS

for i in range(STEPS):
    counter += step
    print("{:10.4f}".format(counter) + ",")
    traingle.append(counter)
    
print(len(x_tab))

plt.plot(traingle)
plt.ylabel('some numbers')
plt.savefig("triangle.png")