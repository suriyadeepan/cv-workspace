/*
 *	Created by RPS Deepan - 05-01-2013
 *	 reference - Learning OpenCV - Chapter 6 : Image Transforms
 *
 *	 	1. testing affine transformation
 *			using cvWarpAffine() method
 *			 with cvGetAffineTransform()
 *		2. tested Rotation of image using
 *		    cvWarpAffine() with cv2DRotationMatrix()
 */


#include<stdio.h>
#include<cv.h>
#include<highgui.h>

void warpImage(IplImage** img)
{

	IplImage* dst = cvCloneImage(*img);

	dst->origin = (*img)->origin;

	cvZero(dst);

		/*
		 *  warp matrices contains the points
		 *   on src to be mapped
		 *  contains points over which mapping
		 *   is done
		 *
		 */
		CvPoint2D32f srcTri[3],dstTri[3];

		// map matrices
		CvMat* warpMat = cvCreateMat(2,3,CV_32FC1);



	/*
	 *  compute warp matrices
	 *   by considering 3 corner points
	 */

	// source
	// top left corner
	srcTri[0].x=0;
	srcTri[0].y=0;
	// top right corner
	srcTri[1].x=((*img)->width)-1;
	srcTri[1].y=0;

	// bottom left
	srcTri[2].x=0;
	srcTri[2].y=((*img)->height)-1;

	// destination
	// top left
	dstTri[0].x=((*img)->width)*0.0;
	dstTri[0].y=((*img)->height)*0.33;
	// top right
	dstTri[1].x=((*img)->width)*0.85;
	dstTri[1].y=((*img)->height)*0.25;
	// bottom left
	dstTri[2].x=((*img)->width)*0.15;
	dstTri[2].y=((*img)->height)*0.7;

	// get warp_mat using cvGetAffineTransform()
	cvGetAffineTransform(srcTri,dstTri,warpMat);

	// warp the image using warpMat
	//  obtained from above step
	cvWarpAffine(*img,dst,warpMat,CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,CV_RGB(0,0,0));

	// display warped image
	cvNamedWindow("Warped",CV_WINDOW_NORMAL);
	cvShowImage("Warped",dst);

	// wait for key press
	cvWaitKey(0);

	// release memory
	cvReleaseImage(&dst);
	cvDestroyWindow("Warped");
	cvReleaseMat(&warpMat);

}


void rotateImage(IplImage** img,double angle)
{


	IplImage* dst = cvCloneImage(*img);

	dst->origin = (*img)->origin;

	cvZero(dst);

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




	/*
	 *  compute warp matrices
	 *   by considering 3 corner points
	 */

	// source
	// top left corner
	srcTri[0].x=0;
	srcTri[0].y=0;
	// top right corner
	srcTri[1].x=((*img)->width)-1;
	srcTri[1].y=0;

	// bottom left
	srcTri[2].x=0;
	srcTri[2].y=((*img)->height)-1;

	// destination
	// top left
	dstTri[0].x=((*img)->width)*0.0;
	dstTri[0].y=((*img)->height)*0.33;
	// top right
	dstTri[1].x=((*img)->width)*0.85;
	dstTri[1].y=((*img)->height)*0.25;
	// bottom left
	dstTri[2].x=((*img)->width)*0.15;
	dstTri[2].y=((*img)->height)*0.7;

	// get center point from img
	CvPoint2D32f center = cvPoint2D32f((dst->width)/2,(dst->height)/2);

	// get rotMat using cvGetAffineTransform()
	cv2DRotationMatrix(center,angle,0.6,rotMat);

	// rotate the image using rotMat
	//  obtained from above step
	cvWarpAffine(*img,dst,rotMat,CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,CV_RGB(0,0,0));

	// display rotated image
	cvNamedWindow("Rotated",CV_WINDOW_NORMAL);
	cvShowImage("Rotated",dst);

	// wait for key press
	cvWaitKey(0);

	// release memory
	cvReleaseImage(&dst);
	cvDestroyWindow("Rotated");
	cvReleaseMat(&rotMat);


}

int main(int argc, char* argv[])
{

	IplImage* src = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);

	cvStartWindowThread();

	// display source
	cvNamedWindow("Source",CV_WINDOW_NORMAL);
	cvShowImage("Source",src);

	cvWaitKey(0);

	//warpImage(&src);

	// rotation parameters
	// double angle=0;

	// index variable for iterating
	int i=0;

	for(i=0;i<5;i++)
	rotateImage(&src,(double)(i*45));



	// release memory
	cvDestroyAllWindows();
	cvReleaseImage(&src);

	return 0;
}// end of main
