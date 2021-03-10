# -*- coding: utf-8 -*-

from numpy import arange
from math import pi, sin, cos
import matplotlib.pyplot as plt

MAX_DAC_VALUE = 512
STEPS = 64

x_tab = arange(0, 2 * pi, pi / (STEPS/2))
sinus = []

print("start")
for i in range(STEPS):
    if i >= STEPS/2:
        val = 0
    else:
        val = 512
    print("{:10.4f}".format(val) + ",")
    sinus.append(val)
print("stop")
    
    
print(len(x_tab))

plt.plot(sinus)
plt.ylabel('some numbers')
plt.savefig("chart.png")