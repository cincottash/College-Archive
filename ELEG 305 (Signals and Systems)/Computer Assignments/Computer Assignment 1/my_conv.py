import numpy as np
from numpy import *
import scipy as Sci
import scipy.linalg
import speech.wav

def  myconv(x,h):

############################################################################
# A function to generate the output signal y as convolution of input signal
# x and impulse response signal h
############################################################################

# INPUT PARAMETERS---------------------------------------------------------
# x: input signal
# h: impulse response
    len_x = len(x) # length of x
    len_h = len(h) # length of h
    X=[x,zeros(1,len_h)] #We want to make X and H the same length, so we fill X with all the values of x, and the rest with 0's until it is the same length as H
    H=[h,zeros(1,len_x)] #We want to make X and H the same length, so we fill H with all the values of h, and the rest with 0's until it is the same length as X

############################################################################
# Data processing: convolution (TO BE COMPLETED BY STUDENTS)
############################################################################
# OUTPUT PARAMETERS--------------------------------------------------------
# y: output signal as convolution of input signal x and impulse response h

# Write the code including comments to explain what you are doing
    for i in range(1,len_h+len_x+1): #We want to itterate through over the total region, which goes from 1 to the length of x + h 
        y[i]=0 #We initialize the first value of our output as 0 (This is just to initialize a value, it will be changed soon)
        for j in range(1,len_x): #For the second loop, we want to itterate over the length of our input signal, this is equalivent to us shifting h(t-T) "through" x(T)
            if i-j+1>0: #This checks for overlap of x(T) and h(t-T)
                y[i]=y[i]+X[j]*H(i-j+1) #If there is overlap, then we update our output array to be the convolution of x(T) and h(t-T)
    return y
