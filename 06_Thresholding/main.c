/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/thresholding/]

Modified by RPS Deepan- 29/12/2012


*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage("061.png",CV_LOAD_IMAGE_UNCHANGED);

	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}


	/*
	 * initialize 3 grayscale images
	 *  to store 3 channels of src
	 */
	IplImage* red=cvCreateImage(cvGetSize(src),8,1);
	IplImage* green=cvCreateImage(cvGetSize(src),8,1);
	IplImage* blue=cvCreateImage(cvGetSize(src),8,1);

	// split src into 3 channels
	cvSplit(src, blue, green, red, NULL);


	cvNamedWindow("input",CV_WINDOW_NORMAL);
	cvShowImage("input",src);

	/*

	cvNamedWindow("blueW",CV_WINDOW_NORMAL);
	cvShowImage("blueW",blue);


	cvNamedWindow("greenW",CV_WINDOW_NORMAL);
	cvShowImage("greenW",green);


	cvNamedWindow("redW",CV_WINDOW_NORMAL);
	cvShowImage("redW",red);

	*/

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

	cvNamedWindow("redW",CV_WINDOW_NORMAL);
	cvShowImage("redW",red);

	// wait from key event
	cvWaitKey(0);

	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	return 0;

}
