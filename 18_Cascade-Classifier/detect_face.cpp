#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <stdio.h>

using namespace std;
using namespace cv;

String face_cascade_file = "file1.xml";
CascadeClassifier face_cascade;


Mat detect(Mat im){

	Mat gray;
	Mat result= im.clone();

	// a vector to hold the detected faces
	std::vector<Rect> faces;

	// BGR to GRAYSCALE
	cvtColor(im,gray,CV_BGR2GRAY);
	// Histogram equalization
	equalizeHist(gray,gray);

	// detect 
	face_cascade.detectMultiScale( gray, faces, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	for(int i=0;i<faces.size();i++){

	// draw a bounding box
	rectangle( result, cvPoint(faces[i].x, faces[i].y), cvPoint(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0,0,255),1,8,0);

	}

	return result; 
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

int main(int argc,char *argv[]){

	VideoCapture capture(argv[1]);
	Mat frame;

	// if video file is not opened
 	if(!capture.isOpened())
		return -1;

 	// flag to stop
 	bool stop(false);
	
	// create window	
	namedWindow("Face Detection");
					

	if( !face_cascade.load(face_cascade_file) ){
	       printf("Check the cascade file!");
	       return -1;	       
	}	     

	while(!stop){

		if(!capture.read(frame)){
			printf("Error in Video!");
			stop = true;
		}

	imshow("Face Detection",detect( crop(frame,4) ) );

	waitKey(2);

	}

	capture.release();		
	return 0;
}
