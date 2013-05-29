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
	IplImage* threshImg = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* harrisImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);

	cvStartWindowThread();

	//cvNamedWindow("Source",CV_WINDOW_NORMAL);
	//cvShowImage("Source",src);

	cvThreshold(src,threshImg,100,255,CV_THRESH_BINARY);

	//cvNamedWindow("Thresholded",CV_WINDOW_NORMAL);
	//cvShowImage("Thresholded",threshImg);

	cvCornerHarris(threshImg,harrisImg,20,5,0.04);



	// display op
	/*
	cvNamedWindow("Corners",CV_WINDOW_NORMAL);
	cvShowImage("Corners",harrisImg);
	*/



	// Blur
	// smooth the image...
	//cvSmooth(harrisImg, harrisImg, CV_GAUSSIAN, 19, 0, 0, 0);

	/*
	// MORPH
	// a temp buffer for morph
	IplImage* temp = cvCreateImage(cvGetSize(harrisImg),harrisImg->depth,1);
	IplImage* morphedHarrisImg = cvCreateImage(cvGetSize(harrisImg),harrisImg->depth,1);
	*/

	/*
	// operating on the harris output image
	cvMorphologyEx(harrisImg,morphedHarrisImg,temp,NULL,CV_MOP_ERODE,3);
	cvMorphologyEx(morphedHarrisImg,morphedHarrisImg,temp,NULL,CV_MOP_CLOSE,7);

	cvSmooth(morphedHarrisImg,morphedHarrisImg, CV_GAUSSIAN, 19, 0, 0, 0);

	// display morphed image
	cvNamedWindow("Morphed",CV_WINDOW_NORMAL);
	cvShowImage("Morphed",morphedHarrisImg);

	*/

	IplImage* cannyImg = cvCreateImage(cvGetSize(harrisImg),8,1);

	cvConvertScaleAbs(harrisImg,cannyImg,1,0);
	cvCanny(cannyImg,cannyImg,8,8,3);


	// display canny image
	cvNamedWindow("canny",CV_WINDOW_NORMAL);
	cvShowImage("canny",cannyImg);




	cvWaitKey(0);

	cvDestroyAllWindows();

	cvReleaseImage(&src);
	cvReleaseImage(&harrisImg);


	return 0;
}// end of main

