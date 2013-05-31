
#include <stdio.h>	
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int dilate_level = 11;

	// image container...
	IplImage* img;


	img = cvLoadImage("current.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// get erode level from user
	scanf("%d", &dilate_level);

	// set limits 0-120
	if(dilate_level<=0)
		dilate_level=1;

	else if(dilate_level>120)
		dilate_level=119;

	 cvDilate(img,img,NULL,dilate_level);

	//  save to current.jpg...
	cvSaveImage("current.jpg", img, 0);
	
	cvReleaseImage( &img );

	return 0;
}// end of main
