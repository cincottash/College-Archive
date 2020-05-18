import numpy as np
from numpy import *
import pylab as pl
import wave
import struct
import scipy.signal as signal
from my_diff_equation import my_diffequation
##--------------------------------------------------------------------
# LTI system parameters
N = 2250          # delay
alpha = 0.9       # amplitude scaling
b = np.array([1])
a = zeros(N+1)
a[0] = 1
a[N] = -alpha
##--------------------------------------------------------------------
## read the input wave file "speech.wav"
f = wave.open("speech.wav", "rb")

params = f.getparams()
nchannels, sampwidth, framerate, nframes = params[:4]

str_data = f.readframes(nframes)
f.close()

if (framerate!=44100): # if Fs is not equal to 44100
    print 'Fs is not 44.1KHz' # display error and abort

waveData = np.fromstring(str_data, dtype=np.short)
waveData = waveData/32768.0  #normalization

len_data = len(waveData) 

Nf = float(N)
strDelay = "The delay of N = %f samples corresponds to a delay %f seconds" %(N, Nf/framerate)
print strDelay
#pl.plot(waveData)
#pl.show()
##--------------------------------------------------------------------
# echo is the output from the differential equation
echo = my_diffequation(waveData, alpha, N)
len_e = len(echo)
# echo2 is the output of the IIR filter
echo2 = signal.lfilter(b, a, waveData)
len_e2 = len(echo2)
# If you want to check if the code works fine, you can comment my_diffequation(waveData, alpha, N)
# and only use echo2 = signal.lfilter(b, a, waveData)
# which uses lfilter function in signal package. 
# The results echo and echo2 should be the same.


#pl.subplot(211)
#pl.plot(echo)
#pl.subplot(212)
#pl.plot(echo2)
#pl.show()
##--------------------------------------------------------------------
norml1= 1.05*abs(echo).max()
norml2= 1.05*abs(echo2).max()  
##--------------------------------------------------------------------
outWave1 = echo/norml1*32768
outWave2 = echo2/norml2*32768
#pl.plot(outWave)
#pl.show()
##--------------------------------------------------------------------
f1 = wave.open("echo.wav",'wb')
f1.setnchannels(1)
f1.setsampwidth(2) # width = 2 Bytes
f1.setframerate(framerate)
f1.setnframes(len_e)
f1.writeframes(outWave1.astype(np.short).tostring())
f1.close()
   
f2 = wave.open("echo2.wav",'wb')
f2.setnchannels(1)
f2.setsampwidth(2) # width = 2 Bytes
f2.setframerate(framerate)
f2.setnframes(len_e2)
f2.writeframes(outWave2.astype(np.short).tostring())
f2.close()
##--------------------------------------------------------------------
print "Finished!"
