/*
 *  Created by RPS Deepan @ 30-05-2013
 *
 *		Frame Differencing
 *			subtract one frame from another
 *			 and label the difference as foreground
 */


#include <cv.h>
#include <highgui.h>
#include <stdio.h>



int main(int argc, char** argv) {



	// container to store frames
		IplImage* frame;
		IplImage* prev;
		IplImage* frame_foreground;

		// a video capture obj
		CvCapture* capture = 0;


		// checking if the argument is valid
		if(argv[1]!=NULL)
		{
			printf("\n\nargv[1] => %s is valid...",argv[1]);
			capture = cvCreateFileCapture(argv[1]);

		}

		 else
		 {
			printf("Provide a proper argument...\nQuitting!\n");
			return -1;

		 }


		// if its null
		if(!capture)
		{
			printf("capture obj is null!");
			return -1;
		}


		// window
		cvStartWindowThread();
		cvNamedWindow("Frame Difference",CV_WINDOW_AUTOSIZE);

		int i=0;

		// iterate thro' all the frames
		while(1)
		{
			i++;

			frame = cvQueryFrame(capture);

			if(!frame)
					break;

			if(i>1)
			{
				cvAbsDiff(prev,frame,frame_foreground);
				cvThreshold(frame_foreground,frame_foreground,20,255,CV_THRESH_BINARY);
				cvShowImage("Frame Difference",frame_foreground);

			}

			// a small delay
			char user_input = cvWaitKey(60);

			if(user_input=='q')
			{
				printf("User Interrupts!\n");
				break;
			}

			//cvShowImage("Frame Difference",frame);
			prev = frame;

		}

		// release capture
		cvReleaseCapture(&capture);
		cvDestroyWindow("Frame Difference");
		cvReleaseImage(&frame);

		return 0;

}
