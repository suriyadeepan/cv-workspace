/*

Created by RPS Deepan- 31/12/2012
	- added a method addBrightness()
	   to increase overall brightness of img

Modified by RPS Deepan- 31/12/2012
	- added a method addContrast()
	   uses cvConvertScale() to increase
	    constrast by a factor(double)
	- added a method to invert image

Modified by RPS Deepan- 02/01/2012
	- modified the main function to
	   play an avi file frame by frame
	    with varying contrasts and brightness
	- need to make this code chunk in main 
	   into a proper method...

*/



#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


IplImage* addBrightness(IplImage** img)
{
	cvAddS(*img,cvScalar(50,50,50,0),*img,NULL);

	return *img;

}

IplImage* addContrast(IplImage** img)
{
	cvConvertScale(*img,*img,2,0);

	return *img;
}

IplImage* invertImg(IplImage** img)
{
	cvNot(*img,*img);

	return *img;
}



int main(int argc, char* argv[])
{


	// load an image from file
	//	IplImage* src=cvLoadImage("00.jpg",CV_LOAD_IMAGE_UNCHANGED);
	//	IplImage* img;


	CvCapture* capture = cvCreateFileCapture("00.avi");


	cvStartWindowThread();


	IplImage* frame = 0;
	IplImage* frame1=0;
	IplImage* frame2=0;

	cvNamedWindow("Org",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Bright",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Contrast",CV_WINDOW_AUTOSIZE);
	
	frame=cvQueryFrame(capture);
	

	while(1)
	{
	
	frame=cvQueryFrame(capture);
	

	if(!frame)
	{  // capture a frame
	    printf("Could not grab a frame\n\7");
	    exit(0);
	}

	frame1=cvCloneImage(frame);
	frame2=cvCloneImage(frame);

	cvShowImage("Org",frame);

	frame1=addBrightness(&frame1);	
	
	cvShowImage( "Bright", frame1);

	frame2=addContrast(&frame2);

	cvShowImage("Contrast",frame2);

        char c = cvWaitKey(33);
        if( c == 27 || c=='q') break;



	}






/*

	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}

	// display original input image
	cvNamedWindow("input",CV_WINDOW_AUTOSIZE);
	cvShowImage("input",src);

	// wait for key event
	cvWaitKey(0);

	cvDestroyWindow("input");

	src=invertImg(&src);


	// display inverted image
	cvNamedWindow("Inverted",CV_WINDOW_AUTOSIZE);
	cvShowImage("Inverted",src);
*/

/*

	// wait for key event
	cvWaitKey(0);
*/


	// clean up memory...
	cvDestroyAllWindows();

	cvReleaseImage(&frame);
	cvReleaseImage(&frame1);
	cvReleaseImage(&frame2);

	cvReleaseCapture(&capture);


	return 0;

}// end of main
