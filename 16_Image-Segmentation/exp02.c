/*
 *  Created by RPS Deepan @ 30-05-2013
 *
 *		Frame Differencing
 *			subtract one frame from another
 *			 and label the difference as foreground
 */


#include <cv.h>
#include <highgui.h>
#include <stdio.h>


// scratch and statistics-keeping images

// 3 channel images
IplImage *Iavg,*Idiff,*Iprev,*Ihi,*Ilow;
IplImage *Iscratch,*Iscratch2;

// 1 channel images
IplImage *Igray1,*Igray2,*Igray3;
IplImage *Ilow1,*Ilow2,*Ilow3;
IplImage *Ihi1,*Ihi2,*Ihi3;

IplImage *Imaskt;

// counts number of images learned
float Icount;

void AllocateImages(IplImage* I){

	CvSize sz = cvGetSize(I);

	Iavg  = cvCreateImage(sz,IPL_DEPTH_32F,3);
	Idiff = cvCreateImage(sz,IPL_DEPTH_32F,3);
	Iprev = cvCreateImage(sz,IPL_DEPTH_32F,3);
	Ihi   = cvCreateImage(sz,IPL_DEPTH_32F,3);
	Ilow  = cvCreateImage(sz,IPL_DEPTH_32F,3);

	Ilow1 = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Ilow2 = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Ilow3 = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Ihi1  = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Ihi2  = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Ihi3  = cvCreateImage(sz,IPL_DEPTH_32F,1);

	Iscratch = cvCreateImage(sz,IPL_DEPTH_32F,3);
	Iscratch2 = cvCreateImage(sz,IPL_DEPTH_32F,3);

	Igray1 = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Igray2 = cvCreateImage(sz,IPL_DEPTH_32F,1);
	Igray3 = cvCreateImage(sz,IPL_DEPTH_32F,1);

	Imaskt = cvCreateImage(sz,IPL_DEPTH_8U,1);


	cvZero(Iavg);
	cvZero(Idiff);
	cvZero(Iprev);
	cvZero(Ihi);
	cvZero(Ilow);


	cvZero(Iscratch);
	cvZero(Iscratch2);

	// to protect against divide by 0
	Icount = 0.00001;

}

// learn the bg statistics
void accumulateBg(IplImage *I)
{
	static int first = 1;
	cvCvtScale(I,Iscratch,1,0);

	if(!first){
		cvAcc(Iscratch,Iavg);
		cvAbsDiff(Iscratch,Iprev,Iscratch2);
		cvAcc(Iscratch2,Idiff);
		Icount +=1.0;
	}

	first = 0;
	cvCopy(Iscratch,Iprev);

}

void setHighThreshold(float scale)
{
	cvConvertScale(Idiff,Iscratch,scale);
	cvAdd(Iscratch,Iavg,Ihi);
	cvSplit(Ihi,Ihi1,Ihi2,Ihi3,0);

}


void setLowThreshold(float scale)
{
	cvConvertScale(Idiff,Iscratch,scale);
	cvSub(Iavg,Iscratch,Ilow);
	cvSplit(Ilow,Ilow1,Ilow2,Ilow3,0);

}

void createModelsFromStats(){

	cvConvertScale(Iavg,Iavg,(double)(1.0/Icount));
	cvConvertScale(Idiff,Idiff,(double)(1.0/Icount));

	// make sure diff is always something
	cvAddS(Idiff,cvScalar(1,1,1),Idiff);
	setHighThreshold(7.0);
	setLowThreshold(6);

}

void bgDiff(IplImage *I,IplImage *Imask){

	cvCvtScale(I,Iscratch,1,0);
	cvSplit(Iscratch,Igray1,Igray2,Igray3,0);

	cvInRange(Igray1,Ilow1,Ihi1,Imask);

	cvInRange(Igray2,Ilow2,Ihi2,Imaskt);
	cvor(Imask,Imaskt,Imask);

	cvInRange(Igray3,Ilow3,Ihi3,Imaskt);
	cvOr(Imask,Imaskt,Imask);

	cvSubRS(Imask,255,Imask);


}

void deallocateImages()
{
	cvReleaseImage(&Iavg);
	cvReleaseImage(&Idiff);
	cvReleaseImage(&Iprev);
	cvReleaseImage(&Ihi);
	cvReleaseImage(&Ilow);

	cvReleaseImage(&Ihi1);
	cvReleaseImage(&Ihi2);
	cvReleaseImage(&Ihi3);

	cvReleaseImage(&Ilow1);
	cvReleaseImage(&Ilow2);
	cvReleaseImage(&Ilow3);

	cvReleaseImage(&Iscratch);
	cvReleaseImage(&Iscratch2);

	cvReleaseImage(&Igray1);
	cvReleaseImage(&Igray2);
	cvReleaseImage(&Igray3);

	cvReleaseImage(&Imaskt);
}

int main(int argc, char** argv) {




	// container to store frames
		IplImage* frame;
		IplImage* prev;
		IplImage* frame_foreground;

		// a video capture obj
		CvCapture* capture = 0;


		// checking if the argument is valid
		if(argv[1]!=NULL)
		{
			printf("\n\nargv[1] => %s is valid...",argv[1]);
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


		int i=0;

		frame = cvQueryFrame(capture);
		AllocateImages(frame);

		// iterate thro' all the frames
		while(1)
		{
			i++;

			frame = cvQueryFrame(capture);

			if(!frame)
					break;



			// a small delay
			char user_input = cvWaitKey(60);

			if(user_input=='q')
			{
				printf("User Interrupts!\n");
				break;
			}

			prev = frame;

		}

		// release capture
		cvReleaseCapture(&capture);

		cvReleaseImage(&frame);

		return 0;

}
