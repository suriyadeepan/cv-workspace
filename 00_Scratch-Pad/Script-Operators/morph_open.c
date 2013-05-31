#include <stdio.h>
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


IplImage* src;
IplImage* dest;
IplImage* temp;



int main(int argc, char* argv[])
{

	src = cvLoadImage("current.jpg",CV_LOAD_IMAGE_UNCHANGED);
	dest = cvCreateImage(cvGetSize(src),src->depth,3);
	temp = cvCreateImage(cvGetSize(src),src->depth,3);



	// necessary variables..
	int mask_strength = 11;


	scanf("%d", &mask_strength);

	// set limits 0-120
	if(mask_strength<=0)
		mask_strength=1;

	else if(mask_strength>120)
		mask_strength=119;


/*
	case 5:
		op=CV_MOP_BLACKHAT;
		break;


	case 6:
		op=CV_MOP_TOPHAT;
		break;



	case 7:
		op=CV_MOP_GRADIENT;
		break;
*/

	// apply mask...
	cvMorphologyEx(src,dest,temp,NULL,CV_MOP_OPEN,mask_strength);


	//  save to modified.jpg...
	cvSaveImage("current.jpg", dest, 0);


	cvReleaseImage(&dest );
	cvReleaseImage(&src);
	cvReleaseImage(&temp);



	return 0;
}// end of main
