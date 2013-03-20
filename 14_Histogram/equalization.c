/*
 *	Created by RPS Deepan - 20-03-2013
 *	ref: 	opencv_tutorials.pf
 *				[Histogram Equalization]
 *
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>

/*
 * 	---------- MAIN -----------
 */

int main(int argc, char* argv[])
{
	IplImage* origSrc = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);
	IplImage* hsvSrc = cvCreateImage(cvGetSize(origSrc),8,3);

	// convert to HSV mode
	cvCvtColor(origSrc,hsvSrc,CV_BGR2HSV);


	// Container to store final equalized image
	IplImage* equalizedImg = cvCreateImage(cvGetSize(hsvSrc),8,3);

	// Separate hsv image into 3 channels
		IplImage* hueCh = cvCreateImage(cvGetSize(hsvSrc),8,1);
		IplImage* satCh = cvCreateImage(cvGetSize(hsvSrc),8,1);
		IplImage* valCh = cvCreateImage(cvGetSize(hsvSrc),8,1);

	cvSplit(hsvSrc,hueCh,satCh,valCh,NULL);


	//cvEqualizeHist(hueCh,hueCh);
	//cvEqualizeHist(satCh,satCh);
	cvEqualizeHist(valCh,valCh);

	cvStartWindowThread();

	cvMerge(hueCh,satCh,valCh,NULL,equalizedImg);

	// convert resulting image to BGR form
	cvCvtColor(equalizedImg,equalizedImg,CV_HSV2BGR);

	// --- Display Source ---
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",origSrc);

	// --- Display Equalized Image ---
	cvNamedWindow("Equalized",CV_WINDOW_NORMAL);
	cvShowImage("Equalized",equalizedImg);

	cvSaveImage("/home/rps/Pictures/android-cv/equalized_pink_ball.jpg",equalizedImg,0);

	// wait for key press
	cvWaitKey(0);

	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&hsvSrc);
	cvReleaseImage(&equalizedImg);

	return 0;
}// end of main


