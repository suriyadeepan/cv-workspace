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
	IplImage* src=cvLoadImage("06.jpg",CV_LOAD_IMAGE_UNCHANGED);

	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}

	cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
	cvShowImage("input",src);

	// wait from key event
	cvWaitKey(0);

	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	return 0;

}
