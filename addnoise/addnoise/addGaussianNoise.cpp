//给图像添加高斯噪声  
#include <cmath>  
#include <limits>  
#include <cstdlib>  
#include <iostream>  
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  

using namespace cv;
using namespace std;


//生成高斯噪声  
double generateGaussianNoise(double mu, double sigma)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;
	double U1, U2;
	if (phase == 0) {
		do {
			U1 = (double)rand() / RAND_MAX;
			U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else {
		X = V2 * sqrt(-2 * log(S) / S);
	}
	phase = 1 - phase;
	return mu + sigma * X;
}



void AddGaussianNoise(Mat I, double mu, double sigma, int k)
{
	// accept only char type matrices  
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j) {
			double val = p[j] + generateGaussianNoise(mu, sigma) * k;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;

			p[j] = (uchar)val;

		}
	}

}

int main()
{
	Mat srcImage = imread("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\gray_weight.bmp", 0);
	if (!srcImage.data)
	{
		cout << "读入图片错误！" << endl;
		return -1;
	}
	imshow("原图像", srcImage);
	AddGaussianNoise(srcImage, 1, 1, 64);
	imshow("添加高斯噪声后的图像", srcImage);
	imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\addGaussianNoise.bmp", srcImage);
	waitKey();
	return 0;
}