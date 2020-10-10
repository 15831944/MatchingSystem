//���ó����ԭͼ�����ӽ�������  
//ͼ��ģ����ӽ���������ͨ�������ȡ���ص���Ǹ�����Ϊ�����ȵ���ʵ�ֵ�  

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
	Mat srcImage = imread("C:\\Users\\����\\Desktop\\ȫ������\\�ɼ�ͼƬ\\gray_weight.bmp", 0);
	if (!srcImage.data)
	{
		cout << "����ͼ������" << endl;
		system("pause");
		return -1;
	}
	imshow("ԭͼ��", srcImage);
	Mat dstImage = addSaltNoise(srcImage, 20000);
	imshow("��ӽ���������ͼ��", dstImage);
	//�洢ͼ��  
	imwrite("C:\\Users\\����\\Desktop\\ȫ������\\�ɼ�ͼƬ\\addSaltNoise.bmp", dstImage);
	waitKey();
	return 0;
}

Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//���ȡֵ����  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//ͼ��ͨ���ж�  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;       //������  
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
		//���ȡֵ����  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//ͼ��ͨ���ж�  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;     //������  
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