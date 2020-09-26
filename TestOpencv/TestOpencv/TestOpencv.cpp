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


//人脸识别函数的解释器
string face_cascade_name = "haarcascade_frontalface_alt_tree.xml";
CascadeClassifier face_cascade;

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