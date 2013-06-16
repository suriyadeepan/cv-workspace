#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// hsv range
#define H_MIN 137
#define H_MAX 176

#define S_MIN 45
#define S_MAX 218

#define V_MIN 84
#define V_MAX 255


IplImage* frame;

CvPoint pt00;
CvPoint pt01;
CvPoint pt02;

CvPoint pt10;
CvPoint pt20;

CvPoint pt11;
CvPoint pt22;

int xMax;
int yMax;

void setup()
{
	xMax = frame->width;
	yMax = frame->height;



	pt00 = cvPoint(0,0);
	pt01 = cvPoint(0,yMax/2);
	pt02 = cvPoint(0,yMax);
	pt10 = cvPoint(xMax/2,0);
	pt20 = cvPoint(xMax,0);
	pt11 = cvPoint(xMax/2,yMax/2);
	pt22 = cvPoint(xMax,yMax);
}

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



void drawQuadrant(IplImage* thresh)
{



	// now we need to find the exact position of the object in the image
			//  using the concept of moments
			CvMoments* moments = (CvMoments*)malloc(sizeof(CvMoments));
			cvMoments(thresh,moments,1);

			// calculate moment values
			double moment01 = cvGetSpatialMoment(moments,0,1);
			double moment10 = cvGetSpatialMoment(moments,1,0);

			// calculate zero order moment value
			double momArea = cvGetCentralMoment(moments,0,0);

			int posX=moment10/momArea,posY=moment01/momArea;


			if(posX < xMax/2 && posY < yMax/2)
				cvRectangle(frame,pt00,pt11,CV_RGB(255,0,0),3,8,0);


			else if(posX > xMax/2 && posY < yMax/2)
				cvRectangle(frame,pt20,pt11,CV_RGB(255,0,0),3,8,0);

			else if(posX < xMax/2 && posY > yMax/2)
				cvRectangle(frame,pt02,pt11,CV_RGB(255,0,0),3,8,0);

			else if(posX > xMax/2 && posY > yMax/2)
				cvRectangle(frame,pt22,pt11,CV_RGB(255,0,0),3,8,0);


}





int main(int argc, char **argv) {


	//IplImage* thresh;

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


	// windows
	cvStartWindowThread();
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	//cvNamedWindow("Thresholded",CV_WINDOW_NORMAL);

	frame = cvQueryFrame(capture);
	setup();

	// iterate thro' all the frames
	while(1)
	{

		frame = cvQueryFrame(capture);

		if(!frame)
			break;

		// threshold the image
		//thresh = hsvThreshold(cvClone(frame));

		// lets identify the quadrant
		drawQuadrant(hsvThreshold(cvClone(frame)));


		cvShowImage("Source",frame);
		//cvShowImage("Thresholded",thresh);

		// a small delay
		char user_input = cvWaitKey(20);

		if(user_input=='q')
		{
			printf("User Interrupts!\n");
			break;
		}



	}// end of while


	// free memory
	cvDestroyAllWindows();
	cvReleaseCapture(&capture);
	//cvReleaseImage(&thresh);
	cvReleaseImage(&frame);


	return 0;
}
