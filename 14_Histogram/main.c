/*
 *	Created by RPS Deepan - 07-01-2013
 *
 *		Modified by RPS Deepan - 20-03-2013
 *		ref:
 *  		[http://www.aishack.in/2010/07/drawing-histograms-in-opencv/]
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>

IplImage* drawHistogram(CvHistogram* hist)
{
	// Scale
	int scaleX = 2;
	int scaleY = 2;


	float histMax = 0;

	cvGetMinMaxHistValue(hist, 0, &histMax, 0, 0);

	// create blank image
	IplImage* imgHist = cvCreateImage(cvSize(256*scaleX, 64*scaleY), 8 ,1);
	cvZero(imgHist);


	// iterate thro' bins and render out graphics...
	int i=0;
	for(i=0;i<255;i++)
	    {
	        float histValue = cvQueryHistValue_1D(hist, i);
	        float nextValue = cvQueryHistValue_1D(hist, i+1);

	        CvPoint pt1 = cvPoint(i*scaleX, 64*scaleY);
	        CvPoint pt2 = cvPoint(i*scaleX+scaleX, 64*scaleY);
	        CvPoint pt3 = cvPoint(i*scaleX+scaleX, (64-nextValue*64/histMax)*scaleY);
	        CvPoint pt4 = cvPoint(i*scaleX, (64-histValue*64/histMax)*scaleY);

	        int numPts = 5;
	        CvPoint pts[] = {pt1, pt2, pt3, pt4, pt1};

	        cvFillConvexPoly(imgHist, pts, numPts, cvScalar(255,0,0,0),8,0);
	    }






	return imgHist;


}

/*
 * 	---------- MAIN -----------
 */

int main(int argc, char* argv[])
{
	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	// get HSV form of image
	IplImage* hsvSrc = cvCreateImage(cvGetSize(src),8,3);
	cvCvtColor(src,hsvSrc,CV_BGR2HSV);

	// initialize Histogram
	int numBins = 256;
    	CvHistogram *hist = cvCreateHist(1,&numBins,CV_HIST_ARRAY,NULL,1);
    	cvClearHist(hist);


	// Separate hsv image into 3 channels
	IplImage* hueCh = cvCreateImage(cvGetSize(hsvSrc),8,1);
	IplImage* satCh = cvCreateImage(cvGetSize(hsvSrc),8,1);
	IplImage* valCh = cvCreateImage(cvGetSize(hsvSrc),8,1);

		cvSplit(hsvSrc,hueCh,satCh,valCh,NULL);


	// **** Rendering Histogram ****

	// --- Hue Channel ---
	cvCalcHist(&hueCh,hist, 0, NULL);
		IplImage* imgHistHue = drawHistogram(hist);
		cvClearHist(hist);

	// --- Sat Channel ---
	cvCalcHist(&satCh, hist, 0, NULL);
	IplImage* imgHistSat = drawHistogram(hist);
		cvClearHist(hist);

	// --- Val Channel ---
	cvCalcHist(&valCh, hist, 0, NULL);
		IplImage* imgHistVal = drawHistogram(hist);
		cvClearHist(hist);

	cvStartWindowThread();

	// display histogram
	cvNamedWindow("Hue",CV_WINDOW_NORMAL);
	cvNamedWindow("Sat",CV_WINDOW_NORMAL);
	cvNamedWindow("Val",CV_WINDOW_NORMAL);

	cvShowImage("Hue",imgHistHue);
	cvShowImage("Sat",imgHistSat);
	cvShowImage("Val",imgHistVal);


	// wait for key press
	cvWaitKey(0);

	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	cvReleaseImage(&hueCh);
	cvReleaseImage(&satCh);
	cvReleaseImage(&valCh);

	cvReleaseImage(&imgHistHue);
	cvReleaseImage(&imgHistSat);
	cvReleaseImage(&imgHistVal);

	return 0;
}// end of main

