#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


IplImage* optimizeColor(IplImage* col_in,int divisor)
{
	int width = col_in->width, height = col_in->height,x,y;
	IplImage* col_out = cvCreateImage(cvGetSize(col_in),8,1);
//	printf("\n\n");
	for(x=0;x<width;x++)
	{
		for(y=0;y<height;y++)
		{
			// get pixel value of each channel

			int val = cvGetReal2D(col_in, y, x);

			//printf("\nVal @ %d,%d : %d",x,y,val);

			cvSetReal2D(col_out, y, x, val/divisor);

		}
	}// end of for loop


//	printf("\n\n");
	return col_out;


}


void red_theme_test(IplImage* img)
{

	/*
	 * initialize 3 grayscale images
	 *  to store 3 channels of img
	 */
	IplImage* red=cvCreateImage(cvGetSize(img),8,1);





	IplImage* green=cvCreateImage(cvGetSize(img),8,1);
	IplImage* green_optimized=cvCreateImage(cvGetSize(img),8,1);

	IplImage* blue=cvCreateImage(cvGetSize(img),8,1);


	// split src into 3 channels
		cvSplit(img, blue, green, red, NULL);

/*

	cvNamedWindow("GREEN_ORIGINAL",CV_WINDOW_NORMAL);
	cvShowImage("GREEN_ORIGINAL",green);
	cvWaitKey(0);

*/

	/*
	 *  lets reduce the effect of green on main image
	 */
	green_optimized = optimizeColor(green,3);
/*	cvNamedWindow("GREEN_OPTIMIZED",CV_WINDOW_NORMAL);
	cvShowImage("GREEN_OPTIMIZED",green_optimized);
	cvWaitKey(0);
	/* ***  ***  */




	IplImage* red_rgb_img = cvCreateImage(cvGetSize(img),8,3);


	cvMerge(NULL,green_optimized,red,NULL,red_rgb_img);

	// increase brightness
	//cvAddS(red_rgb_img,cvScalar(12,12,12,0),red_rgb_img,NULL);

	// reduce brightness
	// cvSubS(red_rgb_img,cvScalar(15,15,15,0),red_rgb_img,NULL);

	// increase/decrease contrast
	// cvConvertScale(red_rgb_img,red_rgb_img,0.5,0);

	// blur
	// cvSmooth(red_rgb_img,red_rgb_img,CV_GAUSSIAN,7,0,0,0);

	// display original input image
	//cvNamedWindow("ORIGINAL",CV_WINDOW_NORMAL);
	//cvShowImage("ORIGINAL",img);

	cvNamedWindow("RED_THEME_TEST",CV_WINDOW_FREERATIO);
	cvShowImage("RED_THEME_TEST",red_rgb_img);

	// wait for key event
	cvWaitKey(0);




}// end of method bgrThreshold()...




int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);


	cvStartWindowThread();


	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}


	red_theme_test(src);

	/*
	// display original input image
	cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
	cvShowImage("input",src);



	// wait for key event
	cvWaitKey(0);
	*/

	return 0;

}// end of main
