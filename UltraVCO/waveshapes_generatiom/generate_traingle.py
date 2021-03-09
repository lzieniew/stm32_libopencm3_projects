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
step = (MAX_DAC_VALUE - 1) / (STEPS/2)

for i in range(int(STEPS/2)):
    counter += step
    print("{:10.4f}".format(counter) + ",")
    traingle.append(counter)

for i in range(int(STEPS/2)):
    counter -= step
    print("{:10.4f}".format(counter) + ",")
    traingle.append(counter)

# print("start")
# for i in x_tab:
#     val = int((((sin(i)) / 2)+ 0.5) * (MAX_DAC_VALUE - 1))
#     print("{:10.4f}".format(val) + ",")
#     sinus.append(val)
# print("stop")
    
    
print(len(traingle))

plt.plot(traingle)
plt.ylabel('some numbers')
plt.savefig("triangle.png")