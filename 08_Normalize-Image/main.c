/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/normalized-rgb/]

Modified by RPS Deepan- 31/12/2012
	get an image as input - split into 3 channels
	 do R/(R+G+B) for each pixel in each channel
	  merge 3 channels to get noramlized image

	- though normalized image seems erratic

*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

IplImage* normalizeImage(IplImage** img)
{
	// index variables
	int x=0,y=0;


	IplImage* red = cvCreateImage(cvGetSize(*img), 8, 1);
	IplImage* green = cvCreateImage(cvGetSize(*img), 8, 1);
	IplImage* blue = cvCreateImage(cvGetSize(*img), 8, 1);

	IplImage* result = cvCreateImage(cvGetSize(*img),8,3);

	// images for storing temp data
	IplImage* redAvg = cvCreateImage(cvGetSize(*img), 8, 1);
	IplImage* greenAvg = cvCreateImage(cvGetSize(*img), 8, 1);
	IplImage* blueAvg= cvCreateImage(cvGetSize(*img), 8, 1);

	// get size of image
	int width=(*img)->width;
		int height=(*img)->height;

	// split img into 3 channels
	cvSplit(*img,red,green,blue,NULL);

	// iterate thro' each pixel
	for(x=0;x<width;x++)
	{
		for(y=0;y<height;y++)
		{
			// get pixel value of each channel
			int redValue = cvGetReal2D(red, y, x);
			int greenValue = cvGetReal2D(green, y, x);
			int blueValue = cvGetReal2D(blue, y, x);

			/*
			 * find sum of particular pixel values
			 *  @ R,G,B channels
			 */
			double sum = redValue+greenValue+blueValue;

			/*
			 * do (R/sum),(B/sum),(G/sum)
			 *  put them in the corresponding channel
			 */
			cvSetReal2D(redAvg, y, x, (redValue/sum)*255);
			cvSetReal2D(greenAvg, y, x, (greenValue/sum)*255);
			cvSetReal2D(blueAvg, y, x, (blueValue/sum)*255);
		}
	}// end of for loop


	// merge the normalized channels
	//  to get result
	cvMerge(blueAvg, greenAvg, redAvg, NULL, result);

	// release image memory
	cvReleaseImage(&red);
	cvReleaseImage(&green);
	cvReleaseImage(&blue);
	cvReleaseImage(&redAvg);
	cvReleaseImage(&blueAvg);
	cvReleaseImage(&greenAvg);

	// return normalizedImage
	return result;
}// end of method normalizeImage()...



int main(int argc, char **argv)
{

	// load an image from file
	IplImage* src=cvLoadImage("081.jpg",CV_LOAD_IMAGE_UNCHANGED);
	IplImage* normalizedImg=cvCreateImage(cvGetSize(src),8,3);



	// if src cant be loaded , quit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}

	cvStartWindowThread();

	// display original image
	cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
	cvShowImage("input",src);

	// wait for key press
	cvWaitKey(0);

	// normalize the image src
	normalizedImg = normalizeImage(&src);

	// display normalized image
	cvNamedWindow("normalized",CV_WINDOW_AUTOSIZE);
	cvShowImage("normalized",normalizedImg);

	// wait for key press
	cvWaitKey(0);

	// release memory
	cvDestroyWindow("normalized");
	cvReleaseImage(&src);
	cvReleaseImage(&normalizedImg);

	return 0;

}// end of main...
