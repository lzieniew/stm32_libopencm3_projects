# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from numpy import arange
from math import pi, sin, cos
import matplotlib.pyplot as plt

MAX_DAC_VALUE = 512

x_tab = arange(0, 2 * pi, 0.1)
sinus = []

print("start")
for i in x_tab:
    val = int((((cos(i)) / 2)+ 0.5) * (MAX_DAC_VALUE - 1))
    print("{:10.4f}".format(val) + ",")
    sinus.append(val)
print("stop")
    
    
print(len(x_tab))

plt.plot(sinus)
plt.ylabel('some numbers')
plt.savefig("chart.png")