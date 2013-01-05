/*
 * Created by RPS Deepan- 05/01/2013
 *	reference - Learning OpenCV - Chapter 6 : Image Transforms
 *
 *		1. testing the Sobel derivative operator
 *
 *
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

	sobelDerivatives(&src);


	cvDestroyAllWindows();
	cvReleaseImage(&src);


	return 0;

}// end of main...
