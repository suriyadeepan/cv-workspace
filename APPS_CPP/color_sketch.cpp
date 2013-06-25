#include <opencv2/opencv.hpp>

#define FILTER_KERNEL_SIZE 2 
#define SIGMA_COLOR 2 
#define SIGMA_SPACE 4
#define IMAGE_RESIZE_FACTOR 2

using namespace cv;

Mat applyColorSketch(Mat frame)
{	
	Mat filtered,temp;	

	for(int i=0;i<7;i++)
	{
		bilateralFilter(frame,temp,FILTER_KERNEL_SIZE,SIGMA_COLOR,SIGMA_SPACE);
		bilateralFilter(temp,filtered,FILTER_KERNEL_SIZE,SIGMA_COLOR,SIGMA_SPACE);
	}

	Mat mask;

	threshold(frame,mask,80,255,THRESH_BINARY_INV);

	Mat final;

	filtered.copyTo(final,mask);

	return final;
}

Mat crop(Mat src, float factor)
{
	Mat cropped;
	
	Size sizeSrc = src.size();
	Size sizeCropped;

	sizeCropped.height = sizeSrc.height/factor;
	sizeCropped.width = sizeSrc.width/factor;

	resize(src,cropped,sizeCropped,0,0,INTER_LINEAR);

	return cropped;

}

int main(int argc,char *argv[])
{
	// frame from a video
	Mat vidFrame;

	// video capture object
	VideoCapture capture(argv[1]);
	
	// if video file is not opened
	if(!capture.isOpened())
		return -1;

	// get frame rate
	double rate = capture.get(CV_CAP_PROP_FPS);
	// calc delay from frame rate
	int delay = 1000/rate;

	// flag to stop
	bool stop(false);
	
	// create window	
	namedWindow("Color Sketch");

	// iterate over each frame
	while(!stop)
	{
		// read a frame, check if its null
		if(!capture.read(vidFrame))
			break;
		
		// display image
		imshow("Color Sketch",applyColorSketch(crop(vidFrame,IMAGE_RESIZE_FACTOR) ) );

		// wait for time "delay", check for user key input
		if((char)waitKey(2)=='q')
			stop=true;

	}

	// free memory
	capture.release();

	return 0;
}


