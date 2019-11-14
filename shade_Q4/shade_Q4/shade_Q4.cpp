// shade_Q4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;
void RemoveSmallRegion(Mat& Src, Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode);
int main()
{	
	int ptr;
	Mat image = imread("D://影子.png");
	Mat imgGray,result;
	cvtColor(image, imgGray, CV_BGR2GRAY);
	Mat dstImage(imgGray.size(), imgGray.type());
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
				int ch_value = imgGray.at<uchar>(x,y);
				dstImage.at<uchar>(x, y) = ch_value;
		}
	}
/*	for (int i = 796;i < 1014;i++) {
		for (int j = 764;j < 1674;j++) {
			int ch_value = imgGray.at<uchar>(i,j);
			if (ch_value > 180 && ch_value < 205) {
				imgGray.at<uchar>(i, j) = 0;
			}
		}
	}*/
	//int get_value = imgGray.at<uchar>(867,1661);
	Mat Gaussian_out, Canny_out;
	GaussianBlur(imgGray, Gaussian_out, Size(5, 5), 0, 0);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat erode_out;
	threshold(Gaussian_out, result, 197, 255, CV_THRESH_BINARY);
	Mat result_dst;
	//RemoveSmallRegion(result, result_dst, 20, 1, 1);
	//RemoveSmallRegion(result_dst, result_dst, 20, 0, 0);
	//cout <<   image.rows<< "    "<<image.cols;
	//cout << get_value;

	//进行腐蚀操作
	//erode(Gaussian_out, erode_out, element);
	//载入原始图 
	Canny(result, Canny_out, 3, 9, 3);
	namedWindow("show");
	//imshow("show",Canny_out);
	imwrite("D://copy.png", result);
	waitKey();
	destroyAllWindows();
	return 0;
}
//CheckMode: 0代表去除黑区域，1代表去除白区域; NeihborMode：0代表4邻域，1代表8邻域;  
void RemoveSmallRegion(Mat& Src, Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode)
{
	int RemoveCount = 0;       //记录除去的个数  
	//记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查  
	Mat Pointlabel = Mat::zeros(Src.size(), CV_8UC1);

	if (CheckMode == 1)
	{
		cout << "Mode: 去除小区域. ";
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i);
			uchar* iLabel = Pointlabel.ptr<uchar>(i);
			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] < 10)
				{
					iLabel[j] = 3;
				}
			}
		}
	}
	else
	{
		cout << "Mode: 去除孔洞. ";
		for (int i = 0; i < Src.rows; ++i)
		{
			uchar* iData = Src.ptr<uchar>(i);
			uchar* iLabel = Pointlabel.ptr<uchar>(i);
			for (int j = 0; j < Src.cols; ++j)
			{
				if (iData[j] > 10)
				{
					iLabel[j] = 3;
				}
			}
		}
	}

	vector<Point2i> NeihborPos;  //记录邻域点位置  
	NeihborPos.push_back(Point2i(-1, 0));
	NeihborPos.push_back(Point2i(1, 0));
	NeihborPos.push_back(Point2i(0, -1));
	NeihborPos.push_back(Point2i(0, 1));
	if (NeihborMode == 1)
	{
		cout << "Neighbor mode: 8邻域." << endl;
		NeihborPos.push_back(Point2i(-1, -1));
		NeihborPos.push_back(Point2i(-1, 1));
		NeihborPos.push_back(Point2i(1, -1));
		NeihborPos.push_back(Point2i(1, 1));
	}
	else cout << "Neighbor mode: 4邻域." << endl;
	int NeihborCount = 4 + 4 * NeihborMode;
	int CurrX = 0, CurrY = 0;
	//开始检测  
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iLabel = Pointlabel.ptr<uchar>(i);
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 0)
			{
				//********开始该点处的检查**********  
				vector<Point2i> GrowBuffer;                                      //堆栈，用于存储生长点  
				GrowBuffer.push_back(Point2i(j, i));
				Pointlabel.at<uchar>(i, j) = 1;
				int CheckResult = 0;                                               //用于判断结果（是否超出大小），0为未超出，1为超出  

				for (int z = 0; z < GrowBuffer.size(); z++)
				{

					for (int q = 0; q < NeihborCount; q++)                                      //检查四个邻域点  
					{
						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
						if (CurrX >= 0 && CurrX < Src.cols&&CurrY >= 0 && CurrY < Src.rows)  //防止越界  
						{
							if (Pointlabel.at<uchar>(CurrY, CurrX) == 0)
							{
								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer  
								Pointlabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查  
							}
						}
					}

				}
				if (GrowBuffer.size() > AreaLimit) CheckResult = 2;                 //判断结果（是否超出限定的大小），1为未超出，2为超出  
				else { CheckResult = 1;   RemoveCount++; }
				for (int z = 0; z < GrowBuffer.size(); z++)                         //更新Label记录  
				{
					CurrX = GrowBuffer.at(z).x;
					CurrY = GrowBuffer.at(z).y;
					Pointlabel.at<uchar>(CurrY, CurrX) += CheckResult;
				}
				//********结束该点处的检查**********  


			}
		}
	}

	CheckMode = 255 * (1 - CheckMode);
	//开始反转面积过小的区域  
	for (int i = 0; i < Src.rows; ++i)
	{
		uchar* iData = Src.ptr<uchar>(i);
		uchar* iDstData = Dst.ptr<uchar>(i);
		uchar* iLabel = Pointlabel.ptr<uchar>(i);
		for (int j = 0; j < Src.cols; ++j)
		{
			if (iLabel[j] == 2)
			{
				iDstData[j] = CheckMode;
			}
			else if (iLabel[j] == 3)
			{
				iDstData[j] = iData[j];
			}
		}
	}

	cout << RemoveCount << " objects removed." << endl;
}
