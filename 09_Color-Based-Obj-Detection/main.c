/*

Created by RPS Deepan- 02/01/2012
	a program for training and object detection
	 based on color based thresholding
	  - hue range is found by training
	     from a cropped out region of object
	  - using the hue range src image containing
	     object is thresholded
	  - thresholded image is filetered using
	     open and close morph ops

*/



#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int threshVal;


IplImage* addBrightness(IplImage* img)
{
	cvAddS(img,cvScalar(50,50,50,0),img,NULL);
	return img;
}

void trainImage(IplImage* img)
{
	// variable for iterating
	int x=0,y=0;




	IplImage* temp = cvCloneImage(img);

	// covert bgr image (img) to HSV format
	cvCvtColor(img,temp,CV_BGR2HSV);

	/* initialize 3 grayscale images to store 3 channels of img	 */
	IplImage* hue = cvCreateImage(cvGetSize(temp),8,1);
	/*IplImage* sat=cvCreateImage(cvGetSize(*img),8,1);
	IplImage* val=cvCreateImage(cvGetSize(*img),8,1);*/

	// split src into 3 channels
	cvSplit(temp, hue, NULL,NULL, NULL);
	// display hue
	cvNamedWindow("HUE",CV_WINDOW_NORMAL);
	cvShowImage("HUE",hue);

	int pixelValue=cvGetReal2D(hue,(hue->height)/2,(hue->width)/2);

	printf("Height: %d, Width: %d ",hue->height,hue->width);
	printf("@ (%d,%d)",(hue->width)/2,(hue->height)/2);
	printf("\nPIXEL VALUE (INIT): %d\n\n",pixelValue);


	int sumOfVals = 0;

	for ( y = 0 ; y < hue->height ; y++ ) {
		for ( x = 0 ; x < hue->width ; x++ ) {
			//printf("\nx: %d y: %d",x,y);
			pixelValue = cvGetReal2D ( hue, y, x ) ;

			sumOfVals = pixelValue + sumOfVals;

		}
	}


	threshVal = sumOfVals/((hue->height)*(hue->width)) ;

	// release memory
	cvDestroyWindow("HUE");
	cvReleaseImage(&hue);
	cvReleaseImage(&temp);







	printf("\nThresh: %d \n",threshVal);


}


/*
 * this method segments the input image
 *  based on a range of Hue value
 */
IplImage* hsvThreshold(IplImage* img,int threshVal)
{
	// covert bgr image (img) to HSV format
	cvCvtColor(img,img,CV_BGR2HSV);

	/* initialize 3 grayscale images  to store 3 channels of img */
	IplImage* hue=cvCreateImage(cvGetSize(img),8,1);

	// split src into 3 channels
	cvSplit(img, hue, NULL, NULL, NULL);



	/* thresholding the image based on  a hue value of range (174/2 to 186/2)
	 *   this corresponds to light blue found from gimp  */



	//cvInRangeS(hue, cvScalar((*range)[0], 0, 0,0), cvScalar((*range)[1], 255, 255,0),hue);
	cvInRangeS ( hue, cvScalar ( threshVal-5, 0, 0 ,0 ),
					 cvScalar ( threshVal + 5, 255, 255,0 ),hue);

	// return resulting thresholded image
	return hue;

}// end of method hsvThreshold()...


IplImage* addContrast(IplImage* img)
{
	cvConvertScale(img,img,2,0);
	return img;
}

IplImage* invertImg(IplImage* img)
{
	cvNot(img,img);
	return img;
}

int main(int argc, char* argv[])
{



		IplImage* detectionSrc=cvLoadImage(argv[2],CV_LOAD_IMAGE_UNCHANGED);
	//	IplImage* img;

	IplImage* trainSrc=cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	cvStartWindowThread();
	cvNamedWindow("TrainingSrc",CV_WINDOW_NORMAL);
	cvShowImage("TrainingSrc",trainSrc);
	//cvWaitKey(0);


	IplImage* opImg=cvCreateImage(cvGetSize(detectionSrc),8,1);
	IplImage* temp=cvCreateImage(cvGetSize(detectionSrc),8,1);	

	// display src image
	cvNamedWindow("Src",CV_WINDOW_NORMAL);
	cvShowImage("Src",detectionSrc);

	//cvWaitKey(0);

	trainImage(trainSrc);

	printf("No prob here...");

	opImg=hsvThreshold(detectionSrc,threshVal);

	printf("No prob here...");

	// display op image
	cvNamedWindow("Output",CV_WINDOW_NORMAL);
	cvShowImage("Output",opImg);

	// save op to file
	cvSaveImage("op-img.jpg",opImg,0);

	// Noise Filtering
	// get mask strength as input from user
	int mask_strength;
	printf("MASK STRENGTH: ");
	scanf("%d",&mask_strength);

	// apply mask...
	// close
	cvMorphologyEx(opImg,opImg,temp,NULL,CV_MOP_CLOSE,mask_strength);
	// open
	cvMorphologyEx(opImg,opImg,temp,NULL,CV_MOP_OPEN,mask_strength);

	// display filtered image
	cvNamedWindow("filtered",CV_WINDOW_NORMAL);
	cvShowImage("filtered",opImg);
	cvWaitKey(0);

	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&trainSrc);
	cvReleaseImage(&detectionSrc);
	cvReleaseImage(&opImg);
	//cvWaitKey(0);

	return 0;

}// end of main

