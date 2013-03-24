// std headers
#include <stdio.h>

// opencv headers
#include <cv.h>
#include <highgui.h>


// --- HEADERS ---
int main(int argc, char* argv[])
{
	// container to store frames
	IplImage* frame;

	// a video capture obj
	CvCapture* capture = 0;


	// checking if the argument is valid
	if(argv[1]!=NULL)
	{
		printf("argv[1] => %s is valid...",argv[1]);
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
	cvNamedWindow("Source",CV_WINDOW_AUTOSIZE);

	// iterate thro' all the frames
	while(1)
	{

		frame = cvQueryFrame(capture);

		if(!frame)
			break;

		// a small delay
		char user_input = cvWaitKey(40);

		if(user_input=='q')
		{
			printf("User Interrupts!\n");
			break;
		}

		cvShowImage("Source",frame);

	}


	// release capture
	cvReleaseCapture(&capture);
	cvDestroyWindow("Source");
	cvReleaseImage(&frame);


	return 0;

}// end of main
