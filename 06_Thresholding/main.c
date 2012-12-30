/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/thresholding/]

Modified by RPS Deepan- 29/12/2012
	splits the input image into
	 3 channels and extracts the
	  red regions alone by thresholding
	   technique




*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

IplImage* bgrThresh(IplImage** img)
{

	/*
	 * initialize 3 grayscale images
	 *  to store 3 channels of img
	 */
	IplImage* red=cvCreateImage(cvGetSize(*img),8,1);
	IplImage* green=cvCreateImage(cvGetSize(*img),8,1);
	IplImage* blue=cvCreateImage(cvGetSize(*img),8,1);

	// split src into 3 channels
	cvSplit(*img, blue, green, red, NULL);


	/*
		 * to threshold red region alone
		 *  we perform the following operation
		 *   result = red - (blue + green)
		 */
		cvAdd(blue, green, green,NULL);
		cvSub(red, green, red,NULL);

		/*
		 * start actual thresholding
		 *  a threshold value of 20 is given
		 */
		cvThreshold(red, red, 20, 255, CV_THRESH_BINARY);


	return red;

}// end of method bgrThreshold()...


int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage("061.png",CV_LOAD_IMAGE_UNCHANGED);
	IplImage* bgrThreshOp=cvCreateImage(cvGetSize(src),8,1);

	cvStartWindowThread();


	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}



	// display original input image
	cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
	cvShowImage("input",src);

	cvWaitKey(0);

	bgrThreshOp=bgrThresh(&src);

	cvNamedWindow("redW",CV_WINDOW_AUTOSIZE);
	cvShowImage("redW",bgrThreshOp);

	// wait from key event
	cvWaitKey(0);

	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	return 0;

}// end of main
