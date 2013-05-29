/*
 *	Created by RPS Deepan - 28-05-2013
 *
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>


IplImage* adapThresh(IplImage* img)
{


	IplImage* thresh = cvCreateImage(cvGetSize(img),8,1);



	/*
	 *	*img -> thresh
	 *	max_val = 255
	 *	method = CV_ADAPTIVE_THRESH_MEAN_C
	 *	threshold type = CV_THRESH_BINARY
	 *	block_size = 3
	 *	param1 = 5
	 */

	cvAdaptiveThreshold(img,thresh,90,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,3,5);

	cvReleaseImage(&img);

	return thresh;

}



int main(int argc, char* argv[])
{
	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* harrisImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);

	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	cvCornerHarris(src,harrisImg,8,5,0.04);

	// display op
	cvNamedWindow("Corners",CV_WINDOW_NORMAL);
	cvShowImage("Corners",harrisImg);

	cvWaitKey(0);

	cvReleaseImage(&src);
	cvReleaseImage(&harrisImg);


	return 0;
}// end of main

