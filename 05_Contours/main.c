/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/an-introduction-to-contours/]

Modified by RPS Deepan- 29/12/2012
  Loads an image - detects the contours in it
  	  draws rectangles over the input image
  	  	  and displays as output

*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.



// the method contourDetect()
//  detect all contours and
//   draws them on to a copy of src
//    and returns it
IplImage* contourDetect(IplImage** img)
{

	// sequence for storing resulting contours
	CvSeq* contours;

	// sequence for temporarily storing points
	//  in a contour
	CvSeq* result;

	// memory storage space for storing contours
	// 0 -> default (64K)
	CvMemStorage *storage = cvCreateMemStorage(0);

	// ret -> this image is a copy of source image "img"
	//  on which contours are drawn and returned
	 IplImage* ret = cvCreateImage(cvGetSize(*img), 8, 3);

	// temp -> grayscale form of source image "img"
	//  for contour detection
	  IplImage* temp = cvCreateImage(cvGetSize(*img), 8, 1);

	// converting "img" to grayscale and
	//  and storing in temp
	 cvCvtColor(*img, temp, CV_BGR2GRAY);

	// find all contours in temp and
	//  store them in contours
	 cvFindContours(temp,storage, &contours,sizeof(CvContour),CV_RETR_LIST,
		        CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	// print total num. of contours
	 printf("\ncontours->total = %d\n", contours->total);

	// draw contours over the image "ret"
	 cvDrawContours(ret, contours, CV_RGB(0,255,0), CV_RGB(0,0,255),
	         2, 1, 8, cvPoint(0, 0));

	 // return image "ret"
	return ret;

} // end of method contourDetect()...


int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage("054.jpeg",CV_LOAD_IMAGE_UNCHANGED);

	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}


	// an image for showing contours
	IplImage* contourDrawn = 0;


	cvStartWindowThread();

	// the method contourDetect()
	//  detect all contours and
	//   draws them on to a copy of src
	//    and returns it
	contourDrawn = contourDetect(&src);

	// a window to display original source image
	cvNamedWindow("original",CV_WINDOW_NORMAL);
	cvShowImage("original", src);

	// wait for key event
	cvWaitKey(0);

	// a window to display contour drawn image
	cvNamedWindow("contours",CV_WINDOW_NORMAL);
	cvShowImage("contours",contourDrawn);


	// wait for key event
	cvWaitKey(0);

	// destroy windows and release img memory
	cvDestroyWindow("original");
	cvReleaseImage(&src);
	cvDestroyWindow("contours");
	cvReleaseImage(&contourDrawn);

	return 0;
}// end of main
