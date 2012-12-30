/*
Code copied from [aishack.in]
[http://www.aishack.in/2010/01/generating-uniform-noise/]

Modified by RPS Deepan- 30/12/2012
	generate Uniform noise
	 generate a random number
	  and add it to value of a pixel
	   in a loop
*/



#include <stdio.h>	// For printf()
#include <cv.h>		// Main OpenCV library.
#include <highgui.h>	// OpenCV functions for files and graphical windows.


/*
 * this method generates a random
 *  number and maps it to the
 *   range -0.5 to 0.5
 */
double uniformRand()
{

	return (rand()/(float)0x7fff)-0.5;

}// end of method uniformRand()...



/*
 * this method generates random num
 *  maps it to -0.5 to 0.5
 *   adds it the original pixel value
 *
 */
IplImage* addUniformNoise(IplImage** img,float noiseIntensity)
{


	/*
	 *  a clone of img for preserving
	 *   the original img
	 */
	IplImage* tempImg=cvCloneImage(*img);


	// get dimensions from image
	int width=tempImg->width;
	int height=tempImg->height;

	// index variables
	int i=0,j=0;

	/*
	 * iterate thro' the pixels
	 *  of the image to add noise
	 *   to each pixel
	 */
	for(j=0; j<height ;j++)
	{

		for(i=0; i< width ;i++)
		{
			// generate a random number
			int randomValue = (char)((uniformRand())*noiseIntensity);

			// Here we "apply" the noise to the current pixel
			int pixelValue = cvGetReal2D(tempImg, j, i)+randomValue;

		    // And set this value in our noisy image
			cvSetReal2D(tempImg, j, i, pixelValue);
		}
	}// end of for loop...

	// return noisy image...
	return tempImg;

}// end of method addUniformNoise()...


int main(int argc, char* argv[])
{
	// noise Strength
	int noiseStrength=255;

	// load an image from file
	IplImage* src=cvLoadImage("07.jpg",0);
	IplImage* noisyImg=cvCreateImage(cvGetSize(src),8,1);


	cvStartWindowThread();


	// if img file not available
	//  print error msg and exit
	if(!src)
	{
		printf("\nCheck input image file location...\nImage file not found!\n");
		exit(1);
	}

	// get noiseStrength as input from user
	printf("Enter Noise Strength: ");
	scanf("%d",&noiseStrength);

	// limit the noiseStrength
	if(noiseStrength>255)
		noiseStrength=255;

	else if(noiseStrength<0)
		noiseStrength=0;



	// display original input image
	cvNamedWindow("input",CV_WINDOW_NORMAL);
	cvShowImage("input",src);

	// wait for key event
	cvWaitKey(0);

	// add noise to src image
	noisyImg = addUniformNoise(&src,noiseStrength);

	// display noisy image
	cvNamedWindow("noisy",CV_WINDOW_NORMAL);
	cvShowImage("noisy",noisyImg);


	// wait for key event
	cvWaitKey(0);



	// clean up memory...
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&noisyImg);

	return 0;

}// end of main
