/*
 * Created by RPS Deepan - 05-01-2013
 *  reference - Learning OpenCV - Chapter 6 : Image Transforms
 *
 *
 *		1. testing the method cvHoughLines2()
 *			ref - aishack.in
 *				  [http://www.aishack.in/2010/04/hough-transform-in-opencv/]
 *
 *		2. testing the method cvHoughCircles()
 *			ref - aishack.in
 *				  [http://www.aishack.in/2010/04/hough-circles-in-opencv/]
 *				- opencv yahoo group
 *				  [http://tech.groups.yahoo.com/group/OpenCV/message/16035?source=1&var=1]
 *				- opencv documentation
 *				  [http://docs.opencv.org/trunk/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html]
 */


#include<cv.h>
#include<highgui.h>
#include<math.h>
#include<stdio.h>

void doHoughLineTransform(IplImage** src,IplImage** temp)
{

	// storage space
	 CvMemStorage* storage = cvCreateMemStorage(0);

	 // a sequence for storing lines...
	 CvSeq* lines = 0;


	 // resolution parameters
	 double rho=1,theta=0.01;

	 // threshold value
	 int threshold = 240;

	 // canny filter
	 cvCanny(*src, *src, 20, 80, 3);

	 // display canny image
	 cvNamedWindow("Canny",CV_WINDOW_NORMAL);
	 cvShowImage("Canny",*src);

	 // wait for key press
	 cvWaitKey(0);

	 // destroy Canny window
	 cvDestroyWindow("Canny");

	 // do hough transform...
	 /*
	  * src -> image
	  * storage -> CvMemoryStorage (space for storage)
	  * CV_HOUGH_STANDARD -> method
	  * rho -> normal distance
	  * theta -> angle
	  * threshold -> 0-255 (i think)
	  * param1, param2 -> 0,0
	  *
	  */
	 lines = cvHoughLines2( *src, storage, CV_HOUGH_STANDARD,
	  rho, theta, threshold, 0,0);

	 // index variable for iteration
	 int i=0;


	 // extract points (x,y) from (rho,theta) op of
	 //  houghLines2() method...

	 for(  i = 0; i < lines->total; i++ )
	 {

		 // get sequence elements (single line
		 //  from array of lines)
		 float* line = (float*)cvGetSeqElem(lines,i);

		 // get rho,theta info from line
		 float rho = line[0];
		 float theta = line[1];

		 // points to store x,y
		 CvPoint pt1, pt2;

		 // rho = xcos(theta) + ysin(theta)
		 // get x,y from rho,theta
		 double a = cos(theta), b = sin(theta);
		 double x0 = a*rho, y0 = b*rho;
		 pt1.x = cvRound(x0 + 1000*(-b));
		 pt1.y = cvRound(y0 + 1000*(a));
		 pt2.x = cvRound(x0 - 1000*(-b));
		 pt2.y = cvRound(y0 - 1000*(a));

		 /*
		 printf("\nPoint 1: %d %d ",pt1.x,pt1.y);
		 printf("Point 2: %d %d\n",pt2.x,pt2.y);
		*/

		 // draw line connecting pt1 and pt2
		 cvLine( *temp, pt1, pt2, CV_RGB(255,0,0), 1,8,0);

			 }



	 // display output...
 	 cvNamedWindow("HoughOp",CV_WINDOW_NORMAL);
 	 cvShowImage("HoughOp",*temp);

 	 // wait for key press
 	 cvWaitKey(0);

 	 cvDestroyWindow("Canny");
 	 cvReleaseMemStorage(&storage);

}

int main(int argc, char* argv[])
{

	IplImage* src = cvLoadImage(argv[1],0);
	//IplImage* opImage=cvCloneImage(src);
	IplImage* opImage=cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);


	cvStartWindowThread();

	// display source...
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	// wait for key press
	cvWaitKey(0);

	//doHoughLineTransform(&src,&temp);

	// storage space
		 CvMemStorage* storage = cvCreateMemStorage(0);

    // a sequence for storing circles...
		 CvSeq* circles = 0;

	// do hough circle transform
	circles = cvHoughCircles(src,storage,CV_HOUGH_GRADIENT,2,
			10,200,100,5,130);

	// index variable for iterating thro' circles
	int i=0;

	// iterate thro' circles to fetch
	//  individual circles
	for(i=0;i<circles->total;i++)
	{
		// get individual circle from sequence circles
		float* circle = (float*)cvGetSeqElem(circles,i);

		// get x,y from each circle
		CvPoint pt = cvPoint(cvRound(circle[0]), cvRound( circle[1] ));

		// draw circle on source image
		cvCircle(opImage,pt,cvRound( circle[2] ),CV_RGB(255,0,0),3,8,0);


	}

	// display output
	cvNamedWindow("HoughOp",CV_WINDOW_NORMAL);
	cvShowImage("HoughOp",opImage);

	cvWaitKey(0);

	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&opImage);





	return 0;

}// end of main...








