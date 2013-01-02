/*

Expt by RPS Deepan- 29/12/2012
  Loads a image and perform specific
  	  morphological operations over the image
Modified by RPS Deepan- 02/01/2013
  modified to test morphological operations on
   an image hue-thresholded from the source image
    for filtering noise


*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

void initImgs(IplImage** src,IplImage** dest,IplImage** temp,char* ipImgName)
{
	// image container...
	 *src = cvLoadImage(ipImgName,0);



	if (!*src) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// init other imgs...
	*dest = cvCreateImage(cvGetSize(*src),(*src)->depth,1);
	*temp = cvCreateImage(cvGetSize(*src),(*src)->depth,1);

}


// image containers...
	IplImage* src;
	// init other imgs...
	IplImage* dest;
		IplImage* temp;


char imgFileName[32];


int main(int argc, char* argv[])
{

	// necessary variables..
	int mask_strength = 11;
	char key='q';
	char s_mask_strength[20] ;
	char img_text[]="erode level: ";

	if ( ! argv[1] ){
		printf ( "ERROR give a file name " );
		exit(1);
	}
	else {
		strcpy(imgFileName,argv[1]);	

 	}

	// display the original image...
			IplImage* orgImg=cvLoadImage(argv[1],0);
			cvNamedWindow("Original", CV_WINDOW_NORMAL);
			cvShowImage("Original", orgImg);

			cvWaitKey(0);

	// Font obj for setting text font...
		CvFont font;

	// initialize font object...
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX,
				1.0, 1.0, 0, 1, CV_AA);



	// starts the window thread...
	// is necessary to destroy window...
	cvStartWindowThread();

	// initialize images...
			//initImgs(src,dest,temp);

	// do...while loop starts here
	do{

		// initialize images...
		initImgs(&src,&dest,&temp,imgFileName);

	// get Mask Strength from user
	printf("Enter Mask Strength: ");
	scanf("%d", &mask_strength);

	// set limits 0-120
	if(mask_strength<=0)
		mask_strength=1;

	else if(mask_strength>120)
		mask_strength=119;


	int op=0;

	printf("\n1.open\n2.close\n3.dilate\n4.erode\n5.blackhat\n6.tophat\n7.gradient\n");

	scanf("%d",&op);

	printf("\n");

	switch(op)
	{

	case 1:
		op=CV_MOP_OPEN;
		break;


	case 2:
		op=CV_MOP_CLOSE;
		break;


	case 3:
		op=CV_MOP_DILATE;
		break;


	case 4:
		op=CV_MOP_ERODE;
		break;


	case 5:
		op=CV_MOP_BLACKHAT;
		break;


	case 6:
		op=CV_MOP_TOPHAT;
		break;



	case 7:
		op=CV_MOP_GRADIENT;
		break;


	default:

		break;

	}


	// apply mask...
	cvMorphologyEx(src,dest,temp,NULL,op,mask_strength);


	// write Mask Strength integer to String
	sprintf(s_mask_strength, "%d", mask_strength) ;

	// Concat "Mask Strength: " and s_mask_strength(actual value)...
	strcpy(img_text,"Mask Strength: ");
	strcat(img_text,s_mask_strength);

	// write text to image
		cvPutText(dest, img_text, cvPoint(10, 50),
				   &font, cvScalar(255, 255, 255, 0));



	// display image in the "Modified" window...
		cvNamedWindow("Modified", CV_WINDOW_NORMAL);
		cvShowImage("Modified", dest);



	//  save to modified.jpg...
	cvSaveImage("modified.jpg", dest, 0);



	// get input from user
	key = cvWaitKey(0);

	// destroy window and release image...
	cvDestroyWindow("Modified");
	cvReleaseImage(&dest );
	cvReleaseImage(&src);
	cvReleaseImage(&temp);



	// if 'q' is pressed by user (key)
	//  break out of loop
	//   else continue...
	}while(key!='q');
	// end of do...while loop


	cvDestroyAllWindows();
	cvReleaseImage(&orgImg);

	return 0;
}// end of main
