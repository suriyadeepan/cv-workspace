/*
 * Created by RPS Deepan - 05-01-2013
 *  reference - Learning OpenCV - Chapter 6 : Image Transforms
 *  		  - aishack.in [http://www.aishack.in/2010/04/hough-transform-in-opencv/]
 *
 *		1. testing the method cvHoughLines2()
 *
 *
 */


#include<cv.h>
#include<highgui.h>

#include<stdio.h>

int main(int argc, char* argv[])
{

	IplImage* src = cvLoadImage(argv[1],0);
	IplImage* temp = cvCloneImage(src);

	cvStartWindowThread();

	// display source...
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	// wait for key press
	cvWaitKey(0);

		// storage space
	 CvMemStorage* storage = cvCreateMemStorage(0);

	 // a sequence for storing lines...
	 CvSeq* lines = 0;

	 // resolution parameters
	 double rho=1,theta=CV_PI/180;

	 // threshold value
	 int threshold = 100;

	 // canny filter
	 cvCanny(src, src, 50, 245, 3);

	 // do hough transform...
	 lines = cvHoughLines2( src, storage, CV_HOUGH_STANDARD,
	  rho, theta, threshold, 0,0);

	 // index variable for iteration
	 int i=0;

	 for(i = 0; i < lines->total; i++)
	 {

		 CvPoint* pts=(CvPoint*)cvGetSeqElem(lines,i);
		 cvLine(temp,pts[0],pts[1],CV_RGB(0,255,0),1,8,0);


     }

	 cvDestroyWindow("Source");

	 // display output...
	 cvNamedWindow("HoughOp",CV_WINDOW_NORMAL);
	 cvShowImage("HoughOp",temp);


	// wait for key press
	cvWaitKey(0);

	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&temp);
	cvReleaseMemStorage(&storage);



	return 0;

}// end of main...








