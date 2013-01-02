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


IplImage* addBrightness(IplImage** img)
{
	cvAddS(*img,cvScalar(50,50,50,0),*img,NULL);

	return *img;

}




int* trainImage(IplImage** img)
{
		// variable for iterating
		int x=0,y=0;

		// variables for finding and storing range
		int max,min;
		int* range=malloc(sizeof(int)*2 + 1);



			// covert bgr image (img) to HSV format
			cvCvtColor(*img,*img,CV_BGR2HSV);


			/*
			 * initialize 3 grayscale images
			 *  to store 3 channels of img
			 */
			IplImage* hue=cvCreateImage(cvGetSize(*img),8,1);
			/*IplImage* sat=cvCreateImage(cvGetSize(*img),8,1);
			IplImage* val=cvCreateImage(cvGetSize(*img),8,1);*/

			// split src into 3 channels
			cvSplit(*img, hue, NULL,NULL, NULL);

			int pixelValue=cvGetReal2D(hue,y,x);
			max=pixelValue;
			min=max;



			for(y=0;y<hue->height;y++)
			{
				for(x=0;x<hue->width;x++)
				{

					//printf("\nx: %d y: %d",x,y);


						pixelValue=cvGetReal2D(hue,y,x);

					// printf(" pixel vale: %d",pixelValue);

						if(pixelValue<10)
							continue;


						if(pixelValue > max)
							max=pixelValue;

						if(pixelValue < min)
							min=pixelValue;

				}
			}



			// release memory
			cvReleaseImage(&hue);

			range[0]=min;
			range[1]=max;


	return range;
}


/*
 * this method segments the input image
 *  based on a range of Hue value
 */
IplImage* hsvThreshold(IplImage** img,int** range)
{
		// covert bgr image (img) to HSV format
		cvCvtColor(*img,*img,CV_BGR2HSV);


		/*
		 * initialize 3 grayscale images
		 *  to store 3 channels of img
		 */
		IplImage* hue=cvCreateImage(cvGetSize(*img),8,1);


		// split src into 3 channels
		cvSplit(*img, hue, NULL, NULL, NULL);

		printf("\nRange: %d %d\n",(*range)[0],(*range)[1]);

		/*
		 * thresholding the image based on
		 *  a hue value of range (174/2 to 186/2)
		 *   this corresponds to light blue
		 *    found from gimp
		 */
		cvInRangeS(hue, cvScalar((*range)[0], 0, 0,0), cvScalar((*range)[1], 255, 255,0),hue);

	// return resulting thresholded image
	return hue;

}// end of method hsvThreshold()...


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



int main(int argc, char* argv[])
{
	// variable for storing range
	int* range=malloc(sizeof(int)*2 + 1);

	// load an image from file
	//	IplImage* src=cvLoadImage("00.jpg",CV_LOAD_IMAGE_UNCHANGED);
	//	IplImage* img;


	IplImage* trainSrc=cvLoadImage("09.jpg",CV_LOAD_IMAGE_UNCHANGED);
	IplImage* detectionSrc=cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);
	IplImage* opImg=cvCreateImage(cvGetSize(detectionSrc),8,1);
	IplImage* temp=cvCreateImage(cvGetSize(detectionSrc),8,1);



	cvStartWindowThread();

	// display src image
		cvNamedWindow("Src",CV_WINDOW_NORMAL);
		cvShowImage("Src",detectionSrc);

		cvWaitKey(0);

	range=trainImage(&trainSrc);

	printf("\nRange: %d to %d\n",range[0],range[1]);


	opImg=hsvThreshold(&detectionSrc,&range);


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
