# -*- coding: utf-8 -*-
from numpy import arange
from math import pi, sin, cos
import matplotlib.pyplot as plt

MAX_DAC_VALUE = 512
STEPS = 16

x_tab = arange(0, 2 * pi, 0.1)
traingle = []


counter = 0.
step = (MAX_DAC_VALUE - 1) / (STEPS/2)

for i in range(int(STEPS/2)):
    counter += step
    print("{:10.4f}".format(counter) + ",")
    traingle.append(counter)

for i in range(int(STEPS/2)):
    counter -= step
    print("{:10.4f}".format(counter) + ",")
    traingle.append(counter)
    
    
print(len(traingle))

plt.plot(traingle)
plt.ylabel('some numbers')
plt.savefig("triangle.png")