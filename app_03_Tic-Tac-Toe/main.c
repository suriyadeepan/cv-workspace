#include <cv.h>
#include <highgui.h>
#include <stdio.h>

IplImage* src;

int main(int argc, char **argv)
{
	src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);
	IplImage* gray = cvCreateImage(cvGetSize(src),8,1);

	cvCvtColor(src,gray,CV_BGR2GRAY);

	//cvSmooth(gray,gray,CV_GAUSSIAN,19,0,0,0);

	IplImage* thresholded = cvCreateImage(cvGetSize(gray),8,1);
	cvAdaptiveThreshold(gray,thresholded,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY_INV,3,5);


	IplImage* temp = cvCreateImage(cvGetSize(thresholded),thresholded->depth,1);



	cvNamedWindow("gray",CV_WINDOW_NORMAL);
	cvShowImage("gray",gray);

	cvNamedWindow("thresholded",CV_WINDOW_NORMAL);
	cvShowImage("thresholded",thresholded);

	cvWaitKey(0);

	// clean up
	cvDestroyAllWindows();
	cvReleaseImage(&gray);
	cvReleaseImage(&thresholded);


	return 0;


}


