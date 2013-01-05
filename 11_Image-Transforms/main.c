/*
 * Created by RPS Deepan- 05/01/2013
 *	reference - Learning OpenCV - Chapter 6 : Image Transforms
 *
 *		1. testing the Sobel derivative operator
 *			- detects edges, fits polynomial based on
 *			   gradient in x or y direction
 *		2. tested the SCHARR filter
 *			- more accurate than Sobel when kernel size
 *			   is small
 *	    3. tested the Laplacian filter
 *	    	- can be applied for blob detection
 *	    	   and edge detection
 *	    4. tested Canny Filter
 *	    	- advanced edge detection technique
 *	    	- edges formed by comparing gradient and
 *	    	   high/low threshold values
 *	    	- assembles edge pixels into contours
 */


#include<cv.h>
#include<stdio.h>
#include<highgui.h>

void sobelDerivatives(IplImage** src)
{

	IplImage* dst = cvCreateImage(cvGetSize(*src),8,1);

	// variables for iterating thro' loops
	int j=0,i=0;


	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(i==0 && j==0)
				continue;

			// sobel derivative operation
			cvSobel(*src,dst,i,j,3);

			// display output image...
			cvNamedWindow("Transform",CV_WINDOW_NORMAL);
			cvShowImage("Transform",dst);


			cvWaitKey(0);
		}



	}

	cvReleaseImage(&dst);

}// end of method sobelDerivatives()

void scharrFilter(IplImage** src,int x_order,int y_order,int aperture_size)
{
	IplImage* dst=cvCreateImage(cvGetSize(*src),8,1);

	cvSobel(*src,dst,x_order,y_order,aperture_size);

	cvNamedWindow("SCHARR",CV_WINDOW_NORMAL);
	cvShowImage("SCHARR",dst);

	cvWaitKey(0);

	cvReleaseImage(&dst);
}

void laplacianFilter(IplImage** src,int aperture_size)
{
	IplImage* dst=cvCreateImage(cvGetSize(*src),8,1);

	cvLaplace(*src,dst,aperture_size);

	cvNamedWindow("Laplacian",CV_WINDOW_NORMAL);
	cvShowImage("Laplacian",dst);

	cvWaitKey(0);

	cvReleaseImage(&dst);
}

void cannyFilter(IplImage** src,double lowThresh,double highThresh,int aperture_size)
{

	IplImage* dst=cvCreateImage(cvGetSize(*src),8,1);

	cvCanny(*src,dst,lowThresh,highThresh,3);

	cvNamedWindow("Canny",CV_WINDOW_NORMAL);
	cvShowImage("Canny",dst);

	cvWaitKey(0);

	cvReleaseImage(&dst);


}


int main(int argc, char* argv[])
{
	IplImage* src=cvLoadImage(argv[1],0);
	//IplImage* dst=cvCreateImage(cvGetSize(src),8,1);

	// index variable for iterating
	int i=0;

	if(!src)
	{
		printf("cant fetch image!\nquitting!"); exit(1);

	}

	cvStartWindowThread();


	// display src...
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	cvWaitKey(0);

/*
	// destroy src window
	cvDestroyWindow("Source");
*/

	// sobelDerivatives(&src);

	// scharrFilter(&src,1,0,CV_SCHARR);

	// laplacianFilter(&src,3);

	cannyFilter(&src,50,120,3);


	cvDestroyAllWindows();
	cvReleaseImage(&src);


	return 0;

}// end of main...
