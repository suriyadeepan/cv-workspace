
#include <cv.h>
#include <highgui.h>
#include <stdio.h>

#define H_MIN 143
#define H_MAX 187

#define S_MIN 19
#define S_MAX 190

#define V_MIN 160
#define V_MAX 255

IplImage* hsvThreshold(IplImage* img)
{
	IplImage* thresh = cvCreateImage(cvGetSize(img),8,1);

		// covert bgr image (img) to HSV format
		cvCvtColor(img,img,CV_BGR2HSV);

		cvInRangeS(img, cvScalar(H_MIN, S_MIN, V_MIN,0), cvScalar(H_MAX, S_MAX, V_MAX,0),thresh);

	cvReleaseImage(&img);

	// return resulting thresholded image
	return thresh;

}// end of method hsvThreshold()...



int main(int argc, char **argv) {


	// container to store frames
	IplImage* frame;
	IplImage* thresh;

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
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvNamedWindow("Thresholded",CV_WINDOW_NORMAL);

	// iterate thro' all the frames
	while(1)
	{

		frame = cvQueryFrame(capture);

		if(!frame)
			break;

		// threshold the image
		thresh = hsvThreshold(cvClone(frame));

		cvShowImage("Source",frame);
		cvShowImage("Thresholded",thresh);

		// a small delay
		char user_input = cvWaitKey(40);

		if(user_input=='q')
		{
			printf("User Interrupts!\n");
			break;
		}



	}


	// release capture
	cvReleaseCapture(&capture);
	cvDestroyWindow("Source");
	cvReleaseImage(&frame);


	return 0;
}
