import numpy as np
import matplotlib.pyplot as plt

dirMu = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]

def MAP():
	
	MAP_ap8889 = [.1187, .1182, .1167, .1154, .1144, .1128, .1117, .1107, .1094, .1077, .1068]
	MAP_doe = [.0904, .0898, .0894, .0878, .0879, .0883, .0898, .0903, .0915, .0909, .091]
	MAP_Mobapp = [.0416, .0412, .0409, .0406, .0405, .0404, .0399, .0397, .0295, .0395, .0393]
	MAP_robust04 = [.1462, .1666, .1668, .1658, .1648, .1633, .1619, .1599, .1589, .1571, .1556]
	MAP_wt2g = [.2317, .2393, .2317, .2292, .2221, .2159, .2127, .2094, .2051, .2003, .1982]

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

	plt.title('F1_LOG MAP Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('MAP Value')

	plt.legend()

	plt.show()

def P30():
	P30_ap8889 = [.2135, .2107, .2059, .2018, .1993, .197, .1945, .1927, .1906, .1893, .1893]
	P30_doe = [.1219, .1276, .1286, .1276, .1257, .1248, .1238, .1219, .119, .1181, .1181]
	P30_Mobapp = [.1243, .1243, .1238, .1238, .1238, .1238, .1233, .1238, .1243, .1243, .1243]
	P30_robust04 = [.212, .2392, .2396, .2387, .2372, .2357, .2337, .2317, .228, .2269, .2257]
	P30_wt2g = [.2727, .298, .286, .278, .274, .262, .2593, .262, .2587, .2553, .252]

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

	plt.title('F1_LOG P@30 Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('P@30 Value')

	plt.legend()

	plt.show()

def main():
	MAP()
	P30()


if __name__ == '__main__':
	main()