
#include <stdio.h>	
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int erode_level = 11;

	// image container...
	IplImage* img;


	img = cvLoadImage("current.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// get erode level from user
	scanf("%d", &erode_level);

	// set limits 0-120
	if(erode_level<=0)
		erode_level=1;

	else if(erode_level>120)
		erode_level=119;



	// erode the image...

	cvErode(img, img, NULL,erode_level);

	/*
	 *
	 * Similarly, dilation can be perfomed...
	 * cvDilate(img,img,NULL,erode_level);
	 *
	 */

	//  save to eroded.jpg...
	cvSaveImage("current.jpg", img, 0);
	
	cvReleaseImage( &img );

	return 0;
}// end of main
