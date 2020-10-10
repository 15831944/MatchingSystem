//利用程序给原图像增加椒盐噪声  
//图象模拟添加椒盐噪声是通过随机获取像素点斌那个设置为高亮度点来实现的  

#include <cstdlib>  
#include <iostream>  
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  

using namespace cv;
using namespace std;

Mat addSaltNoise(const Mat srcImage, int n);


int main()
{
	Mat srcImage = imread("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\gray_weight.bmp", 0);
	if (!srcImage.data)
	{
		cout << "读入图像有误！" << endl;
		system("pause");
		return -1;
	}
	imshow("原图像", srcImage);
	Mat dstImage = addSaltNoise(srcImage, 20000);
	imshow("添加椒盐噪声的图像", dstImage);
	//存储图像  
	imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\addSaltNoise.bmp", dstImage);
	waitKey();
	return 0;
}

Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//随机取值行列  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;       //盐噪声  
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{
		//随机取值行列  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;     //椒噪声  
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;
}