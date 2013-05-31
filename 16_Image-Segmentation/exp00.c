/*
 *  Created by RPS Deepan @ 30-05-2013
 *
 *		store variations of line segment of bgr pixels in a video
 *		 from point 1 to 2 in a file
 */


#include <cv.h>
#include <highgui.h>
#include <stdio.h>



int main(int argc, char** argv, IplImage* prev1) {

	int j=0;

	// open files for storing data (RGB)
	FILE *fptrb = fopen("blines.csv","w");
	FILE *fptrg = fopen("glines.csv","w");
	FILE *fptrr = fopen("rlines.csv","w");

	//
	int max_buffer;
	IplImage* rawImage;
	int r[10000],g[10000],b[10000];
	CvLineIterator iterator;


	// container to store frames
		IplImage* frame;

		// a video capture obj
		CvCapture* capture = 0;


		// checking if the argument is valid
		if(argv[1]!=NULL)
		{
			printf("argv[1] => %s is valid...",argv[1]);
			capture = cvCreateFileCapture(argv[1]);

		}

		 else
		 {
			printf("Provide a proper argument...\nQuitting!\n");
			return -1;

		 }


		// if its null
		if(!capture)
		{
			printf("capture obj is null!");
			return -1;
		}


		// window
		cvStartWindowThread();
		cvNamedWindow("Source",CV_WINDOW_AUTOSIZE);

		// iterate thro' all the frames
		while(1)
		{

			frame = cvQueryFrame(capture);

			if(!frame)
				break;

			max_buffer = cvInitLineIterator(frame,cvPoint(50,30),cvPoint(150,200),&iterator,8,0);

			// write data on line segment to files
			//  pixel by pixel
			for(j=0;j<max_buffer;j++)
			{
				// write data to files
				fprintf(fptrb,"%d",iterator.ptr[0]);
				fprintf(fptrg,"%d",iterator.ptr[1]);
				fprintf(fptrr,"%d",iterator.ptr[2]);

				iterator.ptr[2] = 255;

				// go to next pixel
				CV_NEXT_LINE_POINT(iterator);
			}

			fprintf(fptrb,"\n");fprintf(fptrg,"\n");fprintf(fptrr,"\n");

			/*
			// a small delay
			char user_input = cvWaitKey(40);

			if(user_input=='q')
			{
				printf("User Interrupts!\n");
				break;
			}

			cvShowImage("Source",frame);*/

		}


		// close the files
		fclose(fptrb);fclose(fptrg);fclose(fptrr);
		// release capture
		cvReleaseCapture(&capture);
		//cvDestroyWindow("Source");
		cvReleaseImage(&frame);


		return 0;

}
