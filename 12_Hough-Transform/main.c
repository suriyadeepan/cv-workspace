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
#include<math.h>
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
	 //CvVect32f lines;

	 // resolution parameters
	 double rho=1,theta=0.01;

	 // threshold value
	 int threshold = 100;

	 // canny filter
	 cvCanny(src, src, 50, 245, 3);

	 // display canny image
	 cvNamedWindow("Canny",CV_WINDOW_NORMAL);
	 cvShowImage("Canny",src);

	 cvWaitKey(0);

	 cvDestroyWindow("Canny");

	 // do hough transform...
	 lines = cvHoughLines2( src, storage, CV_HOUGH_STANDARD,
	  rho, theta, threshold, 0,0);

	 // index variable for iteration
	 int i=0;

	 /*

	 for(i = 0; i < lines->total; i++)
	 {

		 CvPoint* pts=(CvPoint*)cvGetSeqElem(lines,i);
		 printf("\nPoints 0 0: %f %f",pts[0].x,pts[0].y);
		 printf("\nPoints 1 1: %f %f",pts[1].x,pts[1].y);
		 //cvLine(temp,pts[0],pts[1],CV_RGB(0,255,0),1,8,0);


     }*/


	 // extract points (x,y) from (rho,theta) op of
	 //  houghLines2() method...

	 for(  i = 0; i < lines->total; i++ )
	 {

		 float* line = (float*)cvGetSeqElem(lines,i);

		 float rho = line[0];
		 float theta = line[1];

		 CvPoint pt1, pt2;

	   double a = cos(theta), b = sin(theta);
	   double x0 = a*rho, y0 = b*rho;
	   pt1.x = cvRound(x0 + 1000*(-b));
	   pt1.y = cvRound(y0 + 1000*(a));
	   pt2.x = cvRound(x0 - 1000*(-b));
	   pt2.y = cvRound(y0 - 1000*(a));
	   cvLine( temp, pt1, pt2, CV_RGB(255,0,0), 1,8,0);
	 }



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








