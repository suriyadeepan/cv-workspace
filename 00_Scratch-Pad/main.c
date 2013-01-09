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

void captureImage(IplImage** img)
{
	system("rm 002.avi");
	system(" ffmpeg -f video4linux2 -r 25 -s 640x480 -i /dev/video1 -y -t 4 002.avi");



		CvCapture* capture = 0;

		capture = cvCreateFileCapture("002.avi");

		if(!capture)
		{
			return;
		}





		int i=0;
		while(1)
		{

		*img = cvQueryFrame(capture);

		if(!*img)
			break;


		i++;

		if(i>10)
			break;


		cvWaitKey(25);



		}



		cvNamedWindow("Source",CV_WINDOW_AUTOSIZE);
			cvShowImage("Source",*img);

			cvWaitKey(0);


		// release capture
		cvReleaseCapture(&capture);
		cvDestroyWindow("Source");


}

int main(int argc, char* argv[])
{
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

	IplImage* imgFromCam = 0;

	cvStartWindowThread();

	captureImage(&imgFromCam);


	cvNamedWindow("Source1",CV_WINDOW_AUTOSIZE);
	cvShowImage("Source1",imgFromCam);






	// wait for key event
	cvWaitKey(0);



	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&imgFromCam);


	return 0;

}// end of main
