#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <stdio.h>

using namespace std;
using namespace cv;

// cascade file name
String face_cascade_file = "file1.xml";

// classifier instance
CascadeClassifier face_cascade;

// this function gets a frame from video/cam as input
//  detects faces in it and draws on a clone of the frame
Mat detect(Mat im){

	// grayscale image 
	Mat gray;

	// a copy of original frame - to draw, return
	Mat result= im.clone();

	// a vector to hold the detected faces
	std::vector<Rect> faces;

	// BGR to GRAYSCALE
	cvtColor(im,gray,CV_BGR2GRAY);
	// Histogram equalization
	equalizeHist(gray,gray);

	// detect 
	face_cascade.detectMultiScale( gray, faces, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	// iterate thro' all the faces found
	for(int i=0;i<faces.size();i++){

	// draw a bounding box
	rectangle( result, cvPoint(faces[i].x, faces[i].y), cvPoint(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0,0,255),1,8,0);

	}

	return result; 
}// end of detect()...

// crop the image for faster operations
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

// ---MAIN---
int main(int argc,char *argv[]){

	// get a video file as argument
	VideoCapture capture(argv[1]);

	// frame from video
	Mat frame;

	// if video file is not opened
 	if(!capture.isOpened())
		return -1;

 	// flag to stop video
 	bool stop(false);
	
	// create window	
	namedWindow("Face Detection");
					
	// load the data from cascade file into the
	//  classifier instance
	if( !face_cascade.load(face_cascade_file) ){
		// if not successful,
	       printf("Check the cascade file!");
	       return -1;	       
	}	     

	// iterate thro' frames in the video
	while(!stop){

	// if frame cant be read,
	if(!capture.read(frame)){
		printf("Error in Video!");
		stop = true;
	}

	// detect faces in the cropped frame
	imshow("Face Detection",detect( crop(frame,4) ) );

	// wait for just 2ms - detection operation already takes a lot 
	//  of time
	waitKey(2);

	}// end of while...

	// free memory
	capture.release();		

	return 0;

}// __END OF MAIN__
