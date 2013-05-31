#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
	IplImage* src;
	IplImage* cloneOfSrc;
	IplImage* cloneOfTemp;


	src = cvLoadImage("current.jpg",CV_LOAD_IMAGE_UNCHANGED);

	CvSeq* contours;
	CvSeq* temp;

	CvMemStorage* storage = cvCreateMemStorage(0);

	// a temp binary image
	IplImage* tempImg = cvCreateImage(cvGetSize(src),8,1);


	// find edges
	cvCanny(src,tempImg,8,8,3);



	cloneOfTemp = cvCloneImage(tempImg);

	// find contours
	cvFindContours(cloneOfTemp,storage,&contours,sizeof(CvContour),CV_RETR_LIST,
			CV_LINK_RUNS,cvPoint(0,0));


	// draw all contours
	cloneOfSrc= cvCloneImage(src);
	cvDrawContours(cloneOfSrc,contours,cvScalar(255,0,0,0),cvScalar(0,0,255,0),1,1,8,cvPoint(5,5));

	cvSaveImage("current.jpg",cloneOfSrc,0);

	// release memory
	cvReleaseImage(&src);
	cvReleaseImage(&tempImg);
	cvReleaseImage(&cloneOfTemp);

   cvReleaseMemStorage(&storage);

	return 0;

}
