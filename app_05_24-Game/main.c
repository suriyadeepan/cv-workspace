#include <cv.h>
#include <highgui.h>
#include <stdio.h>

#define THRESH_VALUE 100
#define CONTOUR_MAX_AREA 50

IplImage* preProcess(IplImage* img)
{

	// temp -> grayscale form of source image "img"
    //  for contour detection
	IplImage* temp = cvCreateImage(cvGetSize(img), 8, 1);

	// converting "img" to grayscale and
	//  and storing in temp
	cvCvtColor(img, temp, CV_BGR2GRAY);

	// blur the image
	cvSmooth(temp,temp,CV_GAUSSIAN,5,0,0,0);

	// binary threshold
	cvThreshold(temp,temp,THRESH_VALUE,255,CV_THRESH_BINARY);

	return temp;

}

// the method contourDetect()
//  detect all contours and
//   draws them on to a copy of src
//    and returns it
IplImage* contourDetect(IplImage* temp,IplImage* src)
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

	// ret -> this image is a copy of source image "temp"
	//  on which contours are drawn and returned
	 IplImage* ret = cvCreateImage(cvGetSize(temp), 8, 3);




	// find all contours in temp and
	//  store them in contours
	 cvFindContours(temp,storage, &contours,sizeof(CvContour),CV_RETR_LIST,
		        CV_CHAIN_APPROX_SIMPLE, cvPoint(5,5));



	 int num=0;

	 // iterate thro' all the contours
	 while(contours)
	 {

		 /*
		  * get the points joining a contour
		  *  and store the points in result
		  */

		 double peri = cvArcLength(contours,CV_WHOLE_SEQ,-1);
		 result = cvApproxPoly(contours, sizeof(CvContour),
			 storage, CV_POLY_APPROX_DP,
			 0.02*peri, 1);

	 /*
	  * if num. of points is 4 (ie) quadrilateral
	  *  get the points and draw 4 lines to connect
	  *   the points to form a quadrilateral...
	  *
	  */


	 	 if(result->total==4 && fabs(cvContourArea(result, CV_WHOLE_SEQ,0))>CONTOUR_MAX_AREA)
	 	 {

	 		// Find Perimeter of each contour
	 		printf("Contour%d Perimeter: %lf\n",++num,cvArcLength(result,CV_WHOLE_SEQ,-1));

			CvPoint pt[4];

	 		CvPoint2D32f srcPt[4],dstPt[4];

	 		// set dest points
	 		dstPt[0] = cvPoint2D32f(100,100);
	 		dstPt[1] = cvPoint2D32f(549,100);
	 		dstPt[2] = cvPoint2D32f(549,549);
	 		dstPt[3] = cvPoint2D32f(100,549);


 			// map matrices
 			CvMat* warpMat = cvCreateMat(3,3,CV_32FC1);


	        CvPoint* temp_pt;
	 		CvPoint2D32f* temp_pt_f;

	        for(i=0;i<4;i++)
	        {
	        	temp_pt = (CvPoint*)cvGetSeqElem(result, i);
	            pt[i] = *temp_pt;
	            temp_pt_f = (CvPoint2D32f*)cvGetSeqElem(result,i);
	            srcPt[i] = *temp_pt_f;
	        }


	        // draw lines to bound contour
	        cvLine(ret, pt[0], pt[1], CV_RGB(0,255,0),1,8,0);
	        cvLine(ret, pt[1], pt[2], CV_RGB(0,255,0),1,8,0);
	        cvLine(ret, pt[2], pt[3], CV_RGB(0,255,0),1,8,0);
	        cvLine(ret, pt[3], pt[0], CV_RGB(0,255,0),1,8,0);



	    	cvNamedWindow("BeforeWarping",CV_WINDOW_NORMAL);
	    	cvShowImage("BeforeWarping",ret);

	    	/*
	    	CvBox2D minBox = cvMinAreaRect2( result, NULL);
	    	cvBoxPoints( minBox, srcPt);
			*/



	    	// get warp_mat using this method
	    	cvGetPerspectiveTransform(srcPt,dstPt,warpMat);

	    	int j=0,k=0;

	    	for(j=0;j<warpMat->rows;j++){
	    		for(k=0;k<warpMat->cols;k++){

	    			printf(" %f ",cvGetReal2D(warpMat,j,k));
	    		}
	    	printf("\n");
	 	 	 }

	    	// warp the image using warpMat
	    	//  obtained from above step
	    	IplImage* srcClone = cvCloneImage(src);
	    	//cvWarpPerspective(srcClone,srcClone,warpMat,CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,CV_RGB(0,0,0));
	    	cvPerspectiveTransform(srcClone,srcClone,warpMat);



	    	cvNamedWindow("Warped",CV_WINDOW_NORMAL);
	    	cvShowImage("Warped",srcClone);

	    	cvWaitKey(0);

	     }

	 	 /*
	 	  * go to next contour
	 	  */
	 	 contours = contours->h_next;
	 }

	 // instead of iterating thro' all the contours,
	 //  using drawContours() functions to draw all the contours
	// cvDrawContours(ret,contours,cvScalar(255,0,0,0),cvScalar(0,0,255,0),1,1,8,cvPoint(5,5));


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

	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	// display the src and contour-drawn images
	cvStartWindowThread();


	//cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvNamedWindow("Contour",CV_WINDOW_NORMAL);

	//cvShowImage("Source",src);
	cvShowImage("Contour",contourDetect(preProcess(src),src));


	cvWaitKey(0);

	return 0;



}
