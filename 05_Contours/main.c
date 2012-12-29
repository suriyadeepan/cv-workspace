/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/an-introduction-to-contours/]

Modified by RPS Deepan- 29/12/2012
  Loads an image - detects the contours in it
   selects quadrilateral type contours
  	  draws indicating lines on the input image
  	  	  and displays as output

*/

#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.



// the method contourDetect()
//  detect all contours and
//   draws them on to a copy of src
//    and returns it
IplImage* contourDetect(IplImage** img)
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

	// ret -> this image is a copy of source image "img"
	//  on which contours are drawn and returned
	 IplImage* ret = cvCreateImage(cvGetSize(*img), 8, 3);

	// temp -> grayscale form of source image "img"
	//  for contour detection
	  IplImage* temp = cvCreateImage(cvGetSize(*img), 8, 1);

	// converting "img" to grayscale and
	//  and storing in temp
	 cvCvtColor(*img, temp, CV_BGR2GRAY);

	// find all contours in temp and
	//  store them in contours
	 cvFindContours(temp,storage, &contours,sizeof(CvContour),CV_RETR_LIST,
		        CV_CHAIN_APPROX_SIMPLE, cvPoint(5,5));

	 // iterate thro' all the contours
	 while(contours)
	 {

	 /*
	  * get the points joining a contour
	  *  and store the points in result
	  */
	 result = cvApproxPoly(contours, sizeof(CvContour),
			 storage, CV_POLY_APPROX_DP,
			 cvContourPerimeter(contours)*0.02, 0);

	 /*
	  * if num. of points is 4 (ie) quadrilateral
	  *  get the points and draw 4 lines to connect
	  *   the points to form a quadrilateral...
	  *
	  */
	 	 if(result->total==4)
	     {
	             CvPoint *pt[4];

	             /*
	              * iterate thro' the seq element
	              *  to get the 4 points
	              */
	             for(i=0;i<4;i++)
	                 pt[i] = (CvPoint*)cvGetSeqElem(result, i);


	             /*
	              * draw line connecting adjacent points
	              */
	             cvLine(ret, *pt[0], *pt[1], CV_RGB(0,255,0),1,8,0);
	             cvLine(ret, *pt[1], *pt[2], CV_RGB(0,255,0),1,8,0);
	             cvLine(ret, *pt[2], *pt[3], CV_RGB(0,255,0),1,8,0);
	             cvLine(ret, *pt[3], *pt[0], CV_RGB(0,255,0),1,8,0);
	     }

	 	 /*
	 	  * go to next contour
	 	  */
	 	contours = contours->h_next;
	 }

	 /*
	  * release temp image and
	  *  release storage space...
	  */
	 cvReleaseImage(&temp);
     cvReleaseMemStorage(&storage);


	 // return image "ret"
	return ret;

} // end of method contourDetect()...


int main(int argc, char* argv[])
{
	// load an image from file
	IplImage* src=cvLoadImage("053.jpeg",CV_LOAD_IMAGE_UNCHANGED);

	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}


	// an image for showing contours
	IplImage* contourDrawn = 0;


	cvStartWindowThread();

	// the method contourDetect()
	//  detect all contours and
	//   selects quad type contours
	//    draws them on to a copy of src
	//     and returns it
	contourDrawn = contourDetect(&src);

	// a window to display original source image
	cvNamedWindow("original",CV_WINDOW_NORMAL);
	cvShowImage("original", src);

	// wait for key event
	cvWaitKey(0);

	// a window to display contour drawn image
	cvNamedWindow("contours",CV_WINDOW_NORMAL);
	cvShowImage("contours",contourDrawn);


	// wait for key event
	cvWaitKey(0);

	// destroy windows and release img memory
	cvDestroyWindow("original");
	cvReleaseImage(&src);
	cvDestroyWindow("contours");
	cvReleaseImage(&contourDrawn);

	return 0;
}// end of main
