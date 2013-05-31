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

// RGB components
IplImage* rImg;
IplImage* gImg;
IplImage* bImg;

// HSV components
IplImage* hImg;
IplImage* sImg;
IplImage* vImg;

// font
CvFont someFont;

// info obtained from image
char message[50];

// split src into RGB components
void splitImagesRGB()
{
	rImg = cvCreateImage(cvGetSize(src),8,1);
	gImg = cvCreateImage(cvGetSize(src),8,1);
	bImg = cvCreateImage(cvGetSize(src),8,1);

	cvSplit(src,rImg,gImg,bImg,NULL);
}

// split src into HSV components
void splitImagesHSV()
{
	IplImage* hsvImg = cvCreateImage(cvGetSize(src),8,3);
	cvCvtColor(src,hsvImg,CV_RGB2HSV);

	hImg = cvCreateImage(cvGetSize(src),8,1);
	sImg = cvCreateImage(cvGetSize(src),8,1);
	vImg = cvCreateImage(cvGetSize(src),8,1);

	cvSplit(src,hImg,sImg,vImg,NULL);

}


// Mouse Event Callback Function
void mouseEvent(int evt, int x, int y, int flags, void* param){

	// left mouse button
	if(evt==CV_EVENT_LBUTTONDOWN){

		// (x,y) => point where LMB is pressed
		// obtain pixel values from RGB, HSV component @ point (x,y)
        int rVal = cvGetReal2D(rImg,y,x), gVal = cvGetReal2D(gImg,y,x), bVal = cvGetReal2D(bImg,y,x);
        int hVal = cvGetReal2D(hImg,y,x), sVal = cvGetReal2D(sImg,y,x), vVal = cvGetReal2D(vImg,y,x);

        // get a copy of src
        IplImage* copyOfSrc = cvCloneImage(src);

        // make a string from all the pixel values obtained
        sprintf(message,"Position: %d %d ; RGB: %d %d %d ; HSV: %d %d %d",x,y,rVal,gVal,bVal,hVal,sVal,vVal);

        // draw the string "message" on the Image "copyOfSrc"
        cvPutText(copyOfSrc,message,cvPoint(50,copyOfSrc->height-100),&someFont,cvScalar(255,0,255,0));

        // display image on window (update/refresh)
        cvShowImage("MyWindow", copyOfSrc);
    }

}




int main(IplImage* prev1)
{
		// create main window
		cvNamedWindow("MyWindow",CV_WINDOW_AUTOSIZE);
		cvStartWindowThread();


		// init font
		cvInitFont(&someFont,CV_FONT_HERSHEY_TRIPLEX,1,0.8,0.2,1,8);

        // assigning the callback function for mouse events
        cvSetMouseCallback("MyWindow", mouseEvent, 0);

        // load and display an image ./01.jpg
        src = cvLoadImage("01.jpg",CV_LOAD_IMAGE_UNCHANGED);

        // displays image
        cvShowImage("MyWindow", src);
        
        // split source image into components
        splitImagesRGB(src);
        splitImagesHSV(src);


        // wait for key press
        cvWaitKey(0);
      
        // Cleaning up
        cvDestroyWindow("MyWindow");


        cvReleaseImage(&rImg);
        cvReleaseImage(&gImg);
        cvReleaseImage(&bImg);

        cvReleaseImage(&hImg);
        cvReleaseImage(&sImg);
        cvReleaseImage(&vImg);

        cvReleaseImage(&src);
       
        return 0;
}// END OF MAIN
