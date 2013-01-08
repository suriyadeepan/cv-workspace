/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/thresholding/]

Modified by RPS Deepan- 30/12/2012
	split the input image into
	 3 channels and extract a particular
	  region based on HSV values or
	   BGR values by Thresholding technique
*/



#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.



/* this method - bgrThresh()
 *  splits the input image into
 *   3 channels and extracts the
 *    red regions alone by thresholding
 *
 */
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


/*
 * this method segments the input image
 *  based on a range of Hue value
 */
IplImage* hsvThreshold(IplImage** img)
{
		// covert bgr image (img) to HSV format
		cvCvtColor(*img,*img,CV_BGR2HSV);


		/*
		 * initialize 3 grayscale images
		 *  to store 3 channels of img
		 */
		IplImage* hue=cvCreateImage(cvGetSize(*img),8,1);
		IplImage* sat=cvCreateImage(cvGetSize(*img),8,1);
		IplImage* val=cvCreateImage(cvGetSize(*img),8,1);

		// split src into 3 channels
		cvSplit(*img, hue, sat, val, NULL);

		cvNamedWindow("hue",CV_WINDOW_AUTOSIZE);
		cvShowImage("hue",hue);


		cvNamedWindow("sat",CV_WINDOW_AUTOSIZE);
		cvShowImage("sat",sat);


		cvNamedWindow("val",CV_WINDOW_AUTOSIZE);
		cvShowImage("val",val);
		/*
		 * thresholding the image based on
		 *  a hue value of range (174/2 to 186/2)
		 *   this corresponds to light blue
		 *    found from gimp
		 */
		cvInRangeS(hue, cvScalar(174/2, 0, 0,0), cvScalar(186/2, 255, 255,0),hue);

	// return resulting thresholded image
	return hue;

}// end of method hsvThreshold()...


int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage("061.png",CV_LOAD_IMAGE_UNCHANGED);
	IplImage* bgrThreshOp=cvCreateImage(cvGetSize(src),8,1);
	IplImage* hsvThreshOp=cvCreateImage(cvGetSize(src),8,1);

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

	/*
	 * this method segments the input image
	 *  based on a range of Hue values
	 *   returns the resluting thresholded image
	 */
	hsvThreshOp = hsvThreshold(&src);

	// display resulting image
	cvNamedWindow("hsvW",CV_WINDOW_AUTOSIZE);
	cvShowImage("hsvW",hsvThreshOp);

	// wait for key event
	cvWaitKey(0);



	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	return 0;

}// end of main
