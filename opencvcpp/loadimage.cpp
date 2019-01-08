#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	char* img_name=argv[1];

	//if(argc>1)
	//	img_name=argv[1];

	Mat image;

	image=imread(img_name,IMREAD_COLOR);
	if(image.empty())
	{
		cout<<"Couldn't open/find image";
		return -1;
	}

	namedWindow("Display window",WINDOW_AUTOSIZE);
	imshow("Display_image",image);

	waitKey(0);
	return 0;
}