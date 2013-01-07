/*
 *	Created by RPS Deepan - 07-01-2013
 *
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>

int main(int argc, char* argv[])
{
	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	// get HSV form of image
	IplImage* hsvSrc = cvCreateImage(cvGetSize(src),8,3);
	cvCvtColor(src,hsvSrc,CV_BGR2HSV);


	// seperate hsv image into 3 channels
	IplImage* hPlane = cvCreateImage(cvGetSize(hsvSrc),8,1);
	IplImage* sPlane = cvCreateImage(cvGetSize(hsvSrc),8,1);
	IplImage* vPlane = cvCreateImage(cvGetSize(hsvSrc),8,1);
	IplImage* planes[] = {hPlane,sPlane};

	cvSplit(hsvSrc,hPlane,sPlane,vPlane,NULL);

	// Build histogram
	int hBins = 30, sBins = 32;

	// setup hist
	CvHistogram* hist;
	{
		// sizes of each dimension's bins
		int histSize[] = { hBins, sBins };

		// individual dimension ranges
		// hue => 0 - 180
		float hRanges[] = { 0,180 };
		// sat => 0 - 255
		float sRanges[] = { 0,255 };

		// ranges
		float* ranges[] = { hRanges, sRanges };

		// create histogram
		hist = cvCreateHist(2,histSize,CV_HIST_ARRAY,ranges,1);

	}// end of histogram DS hist

	// Compute Histogram
	cvCalcHist(planes,hist,0,0);

	// Normalize Histogram
	cvNormalizeHist(hist,1.0);


	// create an image to Visualize Histogram
	int scale = 10;
	IplImage* histImg = cvCreateImage(cvSize(hBins*scale,sBins*scale),8,3);
	cvZero(histImg);

	// get max value
	float maxValue = 0;
	cvGetMinMaxHistValue(hist,0,&maxValue,0,0);

	/*
	 *  iterate thro' each bin, find
	 *   bin values - calculate intensity
	 *    draw rectangle with that (color) intensity
	 */
	int h=0;
	int s=0;

	for(h=0; h < hBins; h++)
	{
		for(s=0; s < sBins; s++)
		{
			// get bin value
			float binVal = cvQueryHistValue_2D(hist,h,s);
			int intensity = cvRound((binVal/maxValue)*255);
			cvRectangle(histImg,cvPoint(h*scale,s*scale),
					cvPoint((h+1)*scale,(s+1)*scale),
					CV_RGB(intensity,intensity,intensity),-1,8,0);
		}
	}

	cvStartWindowThread();

	// display histogram
	cvNamedWindow("Hist",CV_WINDOW_FULLSCREEN);
	cvShowImage("Hist",histImg);




	// wait for key press
	cvWaitKey(0);

	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&hPlane);
	cvReleaseImage(&sPlane);
	cvReleaseImage(&vPlane);
	cvReleaseImage(&hsvSrc);
	cvReleaseImage(&histImg);

	return 0;
}// end of main

