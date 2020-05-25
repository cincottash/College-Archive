import numpy as np
import matplotlib.pyplot as plt

dirMu = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]

def MAP():
	
	MAP_ap8889 = [.0161, .1176,  .1222, .1254, .1278, .1294, .1303, .1313, .1324, .1332, .1336]
	MAP_doe = [.0071, .0815, .0871, .0867, .0885, .0902, .0912, .0914, .0916, .091, .0909]
	MAP_Mobapp = [.0093, .3057, .3121, .3142, .316, .3173, .3182, .3188, .3195, .3193, .3195]
	MAP_robust04 = [.0148, .0813, .0841, .0861, .0875, .0882, .0889, .0896, .09, .0903, .0904]
	MAP_wt2g = [.0103, .0674, .071, .072, .0739, .0755, .0761, .0771, .0781, .0785, .0792]

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

	plt.title('PL2 MAP Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('MAP Value')

	plt.legend()

	plt.show()

def P30():
	P30_ap8889 = [.0231, .176, .1854, .1877, .1932, .1927, .1932, .1947, .1968, .1977, .1993]
	P30_doe = [.0057, .1181, .1181, .1229, .1267, .1305, .1305, .1324, .1324, .1295, .1314]
	P30_Mobapp = [.0185, .5529, .5603, .5672, .5683, .5688, .573, .5741, .5762, .5751, .5735]
	P30_robust04 = [.0142, .1181, .121, .125, .1252, .1254, .1262, .1272, .1272, .127, .1273]
	P30_wt2g = [.024, .1, .104, .11, .1173, .1173, .1173, .1173, .1173, .118, .1173]

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

	plt.title('PL2 P@30 Values')
	
	plt.xlabel('dirMu Value')
	
	plt.ylabel('P@30 Value')

	plt.legend()

	plt.show()

def main():
	MAP()
	P30()


if __name__ == '__main__':
	main()
