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

// corner image
IplImage* cornImg;

// font
CvFont someFont;

// info obtained from image
char message[70];

// find corners
void findCorners(IplImage* cornerIp)
{

	IplImage* threshImg = cvCreateImage(cvGetSize(cornerIp), 8, 1);
	IplImage* harrisImg = cvCreateImage(cvGetSize(cornerIp), IPL_DEPTH_32F, 1);


	cvThreshold(cornerIp,threshImg,100,255,CV_THRESH_BINARY);

	cvCornerHarris(threshImg,harrisImg,20,5,0.04);

	// Blur
	// smooth the image...
	cvSmooth(harrisImg, harrisImg, CV_GAUSSIAN, 19, 0, 0, 0);


	// MORPH
	// a temp buffer for morph
	IplImage* temp = cvCreateImage(cvGetSize(harrisImg),harrisImg->depth,1);
	IplImage* morphedHarrisImg = cvCreateImage(cvGetSize(harrisImg),harrisImg->depth,1);

	// operating on the harris output image
	cvMorphologyEx(harrisImg,morphedHarrisImg,temp,NULL,CV_MOP_ERODE,7);

	// display morphed image
	cvNamedWindow("Morphed",CV_WINDOW_NORMAL);
	cvShowImage("Morphed",morphedHarrisImg);

	cornImg = morphedHarrisImg;

}

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

		// get a copy of src
		IplImage* copyOfSrc = cvCloneImage(cornImg);





		/*
		// (x,y) => point where LMB is pressed
		// obtain pixel values from RGB, HSV component @ point (x,y)
        int rVal = cvGetReal2D(rImg,y,x), gVal = cvGetReal2D(gImg,y,x), bVal = cvGetReal2D(bImg,y,x);
        int hVal = cvGetReal2D(hImg,y,x), sVal = cvGetReal2D(sImg,y,x), vVal = cvGetReal2D(vImg,y,x);

        // get a copy of src
        IplImage* copyOfSrc = cvCloneImage(src);

        // make a string from all the pixel values obtained
        sprintf(message,"Position: %d %d ; RGB: %d %d %d ; HSV: %d %d %d ; Mask: %d",
        		x,y,rVal,gVal,bVal,hVal,sVal,vVal,applyMask(x,y));
*/

		sprintf(message,"Position: %d %d ; Mask: %d", x,y,applyMask(x,y));

        // draw the string "message" on the Image "copyOfSrc"
        cvPutText(copyOfSrc,message,cvPoint(50,copyOfSrc->height-100),&someFont,cvScalar(255,0,255,0));

        // display image on window (update/refresh)
        cvShowImage("MyWindow", copyOfSrc);
    }

}

int applyMask(int x,int y)
{
	/*
	int width = src->width, height = src->height;

	int val = 0,i=0,j=0;

	if(x>2 && y>2 && x<width-1 && y<height-1)
	{

		for(i=x-1;i<=x+1;i++)
		{
			for(j=y-1;j<=y+1;j++)
			{
				if(i==x && j==y)
					val += 4*cvGetReal2D(src,j,i);

				else
					val += 2*cvGetReal2D(src,j,i);
			}
		}
/*
	// get pixel value of each channel
	int val = (2*cvGetReal2D(src, y-1, x-1))+(2*cvGetReal2D(src,y-1,x))+(2*cvGetReal2D(src,y-1,x+1))
			+(2*cvGetReal2D(src,y,x-1))+(4*cvGetReal2D(src,y,x))+(2*cvGetReal2D(src,y,x+1))
			+(2*cvGetReal2D(src,y+1,x-1))+(2*cvGetReal2D(src,y+1,x))+(2*cvGetReal2D(src,y+1,x+1));

	return cvGetReal2D(src,y,x);

	}
*/

	return cvGetReal2D(src,y,x);
}


int main(int argc, char* argv[])
{
		src = cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

		cornImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);

		// create main window
		cvNamedWindow("MyWindow",CV_WINDOW_AUTOSIZE);
		cvStartWindowThread();


		// init font
		cvInitFont(&someFont,CV_FONT_HERSHEY_TRIPLEX,1,0.8,0.2,1,8);

        // assigning the callback function for mouse events
        cvSetMouseCallback("MyWindow", mouseEvent, 0);

        findCorners(src);

        // displays image
        cvShowImage("MyWindow", cornImg);
        
        /*
        // split source image into components
        splitImagesRGB(src);
        splitImagesHSV(src);
*/

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
