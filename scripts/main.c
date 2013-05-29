#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// Open the file "01.jpg".
	IplImage* img = cvLoadImage("01.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}


	// Show the image on the screen.
	cvNamedWindow("Sample Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Sample Image", img);

	// Wait for the user to press something on the graphical window.
	// Note: cvWaitKey() is needed for time to draw on the screen.
	cvWaitKey(0);

	// Free the resources.
	cvDestroyWindow("Sample Image");
	cvReleaseImage( &img );

	return 0;
}
