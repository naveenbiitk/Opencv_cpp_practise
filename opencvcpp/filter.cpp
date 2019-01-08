
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int Delay_Caption=1500;
int Delay_Blur=1000;
int Max_Kernel_Length=31;

Mat src,dst;
char window_name[]="Smoothing Demo";

int display_caption(const char* caption);
int display_dst(int delay);

int main(void)
{
	namedWindow(window_name,WINDOW_AUTOSIZE);

	src=imread("lenna.png");

	if(display_caption("Original Image ")!=0)
		return 0;
	dst=src.clone();

	if(display_dst(Delay_Caption)!=0)
		return 0;

	if(display_caption("Homogeneous Blur ")!=0)
		return 0;
	for(int i=1;i<Max_Kernel_Length;i=i+2)
	{
		blur(src,dst,Size(i,i),Point(-1,-1));
		if(display_dst(Delay_Blur)!=0)
			return 0;
	}

	if(display_caption("Gaussian Blur ")!=0)
		return 0;
	for(int i=1;i<Max_Kernel_Length;i=i+2)
	{
		GaussianBlur(src,dst,Size(i,i),0,0);
		if(display_dst(Delay_Blur)!=0)
			return 0;
	}

	if(display_caption("Median Blur ")!=0)
		return 0;
	for(int i=1;i<Max_Kernel_Length;i=i+2)
	{
		medianBlur(src,dst,i);
		if(display_dst(Delay_Blur)!=0)
			return 0;
	}

	if(display_caption("Bilateral Blur ")!=0)
		return 0;
	for(int i=1;i<Max_Kernel_Length;i=i+2)
	{
		bilateralFilter(src,dst,i,i*2,i/2);
		if(display_dst(Delay_Blur)!=0)
			return 0;
	}

	display_caption(" End: Press a key! ");
	waitKey(0);
	return 0;
}

int display_caption(const char* caption)
{
	dst= Mat::zeros(src.size(),src.type());
	putText(dst,caption,Point(src.cols/4,src.rows/2),FONT_HERSHEY_COMPLEX,1,Scalar(255,255,255));
	imshow(window_name,dst);
	int c=waitKey(Delay_Caption);
	if(c>=0)
		return -1;

	return 0;
}

int display_dst(int delay)
{
	imshow(window_name,dst);
	int c=waitKey(delay);
	if(c>=0)
		return -1;

	return 0;
}