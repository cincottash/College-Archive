import math
import numpy
from numpy import *
import scipy
from scipy import *
from scipy.signal import *


w = logspace(-2, 2, 100)

a = [1, (2/math.sqrt(2)), 1] #denominator
b = [1] #numerator

#k=1
H1 = freqs(b, a, w)


#k=.09
a = [1, (0.6/math.sqrt(2)), .09] #denominator
b = [0.09] #numerator
H2 = freqs(b, a, w)

#k=4
a = [1, (4/math.sqrt(2)), 4] #denominator
b = [4] #numerator
H3 = freqs(b, a, w)