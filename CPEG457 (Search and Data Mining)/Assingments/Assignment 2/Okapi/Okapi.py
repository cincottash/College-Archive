import numpy as np
import matplotlib.pyplot as plt

dirMu = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]

def MAP():
	
	MAP_ap8889 = [.2157, .2168, .2164, .2163, .2159, .2152, .2131, .2103, .2069, .2011, .1938]
	MAP_doe = [.1771, .1809, .1808, .1825, .1834, .1836, .1844, .1844, .1797, .1754, .1699]
	MAP_Mobapp = [.3513, .3525, .3534, .3544, .3541, .3541, .3538, .3527, .3511, .3488, .3474]
	MAP_robust04 = [.2025, .2221, .2287, .233, .236, .237, .2375, .2358, .232, .2253, .2122]
	MAP_wt2g = [.2703, .2911, .2979, .2994, .301, .3007, .3015, .2959, .2819, .2658, .2272]

	X=np.array(dirMu)
	Y1=np.array(MAP_ap8889)
	Y2=np.array(MAP_doe)
	Y3=np.array(MAP_Mobapp)
	Y4=np.array(MAP_robust04)
	Y5=np.array(MAP_wt2g)

	plt.plot(X, Y1,label="ap8889")
	plt.plot(X, Y2,label="doe")
	plt.plot(X, Y3,label="Mobapp")
	plt.plot(X, Y4,label="robust04")
	plt.plot(X, Y5,label="wt2g")

	plt.title('Okapi MAP Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('MAP Value')

	plt.legend()

	plt.show()

def P30():
	P30_ap8889 = [.2954, .2945, .2954, .2936, .2918, .2904, .284, .2806, .2744, .2667, .2546]
	P30_doe = [.2152, .219, .221, .221, .221, .2267, .2238, .2267, .2276, .221, .2124]
	P30_Mobapp = [.6386, .6392, .6423, .645, .645, .6471, .645, .6439, .6423, .6381, .6381]
	P30_robust04 = [.249, .2697, .2802, .2838, .2876, .2896, .2913, .2898, .2886, .2788, .2614]
	P30_wt2g = [.294, .3107, .3167, .3207, .3173, .3313, .3247, .322, .3073, .294, .248]

	X=np.array(dirMu)
	Y1=np.array(P30_ap8889)
	Y2=np.array(P30_doe)
	Y3=np.array(P30_Mobapp)
	Y4=np.array(P30_robust04)
	Y5=np.array(P30_wt2g)

	plt.plot(X, Y1,label="ap8889")
	plt.plot(X, Y2,label="doe")
	plt.plot(X, Y3,label="Mobapp")
	plt.plot(X, Y4,label="robust04")
	plt.plot(X, Y5,label="wt2g")

	plt.title('Okapi P@30 Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('P@30 Value')

	plt.legend()

	plt.show()

def main():
	MAP()
	P30()


if __name__ == '__main__':
	main()