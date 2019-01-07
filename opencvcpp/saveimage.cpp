#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	char* img_name=argv[1];

	Mat image;

	image=imread(img_name,1);

	Mat img_gray;
	
}