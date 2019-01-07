#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat frame;
	VideoCapture cap;
	cap.open(0);

	if(!cap.isOpened())
	{
		cout<<"ERROR! Unable to open\n";
		return -1;
	}

	cout<<"started "<<"Press any 'q' to terminate"<<endl;

	while(1)
	{
		cap.read(frame);
		if(frame.empty())
		{
			cerr<<"ERROR blank frame grabbed \n";
			break;
		}

		namedWindow("WEBCAM", WINDOW_AUTOSIZE);
		imshow("Live",frame);
		if((char)waitKey(5)=='q')
			break;
		
	}

	return 0;
}