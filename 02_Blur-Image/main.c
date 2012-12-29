/* 
Expt by Selvakumar - 24/09/2012
  Loads a image and perform blur operation over the image 
Modified by RPS Deepan - 29/12/2012
  Gets the blur level as input from user
	runs this in a loop
*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int blur_level = 11;
	char key='q';
	char s_blur_level[20] ;
	char img_text[]="blur level: ";

	// image container...
	IplImage* img;

	// Font obj for setting text font...
	CvFont font;

	// initialize font object...
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX,
			1.0, 1.0, 0, 1, CV_AA);



	// starts the window thread...
	// is necessary to destroy window...
	cvStartWindowThread();

	// do...while loop starts here
	do{

	 img = cvLoadImage("02.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// get blur level from user
	printf("Enter the level of blurring: ");
	scanf("%d", &blur_level);

	// set limits 0-120
	if(blur_level<=0)
		blur_level=1;

	else if(blur_level>120)
		blur_level=119;



	// if its even - some errors arise
	//  so increment by 1 if even...
	if(blur_level%2==0)
		blur_level++;


	// smooth the image...
	cvSmooth(img, img, CV_GAUSSIAN, blur_level, 0, 0, 0);


	// write blur_level integer to String
	sprintf(s_blur_level, "%d", blur_level) ;

	// Concat "Blur Level: " and s_blur_level(actual value)...
	strcat(img_text,s_blur_level);

	// write text to image
		cvPutText(img, img_text, cvPoint(10, 50),
				   &font, cvScalar(255, 255, 255, 0));



	// display image in the "Blurred" window...
		cvNamedWindow("Blurred", CV_WINDOW_AUTOSIZE);
		cvShowImage("Blurred", img);



	//  save to blurred.jpg...
	cvSaveImage("blurred.jpg", img, 0);



	// get input from user
	key = cvWaitKey(0);

	// destroy window and release image...
	cvDestroyWindow("Blurred");
	cvReleaseImage( &img );

	// if 'q' is pressed by user (key)
	//  break out of loop
	//   else continue...
	}while(key!='q');
	// end of do...while loop




	return 0;
}// end of main
