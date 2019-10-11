#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <fstream>

using namespace std;
using namespace cv;

void showImage(const char *winName, InputArray imgMat, int x, int y);
void outToFile(const char *fileName, const string content);

//const char codeLib[] = "@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const char codeLib[] = "01";
const char *imgFileName = "C:\\Users\\hp\\Desktop\\作业\\第二章\\圆柱圆锥\\GB-homework1.jpg";
const char *outFileName = "test.txt";

int main() {
	cout << strlen(codeLib) << " : " << codeLib << endl;
	Mat srcImg = imread(imgFileName);
	Mat grayImg;
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

	string str;

	int mark = 0;

	for (int y = 0; y < grayImg.rows; y++) {
		for (int x = 0; x < grayImg.cols; x++) {
			int grayVal = (int)grayImg.at<uchar>(y, x);
			            //cout << grayVal << endl;
			if (grayVal==0) {
				if(mark == 0){
					str += codeLib[0];
					mark = 1;
				}
				else {
					str += codeLib[1];
					mark = 0;
				}
			}
			else {
				str += " ";
			}
			//if (grayVal > 255 / 2) {
			//	str += codeLib[1];
			//}
			//else {
			//	str += codeLib[0];
			//}
		}
		str += "\r\n";
	}

	cout << str << endl;
	outToFile(outFileName, str);
	showImage("src", srcImg, 0, 0);
	showImage("gray", grayImg, 100, 100);
	waitKey(0);
	return 0;
}

//显示图片
void showImage(const char *winName, InputArray imgMat, int x, int y) {
	namedWindow(winName, WINDOW_AUTOSIZE);
	moveWindow(winName, x, y);
	imshow(winName, imgMat);
}

//将字符串写入文件
void outToFile(const char *fileName, const string content) {
	ofstream outStream;
	outStream.open(fileName);
	outStream << content << endl;
	outStream.close();
}