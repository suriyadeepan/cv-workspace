/* 
Expt by Selvakumar - 24/09/2012
  Loads a image and perform blur operation over the image 
Modified by RPS Deepan - 29/12/2012
  Gets the blur level as input from user
	runs this in a loop
*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int blur_level = 11;
	char key='q';

	// image container...
	IplImage* img;

	// starts the window thread...
	// is necessary to destroy window...
	cvStartWindowThread();

	// do...while loop starts here
	do{

	 img = cvLoadImage("02.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// get blur level from user
	printf("Enter the level of blurring: ");
	scanf("%d", &blur_level);

	// smooth the image...
	//  save to blurred.jpg...
	cvSmooth(img, img, CV_GAUSSIAN, blur_level, 0, 0, 0);
	cvSaveImage("blurred.jpg", img, 0);

	// display image in the "Blurred" window...
	cvNamedWindow("Blurred", CV_WINDOW_AUTOSIZE);
	cvShowImage("Blurred", img);

	// get input from user
	key = cvWaitKey(0);

	// destroy window and release image...
	cvDestroyWindow("Blurred");
	cvReleaseImage( &img );

	// if 'q' is pressed by user (key)
	//  break out of loop
	//   else continue...
	}while(key!='q');
	// end of do...while loop




	return 0;
}// end of main
