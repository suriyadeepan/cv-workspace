/*

Created by RPS Deepan- 31/12/2012
	- added a method addBrightness()
	   to increase overall brightness of img

Modified by RPS Deepan- 31/12/2012
	- added a method addContrast()
	   uses cvConvertScale() to increase
	    constrast by a factor(double)
	- added a method to invert image

Modified by RPS Deepan- 02/01/2012
	- modified the main function to
	   play an avi file frame by frame
	    with varying contrasts and brightness
	- need to make this code chunk in main 
	   into a proper method...

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

IplImage* invertImg(IplImage** img)
{
	cvNot(*img,*img);

	return *img;
}

// ----NOTE----

/*
 * use of ffmpeg for recording video using webcam
 *  then iterate thro' frames and pick a frame
 *   - i => device node
 *   - y => overwrite file
 *   - f => v4l2
 *   - s => size
 *   - t => time of recording
 *
 */




int main(int argc, char* argv[])
{


	IplImage* frame;




	// a video capture obj
	CvCapture* capture = 0;
	capture = cvCreateFileCapture(argv[1]);

	// if its null
	if(!capture)
	{
		printf("capture obj is null!");
		return -1;
	}


	// window
	cvStartWindowThread();
	cvNamedWindow("Source",CV_WINDOW_AUTOSIZE);

	// iterate thro' all the frames
	while(1)
	{

		frame = cvQueryFrame(capture);

		if(!frame)
			break;

		// a small delay
		cvWaitKey(40);

		cvShowImage("Source",frame);

	}


	// release capture
	cvReleaseCapture(&capture);
	cvDestroyWindow("Source");
	cvReleaseImage(&frame);


	return 0;

}// end of main
