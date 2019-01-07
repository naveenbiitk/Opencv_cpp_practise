#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat frame;

	VideoCapture cap(0);

	if(!cap.isOpened())
	{
		cout<<"Error"<<endl;
		return -1;
	}
	 cap >> frame;

	 bool isColor=(frame.type()==CV_8UC3);

	 VideoWriter writer;
	 int codec= CV_FOURCC('M','J','P','G');
	 double fps=30.0;
	 string filename="./live.mp4";
	 writer.open(filename,codec,fps,frame.size(),isColor);

	 if(!writer.isOpened())
	 {
	 	cerr<<"Couldn't open the output video file \n";
	 	return -1;
	 }

	 cout<<"Writing Video: "<<filename<<endl;
	 cout<<"Press 'q' to terminate";

	 while(1)
	 {
	 	cap.read(frame);

	 	writer.write(frame);
	 	imshow("live",frame);

	 	if((char)waitKey(5)=='q')
	 		break;
	 }
	 return 0;
}