/*
 *	Created by RPS Deepan - 31-05-2013
 *
 */


#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// source image
IplImage* src;

int main(IplImage* prev1)
{
		// create main window
		cvNamedWindow("MyWindow",CV_WINDOW_AUTOSIZE);
		cvStartWindowThread();

      // load and display an image ./01.jpg
      src = cvLoadImage("01.jpg",CV_LOAD_IMAGE_UNCHANGED);

      // displays image
      cvShowImage("MyWindow", src);

		char ch = 'a';

		while(ch!='q')
		{
			ch = cvWaitKey(0);
			printf("\nChar pressed: %c",ch);
		}
		

        // Cleaning up
        cvDestroyWindow("MyWindow");


        cvReleaseImage(&src);
       
        return 0;
}// END OF MAIN
