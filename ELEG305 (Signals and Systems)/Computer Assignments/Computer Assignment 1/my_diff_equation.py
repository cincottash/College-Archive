
import numpy as np
def my_diffequation(x, alpha, N):

############################################################################
# A function to generate the output signal y of the system described by a
# diffence equation
############################################################################

# INPUT PARAMETERS---------------------------------------------------------
# x: input signal
# alpha: decreasing amplitude
# N: delay between consecutive echoes

############################################################################
# Data processing (TO BE COMPLETED BY STUDENTS)
############################################################################
# OUTPUT PARAMETERS--------------------------------------------------------
# y: output signal
    L=len(x)

    x=[x, zeros(1,5*L)] #Fill with x and zeros
    y=[x, zeros(1,N-mod(L,N))] #y range is smaller

    for i in range((N+1),L,N):
        y=y(i,i=N-1)+ alpha*y(i-N,i-1) #Alpha is our attentuation (0.9 in our case), while N is the delay

    return y
