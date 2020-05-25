import numpy as np
import matplotlib.pyplot as plt

dirMu = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]

def MAP():
	
	MAP_ap8889 = [.1187, .1177, .1158, .1141, .111, .1068, .1037, .1007, .0973, .0929, .089]
	MAP_doe = [.0904, .0897, .0883, .0878, .0898, .091, .0901, .0888, .0863, .0836, .0807]
	MAP_Mobapp = [.0416, .0413, .0405, .0405, .0397, .0393, .039, .0388, .0388, .0391, .039]
	MAP_robust04 = [.1462, .1672, .1662, .1644, .1605, .1556, .1502, .1444, .1386, .1339, .1284]
	MAP_wt2g = [.2317, .2384, .2312, .2195, .2101, .1982, .1884, .1813, .1714, .1613, .1451]

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

	plt.title('TF_IDF MAP Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('MAP Value')

	plt.legend()

	plt.show()

def P30():
	P30_ap8889 = [.2135, .21, .2037, .1986, .1922, .1893, .1833, .1781, .171, .1646, .1557]
	P30_doe = [.1219, .1267, .1286, .1267, .1219, .1181, .119, .1162, .1143, .1114, .1067]
	P30_Mobapp = [.1243, .1243, .1238, .1238, .1233, .1243, .1243, .1243, .1243, .1243, .1238]
	P30_robust04 = [.212, .2402, .2398, .2365, .2321, .2257, .2197, .2147, .2075, .1996, .1932]
	P30_wt2g = [.2727, .2993, .282, .2747, .2627, .252, .242, .2287, .2167, .2, .182]

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

	plt.title('TF_IDF P@30 Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('P@30 Value')

	plt.legend()

	plt.show()

def main():
	MAP()
	P30()


if __name__ == '__main__':
	main()
