/*
Expt by RPS Deepan- 29/12/2012
  Loads a image and perform erode operation over the image

  Gets the erode level as input from user
   runs this in a loop
    puts the text erode level: <level> in the image
     saves image to eroded.jpg

*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.

int main(int argc, char* argv[])
{
	// necessary variables..
	int erode_level = 11;
	char key='q';
	char s_erode_level[20] ;
	char img_text[]="erode level: ";

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

	 img = cvLoadImage("03.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img) {
		printf("Error: Could not open the image file! \n");
		exit(1);
	}

	// get erode level from user
	printf("Enter the level of eroding: ");
	scanf("%d", &erode_level);

	// set limits 0-120
	if(erode_level<=0)
		erode_level=1;

	else if(erode_level>120)
		erode_level=119;



	// erode the image...

	cvErode(img, img, NULL,erode_level);

	/*
	 *
	 * Similarly, dilation can be perfomed...
	 * cvDilate(img,img,NULL,erode_level);
	 *
	 */

	// write erode_level integer to String
	sprintf(s_erode_level, "%d", erode_level) ;

	// Concat "erode Level: " and s_erode_level(actual value)...
	strcpy(img_text,"erode level: ");
	strcat(img_text,s_erode_level);

	// write text to image
		cvPutText(img, img_text, cvPoint(10, 50),
				   &font, cvScalar(255, 255, 255, 0));



	// display image in the "Eroded" window...
		cvNamedWindow("Eroded", CV_WINDOW_AUTOSIZE);
		cvShowImage("Eroded", img);



	//  save to eroded.jpg...
	cvSaveImage("eroded.jpg", img, 0);



	// get input from user
	key = cvWaitKey(0);

	// destroy window and release image...
	cvDestroyWindow("Eroded");
	cvReleaseImage( &img );

	// if 'q' is pressed by user (key)
	//  break out of loop
	//   else continue...
	}while(key!='q');
	// end of do...while loop




	return 0;
}// end of main
