#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv){

	Mat src = imread(argv[1],1);	

	Mat roiSrc(src, Rect(100,100,100,100));
	
	imshow("src",roiSrc);

	waitKey(0);

	return 0;

}
