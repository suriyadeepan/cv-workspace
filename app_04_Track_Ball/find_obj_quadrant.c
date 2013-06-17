Expt by RPS Deepan- 16/06/2013
    the program iterates thro' a video - frame by frame
    thresholds each frame for finding the object location
    finds the postion of object and draws a rectangle over 
    	that quadrant
	
Modified by RPS Deepan- 17/06/2013
    added comments on every step
    made the indentations proper
    still need to modify the code to work
     efficiently


#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// hsv range
//  the HSV values of the object is 
//   supposed to lie within these ranges
#define H_MIN 137
#define H_MAX 176

#define S_MIN 45
#define S_MAX 218

#define V_MIN 84
#define V_MAX 255

// a container to store and manipulate 
//  each frame...
// made global to access it in all functions
IplImage* frame;

// points on the image 
//  helps in drawing the bounding box
//   over the quadrants
CvPoint pt00;
CvPoint pt01;
CvPoint pt02;

CvPoint pt10;
CvPoint pt20;

CvPoint pt11;
CvPoint pt22;

// max x and y values on the image
int xMax;
int yMax;

// a function to initialize all the points on
//  image and set yMax, xMax...
void setup()
{
	// obtain width and height of image
	//  from the frame (IplImage, is global)
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

// HSV thresholding:
//  takes a copy of the "frame"
//  converts it to HSV format (cvCvtColor())
//  thresholds it based on known HSV ranges
//  returns the thresholded image
IplImage* hsvThreshold(IplImage* img)
{
	// create a container to store thresholded image
	IplImage* thresh = cvCreateImage(cvGetSize(img),8,1);

	// covert bgr image (img) to HSV format
	cvCvtColor(img,img,CV_BGR2HSV);

	// thresholding
	cvInRangeS(img, cvScalar(H_MIN, S_MIN, V_MIN,0), cvScalar(H_MAX, S_MAX, V_MAX,0),thresh);

	cvReleaseImage(&img);

	// return resulting thresholded image
	return thresh;

}// end of method hsvThreshold()...


// Draw Quadrant:
//  finds the position of object from thresholded image
//   (by calculated moments)
//  draws a bounding box (rectangle) around the quadrant 
//   at which the object is present
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
	
	// calculate position of obj (COG)
	int posX=moment10/momArea,posY=moment01/momArea;


	// based on posX and posY of object
	//  draw a rectangle over the quadrant
	// cvRectangle(image,point1,point2,color(red),line_thickness,
	// 		line_type,shift);
	if(posX < xMax/2 && posY < yMax/2)
		cvRectangle(frame,pt00,pt11,CV_RGB(255,0,0),3,8,0);

	else if(posX > xMax/2 && posY < yMax/2)
		cvRectangle(frame,pt20,pt11,CV_RGB(255,0,0),3,8,0);

	else if(posX < xMax/2 && posY > yMax/2)
		cvRectangle(frame,pt02,pt11,CV_RGB(255,0,0),3,8,0);

	else if(posX > xMax/2 && posY > yMax/2)
		cvRectangle(frame,pt22,pt11,CV_RGB(255,0,0),3,8,0);
}// end of function drawQuadrant()

int main(int argc, char **argv) {

	// a video capture obj
	CvCapture* capture = 0;

	// checking if the argument is valid
	if(argv[1]!=NULL){
		printf("argv[1] => %s is valid...",argv[1]);
		capture = cvCreateFileCapture(argv[1]);
	}
	else{
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
	cvNamedWindow("Object Quadrant",CV_WINDOW_NORMAL);

	// get a sample image for initializing variables
	frame = cvQueryFrame(capture);

	// initialize variable
	setup();

	// iterate thro' all the frames
	while(1)
	{
		// get a frame from video
		frame = cvQueryFrame(capture);
		
		// check if its null
		if(!frame)
			break;

		// lets identify the quadrant!
		// threshold a copy of the frame
		// pass the result to drawQuadrant() function
		drawQuadrant(hsvThreshold(cvClone(frame)));

		cvShowImage("Object Quadrant",frame);

		// a small delay
		// get user input 
		// check if the user wants to 
		//  quit
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
	cvReleaseImage(&frame);

	return 0;
}// END OF MAIN
