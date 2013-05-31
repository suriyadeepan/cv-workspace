/*
 *	Created by RPS Deepan - 29-05-2013
 *
 *	 ref: [http://dasl.mem.drexel.edu/~noahKuntz/openCVTut2.html]
 *	 	  [http://opencv-srf.blogspot.in/2011/11/mouse-events.html]
 *
 */


#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// source image
IplImage* src;



// Mouse Event Callback Function
void mouseEvent(int evt, int x, int y, int flags, void* param){

	// left mouse button
	if(evt==CV_EVENT_LBUTTONDOWN){

		// (x,y) => point where LMB is pressed
		printf("\n x: %d , y: %d",x,y);
    }

}




int main(IplImage* prev1)
{
		// create main window
		cvNamedWindow("MyWindow",CV_WINDOW_AUTOSIZE);
		cvStartWindowThread();


        // assigning the callback function for mouse events
        cvSetMouseCallback("MyWindow", mouseEvent, 0);

        // load and display an image ./01.jpg
        src = cvLoadImage("01.jpg",CV_LOAD_IMAGE_UNCHANGED);

        // displays image
        cvShowImage("MyWindow", src);

        // wait for key press
        cvWaitKey(0);
      
        // Cleaning up
        cvDestroyWindow("MyWindow");


        cvReleaseImage(&src);
       
        return 0;
}// END OF MAIN
