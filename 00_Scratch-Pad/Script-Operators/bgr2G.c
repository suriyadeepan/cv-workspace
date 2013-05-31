#include <stdio.h>
#include <highgui.h>
#include <cv.h>

int main()
{
	IplImage* src = cvLoadImage("current.jpg",CV_LOAD_IMAGE_UNCHANGED);
	IplImage* R = cvCreateImage(cvGetSize(src),8,1);
	cvSplit(src, NULL, R,NULL, NULL);
	cvSaveImage("current.jpg",R,0);

	cvReleaseImage(&src);
	cvReleaseImage(&R);
	return 0;

}
		
