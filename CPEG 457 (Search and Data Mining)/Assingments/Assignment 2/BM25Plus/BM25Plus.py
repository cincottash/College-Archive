import numpy as np
import matplotlib.pyplot as plt

dirMu = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]

def MAP():
	
	MAP_ap8889 = [.1191, .1162, .1087, .1016, .0956, .0913, .0879, .0844, .082, .0801, .0785]
	MAP_doe = [.0903, .0888, .0942, .0928, .0853, .0828, .0801, .0789, .0765, .0758, .0753]
	MAP_Mobapp = [.0414, .0413, .0393, .0387, .039, .039, .0389, .039, .0389, .0388, .0388]
	MAP_robust04 = [.1462, .1678, .1586, .1478, .1397, .1331, .129, .1253, .1226, .1203, .1179]
	MAP_wt2g = [.2317, .2277, .2058, .188, .1751, .1684, .1598, .1522, .1431, .1374, .1342]

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

	plt.title('BM25Plus MAP Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('MAP Value')

	plt.legend()

	plt.show()

def P30():
	P30_ap8889 = [.2139, .2073, .1936, .1836, .1717, .1596, .1525, .147, .1427, .139, .1365]
	P30_doe = [.1229, .1276, .121, .1162, .1142, .1086, .1057, .1057, .1029, .101, .0981]
	P30_Mobapp = [.1243, .1243, .1243, .1243, .1238, .1238, .1238, .1238, .1233,  .1233,  .1233]
	P30_robust04 = [.211, .2431, .2297, .2203, .2099, .2008, .1937, .1889, .1857, .1822, .1806]
	P30_wt2g = [.2693, .2813, .258, .2407, .225, .2113, .2067, .186, .1773, .1707, .1633]

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

	plt.title('BM25Plus P@30 Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('P@30 Value')

	plt.legend()

	plt.show()

def main():
	MAP()
	P30()


if __name__ == '__main__':
	main()