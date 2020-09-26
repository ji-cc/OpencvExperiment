// TestOpencv.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
//OpenCV ͷ�ļ�����
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
		printf("�������������󣬿���δ�ҵ��ļ����������ļ�������Ŀ¼�£�\n");
		return -1;
	}
	OpenUSB();
	return 0;

	Mat img;
	img = imread("D:\\OpenCVʵ��\\lenna.bmp", 1);
	namedWindow("OpenImg", CV_WINDOW_AUTOSIZE);
	imshow("OpenImg", img);
	waitKey(0);

	return 0;
}

//˵��3����USB����ͷ����¼����Ƶ�ļ�
void OpenUSB()
{
	//д����Ƶ�ļ���
	std::string outFlie = "D:/A1.avi";
	//��Ƶд�����
	//cv::VideoWriter writer;

	VideoCapture capture(0);//����ǱʼǱ���0�򿪵����Դ�������ͷ��1 ����ӵ����  
	double rate = 20;//��Ƶ��֡��  
	//���֡�Ŀ��
	int w = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
	int h = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	Size videoSize(w, h);
	//VideoWriter writer("D:\\VideoTest.avi", CV_FOURCC('D', 'I', 'V', 'X'), rate, videoSize);
	VideoWriter writer("D:\\VideoTest2.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, videoSize);
	//VideoWriter writer("D:\\VideoTest1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
	//����Ƶ�ļ���׼��д��
	//writer.open(outFlie, -1, rate, videoSize, true);

	Mat frame;

	while (capture.isOpened())
	{
		capture >> frame;
		detectAndDisplay(frame);

		writer << frame;
		//writer.write(frame);
		//imshow("video", frame);  
		if (waitKey(20) == 27)//27�Ǽ�������escʱ����������յ���ascii��ֵ  
		{
			break;
		}
	}

	//�ر���Ƶ�ļ�
	writer.release();
	capture.release();

}




void detectAndDisplay(Mat face)
{
	std::vector<Rect> faces;
	Mat face_gray;
	cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb����ת��Ϊ�Ҷ�����
	equalizeHist(face_gray, face_gray);   //ֱ��ͼ���⻯ 
	face_cascade.detectMultiScale(face_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(1, 1));
	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(face, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 255, 255), 2, 7, 0);
	}
	imshow("����ʶ��", face);
}

