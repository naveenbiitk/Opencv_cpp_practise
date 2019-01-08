
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "iostream"

using namespace std;
using namespace cv;

int h_min=4,h_max=78,s_min=130,s_max=255,v_min=20,v_max=255;

int main(void)
{
	VideoCapture cap(1);
	if(!cap.isOpened())
		return -1;

	cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	Mat frame,hsv,gray;
	namedWindow("camera");
	namedWindow("hsv");

	while(true)
	{
		cap.read(frame);
		imshow("camera",frame);
		cvtColor(frame,hsv,CV_BGR2HSV);

		createTrackbar("H minimum:","hsv",& h_min,255);
		createTrackbar("H maximum:","hsv",& h_max,255);
		createTrackbar("S minimum:","hsv",& s_min,255);
		createTrackbar("S maximum:","hsv",& s_max,255);
		createTrackbar("V minimum:","hsv",& v_min,255);
		createTrackbar("V maximum:","hsv",& v_max,255);

		inRange(hsv,Scalar(h_min,s_min,v_min),Scalar(h_max,s_max,v_max),hsv);
		imshow("hsv",hsv);

		if((char)waitKey(5)=='q')
	 		break;

	}
	return 0;
}