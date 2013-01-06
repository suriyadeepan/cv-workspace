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

void doHoughLineTransform(IplImage** src,IplImage** temp)
{

	// storage space
	 CvMemStorage* storage = cvCreateMemStorage(0);

	 // a sequence for storing lines...
	 CvSeq* lines = 0;
	 //CvVect32f lines;

	 // resolution parameters
	 double rho=1,theta=0.01;

	 // threshold value
	 int threshold = 240;

	 // canny filter
	 cvCanny(*src, *src, 20, 80, 3);

	 // display canny image
	 cvNamedWindow("Canny",CV_WINDOW_NORMAL);
	 cvShowImage("Canny",*src);

	 // wait for key press
	 cvWaitKey(0);

	 // destroy Canny window
	 cvDestroyWindow("Canny");

	 // do hough transform...
	 /*
	  * src -> image
	  * storage -> CvMemoryStorage (space for storage)
	  * CV_HOUGH_STANDARD -> method
	  * rho -> normal distance
	  * theta -> angle
	  * threshold -> 0-255 (i think)
	  * param1, param2 -> 0,0
	  *
	  */
	 lines = cvHoughLines2( *src, storage, CV_HOUGH_STANDARD,
	  rho, theta, threshold, 0,0);

	 // index variable for iteration
	 int i=0;


	 // extract points (x,y) from (rho,theta) op of
	 //  houghLines2() method...

	 for(  i = 0; i < lines->total; i++ )
	 {

		 // get sequence elements (single line
		 //  from array of lines)
		 float* line = (float*)cvGetSeqElem(lines,i);

		 // get rho,theta info from line
		 float rho = line[0];
		 float theta = line[1];

		 // points to store x,y
		 CvPoint pt1, pt2;

		 // rho = xcos(theta) + ysin(theta)
		 // get x,y from rho,theta
		 double a = cos(theta), b = sin(theta);
		 double x0 = a*rho, y0 = b*rho;
		 pt1.x = cvRound(x0 + 1000*(-b));
		 pt1.y = cvRound(y0 + 1000*(a));
		 pt2.x = cvRound(x0 - 1000*(-b));
		 pt2.y = cvRound(y0 - 1000*(a));

		 /*
		 printf("\nPoint 1: %d %d ",pt1.x,pt1.y);
		 printf("Point 2: %d %d\n",pt2.x,pt2.y);
		*/

		 // draw line connecting pt1 and pt2
		 cvLine( *temp, pt1, pt2, CV_RGB(255,0,0), 1,8,0);

			 }



	 // display output...
 	 cvNamedWindow("HoughOp",CV_WINDOW_NORMAL);
 	 cvShowImage("HoughOp",*temp);

 	 // wait for key press
 	 cvWaitKey(0);

 	 cvDestroyWindow("Canny");
 	 cvReleaseMemStorage(&storage);

}

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

	//doHoughLineTransform(&src,&temp);





	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&temp);





	return 0;

}// end of main...








