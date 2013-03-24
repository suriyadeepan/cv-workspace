#include <stdio.h>

#include <cv.h>
#include <highgui.h>



// the method contourDetect()
//  detect all contours and
//   draws them on to a copy of src
//    and returns it
void contourDetect(IplImage** img)
{
	int i=0;

	// sequence for storing resulting contours
	CvSeq* contours;

	// sequence for temporarily storing points
	//  in a contour
	CvSeq* result;

	// memory storage space for storing contours
	// 0 -> default (64K)
	CvMemStorage *storage = cvCreateMemStorage(0);



	// grayscale form of source image "img"
	//  for contour detection
	  IplImage* imgGray = cvCreateImage(cvGetSize(*img), 8, 1);
	  	  cvCvtColor(*img, imgGray, CV_BGR2GRAY);


	// find all contours in temp and
	//  store them in contours
	 cvFindContours(imgGray,storage, &contours,sizeof(CvContour),CV_RETR_LIST,
		        CV_CHAIN_APPROX_SIMPLE, cvPoint(5,5));

	 cvDrawContours(*img,contours,cvScalar(255,0,0,0),cvScalar(0,255,0,0),2,1,8,cvPoint(0,0));


} // end of method contourDetect()...



// --- MAIN ---
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


		// find contours on image
		contourDetect(&frame);



		// display frame
		cvShowImage("Source",frame);

	}


	// release capture
	cvReleaseCapture(&capture);
	cvDestroyWindow("Source");
	cvReleaseImage(&frame);


	return 0;

}// end of main
