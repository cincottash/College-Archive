import numpy as np
from numpy import *
import pylab as pl
import wave
import struct
from my_conv import myconv
#import scipy.signal as signal
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
#pl.plot(waveData)
#pl.show()
##--------------------------------------------------------------------
## read the impulse response for the system
len_imp = 128 # length of left/right impulse response (fixed)

fp = open("H0e090a.dat", 'rb') # open imp_filename
sysData=zeros(2*len_imp)
for i in range(0,2*len_imp):
    strd = fp.read(2)
    data1 = struct.unpack(">h", strd) 
    sysData[i] = int(data1[0])

fp.close() # close imp_filename
## separate the left and right channel impulse response
leftimp  = sysData[0:2*len_imp-1:2] # left ear impulse response: hl[1]...hl[len_imp]
rightimp = sysData[1:2*len_imp:2] # right ear impulse response: hr[1]...hr[len_imp]
#pl.plot(rightimp)
#pl.show()
##--------------------------------------------------------------------
#leftCh = signal.convolve(waveData, leftimp, mode='valid')
#rightCh = signal.convolve(waveData, rightimp, mode='valid')
leftCh  = myconv(leftimp, waveData) # convolution of left ear impulse response and waveData
rightCh = myconv(rightimp, waveData) # convolution of left ear impulse response and waveData
len_R= len(rightCh)
len_L= len(leftCh)
#pl.plot(leftCh)
#pl.plot(rightCh)
#pl.show()
##--------------------------------------------------------------------
LR_Ch = vstack((leftCh, rightCh))
norml= 1.05*abs(LR_Ch).max() 
leftCh = leftCh.reshape(len(leftCh ), 1,order='F').copy()
rightCh = rightCh.reshape(len(rightCh ), 1,order='F').copy()
##--------------------------------------------------------------------
outWave = hstack((leftCh, rightCh))/norml*32768.
# Since we'll write outWave to the output wav file which has 16bits short int as the data, 
#we should map the values in outWave to the range of 16bits short int by multiplying 32768. 
#pl.plot(outWave)
#pl.show()
##--------------------------------------------------------------------
f1 = wave.open("testOutput.wav",'wb')
f1.setnchannels(2)
f1.setsampwidth(2) # width = 2 Bytes
f1.setframerate(framerate)
f1.setnframes(len_L)

f1.writeframes(outWave.astype(np.short).tostring())
# The outWave is float64 type after the convolution, thus we should first translate outWave
# into 16bits int using astype(np.short) and then write it as a string to the target file.     
f1.close()
##--------------------------------------------------------------------
print "Finished!"
