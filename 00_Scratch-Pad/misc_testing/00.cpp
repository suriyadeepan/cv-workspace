#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;

int main()
{
	Mat img = imread("01.jpg",CV_LOAD_IMAGE_UNCHANGED);

	if(img.empty())
	{
		printf("cant load image");
		return -1;
	}


	namedWindow("image",CV_WINDOW_AUTOSIZE);

	imshow("image",img);

	waitKey(0);


	return 0;
}

