#include <stdio.h>
#include <highgui.h>
#include <cv.h>

int main()
{
	IplImage* src = cvLoadImage("current.jpg",CV_LOAD_IMAGE_UNCHANGED);
	cvCvtColor(src,src,CV_BGR2HSV);
	cvSaveImage("current.jpg",src,0);

	cvReleaseImage(&src);
	return 0;

}
		
