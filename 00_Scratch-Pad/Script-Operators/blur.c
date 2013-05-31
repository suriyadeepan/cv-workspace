
#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int blur_level = 11;

	// image container...
	IplImage* img;


	img = cvLoadImage("current.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	scanf("%d",&blur_level);

	// set limits 0-120
	if(blur_level<=0)
		blur_level=1;

	else if(blur_level>120)
		blur_level=119;


	// if its even - some errors arise
	//  so increment by 1 if even...
	if(blur_level%2==0)
		blur_level++;


	// smooth the image...
	cvSmooth(img, img, CV_GAUSSIAN, blur_level, 0, 0, 0);


	//  save to blurred.jpg...
	cvSaveImage("current.jpg", img, 0);

	cvReleaseImage( &img );



	return 0;
}// end of main
