// TestOpencv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//OpenCV 头文件包含
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "cv.hpp"
#include "opencv.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>
using namespace cv;
using namespace std;

string face_cascade_name = "haarcascade_frontalface_alt_tree.xml";
CascadeClassifier face_cascade;

void OpenUSB();
void detectAndDisplay(Mat face);



int main()
{
	if (!face_cascade.load(face_cascade_name))
	{
		printf("级联分类器错误，可能未找到文件，拷贝该文件到工程目录下！\n");
		return -1;
	}
	OpenUSB();
	return 0;

	Mat img;
	img = imread("D:\\OpenCV实验\\lenna.bmp", 1);
	namedWindow("OpenImg", CV_WINDOW_AUTOSIZE);
	imshow("OpenImg", img);
	waitKey(0);

	return 0;
}

//说明3：打开USB摄像头，且录制视频文件
void OpenUSB()
{
	//写入视频文件名
	std::string outFlie = "D:/A1.avi";
	//视频写入对象
	//cv::VideoWriter writer;

	VideoCapture capture(0);//如果是笔记本，0打开的是自带的摄像头，1 打开外接的相机  
	double rate = 20;//视频的帧率  
	//获得帧的宽高
	int w = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
	int h = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	Size videoSize(w, h);
	//VideoWriter writer("D:\\VideoTest.avi", CV_FOURCC('D', 'I', 'V', 'X'), rate, videoSize);
	VideoWriter writer("D:\\VideoTest2.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, videoSize);
	//VideoWriter writer("D:\\VideoTest1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
	//打开视频文件，准备写入
	//writer.open(outFlie, -1, rate, videoSize, true);

	Mat frame;

	while (capture.isOpened())
	{
		capture >> frame;
		detectAndDisplay(frame);

		writer << frame;
		//writer.write(frame);
		//imshow("video", frame);  
		if (waitKey(20) == 27)//27是键盘摁下esc时，计算机接收到的ascii码值  
		{
			break;
		}
	}

	//关闭视频文件
	writer.release();
	capture.release();

}




void detectAndDisplay(Mat face)
{
	std::vector<Rect> faces;
	Mat face_gray;
	cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
	equalizeHist(face_gray, face_gray);   //直方图均衡化 
	face_cascade.detectMultiScale(face_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(1, 1));
	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(face, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 255, 255), 2, 7, 0);
	}
	imshow("人脸识别", face);
}

