/*

Created by RPS Deepan- 31/12/2012
	- added a method addBrightness()
	   to increase overall brightness of img

Modified by RPS Deepan- 31/12/2012
	- added a method addContrast()
	   uses cvConvertScale() to increase
	    constrast by a factor(double)

*/



#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


IplImage* addBrightness(IplImage** img)
{
	cvAddS(*img,cvScalar(50,50,50,0),*img,NULL);

	return *img;

}

IplImage* addContrast(IplImage** img)
{
	cvConvertScale(*img,*img,2,0);

	return *img;
}


int main(int argc, char* argv[])
{


	// load an image from file
	IplImage* src=cvLoadImage("00.jpg",CV_LOAD_IMAGE_UNCHANGED);



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

	// wait for key event
	cvWaitKey(0);

	cvDestroyWindow("input");

	src=addContrast(&src);



	// display brighter image
	cvNamedWindow("Brighter",CV_WINDOW_AUTOSIZE);
	cvShowImage("Brighter",src);


	// wait for key event
	cvWaitKey(0);



	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);


	return 0;

}// end of main
