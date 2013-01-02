
#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.



IplImage* hsvThreshold(IplImage** img)
{
	IplImage* src = cvCloneImage(*img);

		// covert bgr image (img) to HSV format
		cvCvtColor(src,src,CV_BGR2HSV);


		/*
		 * initialize 3 grayscale images
		 *  to store 3 channels of img
		 */
		IplImage* hue=cvCreateImage(cvGetSize(src),8,1);


		// split src into 3 channels
		cvSplit(src, hue, NULL, NULL, NULL);



		/*
		 * thresholding the image based on
		 *  a hue value of range (174/2 to 186/2)
		 *   this corresponds to light blue
		 *    found from gimp
		 */
		cvInRangeS(hue, cvScalar(148, 0, 0,0), cvScalar(176, 255, 255,0),hue);

	// return resulting thresholded image
	return hue;

}// end of method hsvThreshold()...

int main(int argc, char* argv[])
{

	//	IplImage* src=cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);



	IplImage* frame=0;

	CvCapture* capture=cvCreateFileCapture("0104.mp4");
	frame=cvQueryFrame(capture);

	IplImage* threshOp=cvCreateImage(cvGetSize(frame),8,1);
	cvNamedWindow("Detected",CV_WINDOW_NORMAL);
	cvNamedWindow("Threshold",CV_WINDOW_NORMAL);

	cvStartWindowThread();

		while(1)
		{

		frame=cvQueryFrame(capture);


		if(!frame)
		{  // capture a frame
		    printf("Could not grab a frame\n\7");
		    exit(0);
		}


		// threshold the src
		threshOp=hsvThreshold(&frame);
		cvShowImage("Threshold",threshOp);


		// now we need to find object in the image
			//  using the concept of moments
			CvMoments* moments=(CvMoments*)malloc(sizeof(CvMoments));
			cvMoments(threshOp,moments,1);

			// calculate moment values
			double moment01 = cvGetSpatialMoment(moments,0,1);
			double moment10 = cvGetSpatialMoment(moments,1,0);

			// calculate zero order moment value
			double momArea = cvGetCentralMoment(moments,0,0);

			int posX=moment10/momArea,posY=moment01/momArea;

			/*
			printf("\n\n\nM01: %g M10: %g M00: %g\n",moment01,moment10,momArea);

			printf("posX: %d posY: %d",posX,posY);
			*/

			CvPoint pt;
			pt.x=(int)posX;
			pt.y=(int)posY;

			cvCircle( frame, pt, 22, CV_RGB(255,0,0), -1,8,0 );



		cvShowImage("Detected",frame);

	    char c = cvWaitKey(100);
	    if( c == 27 || c=='q') break;



		}







/*	// display source img
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);
*/

	// save threshOp to file
	//cvSaveImage("threshOp.jpg",threshOp,0);

/*
	cvNamedWindow("Threshold",CV_WINDOW_NORMAL);
	cvShowImage("Threshold",threshOp);
*/


	cvDestroyAllWindows();
	cvReleaseImage(&frame);
	cvReleaseImage(&threshOp);

	return 0;

}
