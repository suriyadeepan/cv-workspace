/*
 *	Created by RPS Deepan - 05-01-2013
 *	 reference - Learning OpenCV - Chapter 6 : Image Transforms
 *
 *	 	1. testing affine transformation
 *			using cvWarpAffine() method
 *			 with cvGetAffineTransform()
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>

int main(int argc, char* argv[])
{
	/*
	 *  warp matrices contains the points
	 *   on src to be mapped
	 *  contains points over which mapping
	 *   is done
	 *
	 */
	CvPoint2D32f srcTri[3],dstTri[3];

	// map matrices
	CvMat* rotMat = cvCreateMat(2,3,CV_32FC1);
	CvMat* warpMat = cvCreateMat(2,3,CV_32FC1);


	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	// display source
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	cvWaitKey(0);

	IplImage* dst = cvCloneImage(src);

	dst->origin = src->origin;

	cvZero(dst);

	/*
	 *  compute warp matrices
	 *   by considering 3 corner points
	 */

	// source
	// top left corner
	srcTri[0].x=0;
	srcTri[0].y=0;
	// top right corner
	srcTri[1].x=(src->width)-1;
	srcTri[1].y=0;

	// bottom left
	srcTri[2].x=0;
	srcTri[2].y=(src->height)-1;

	// destination
	// top left
	dstTri[0].x=(src->width)*0.0;
	dstTri[0].y=(src->height)*0.33;
	// top right
	dstTri[1].x=(src->width)*0.85;
	dstTri[1].y=(src->height)*0.25;
	// bottom left
	dstTri[2].x=(src->width)*0.15;
	dstTri[2].y=(src->height)*0.7;

	// get warp_mat using cvGetAffineTransform()
	cvGetAffineTransform(srcTri,dstTri,warpMat);

	// warp the image using warpMat
	//  obtained from above step
	cvWarpAffine(src,dst,warpMat,CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,CV_RGB(0,0,0));

	// display warped image
	cvNamedWindow("Warped",CV_WINDOW_NORMAL);
	cvShowImage("Warped",dst);

	// wait for key press
	cvWaitKey(0);

	return 0;
}// end of main
