#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc,char *argv[])
{

	Mat vidFrame;
	VideoCapture capture(argv[1]);

	if(!capture.isOpened())
		return -1;

	// get frame rate
	double rate = capture.get(CV_CAP_PROP_FPS);

	// flag to stop
	bool stop(false);
		
	namedWindow("Extracted Frame");

	while(!stop)
	{
		if(!capture.read(vidFrame))
			break;
		
		Mat gray;

		cvtColor(vidFrame,gray,CV_RGB2GRAY); 
		medianBlur(gray,gray,7);

		Mat edges;

		Laplacian(gray,edges,CV_8U,5);

		Mat thresh;

		threshold(edges,thresh,80,255,THRESH_BINARY_INV);

		imshow("Extracted Frame",thresh);

		if(waitKey(50)>=0)
			stop=true;

	}

	capture.release();

	return 0;

}


