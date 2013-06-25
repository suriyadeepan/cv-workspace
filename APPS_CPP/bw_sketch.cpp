#include <opencv2/opencv.hpp>

#define BLUR_LEVEL 7
#define LAPLACE_MASK 5
#define THRESH_MIN 80

using namespace cv;

Mat applyBwSketch(Mat frame){
		
	// convert rgb to gray mat	
	Mat gray;
	cvtColor(frame,gray,CV_RGB2GRAY); 

	// blur
	medianBlur(gray,gray,BLUR_LEVEL);

	// apply laplacian filter
	Mat edges;
	Laplacian(gray,edges,CV_8U,LAPLACE_MASK);

	// binary threshold the image
	Mat thresh;
	threshold(edges,thresh,THRESH_MIN,255,THRESH_BINARY_INV);

	return thresh;

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
	namedWindow("BW Sketch");

	// iterate over each frame
	while(!stop)
	{
		// read a frame, check if its null
		if(!capture.read(vidFrame))
			break;
		
		// display image
		imshow("BW Sketch",applyBwSketch(vidFrame));

		// wait for time "delay", check for user key input
		if((char)waitKey(delay)=='q')
			stop=true;

	}

	// free memory
	capture.release();

	return 0;
}


