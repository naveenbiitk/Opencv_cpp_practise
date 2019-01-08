
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main(void)
{
	double alpha=0.5;
	double beta,input;

	Mat src1,src2,dst;

	cout<<" Simple linear blender "<<endl<<" Enter alpha[0-1]: ";
	cin>>input;

	if(input>=0 && input<=1)
		alpha=input;

	src1=imread("lion.jpg");
	src2=imread("naveen.jpg");

	beta = 1.0 - alpha;
	addWeighted(src1,alpha,src2,beta,0.0,dst);

	imshow("Linear Blend",dst);
	waitKey(0);

	return 0;

}