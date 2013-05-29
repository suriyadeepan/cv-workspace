/*
 *	Created by Selva Kumar - 31-01-2013
 *
 */
#include<stdio.h>
#include<cv.h>
#include<highgui.h>
 
int max = 255;
 
int lowHue = 10 ;
int lowSat = 0 ;
int lowVal = 0 ;
 
int highHue = 100 ;
int highSat = 255 ;
int highVal = 255 ;
 
void onLowHue ( int value ) { lowHue = value ; }
void onLowSat ( int value ) { lowSat = value ; }
void onLowVal ( int value ) { lowVal = value ; }
 
void onHighHue ( int value ) { highHue = value ; }
void onHighSat ( int value ) {  highSat = value ; }
void onHighVal ( int value ) { highVal = value ; }
 
IplImage* hsv_from_rgb(IplImage* _src);
IplImage* hsv_threshold ( IplImage* _hsv_src,
     CvScalar _min,
     CvScalar _max );
 
void cvCreateShowWindow(char* name, IplImage *src)
{
 cvNamedWindow(name,CV_WINDOW_NORMAL);
 cvShowImage(name, src);
  
}
 
IplImage* resize_640x480(IplImage* _src)
{
    IplImage* res = cvCreateImage( cvSize(640,480) ,
                                   _src->depth, 
                                   _src->nChannels
                                  );   
    cvResize ( _src, res, CV_INTER_LINEAR );
 return res;
}
 
int main ( int  argc, char* argv[] )
{
 if ( argc < 2 ) {
     printf ("Error: no input image found\n" ) ;
     exit (1) ;
   }
 cvStartWindowThread();
 
   IplImage* src = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
   cvCreateShowWindow("src", src);
   cvWaitKey(0);
   IplImage* cir = cvCloneImage (src) ;
   //IplImage* _src = cvCreateImage ( cvGetSize(src), IPL_DEPTH_8U, 1 ) ;
   //cvCvtColor (src, _src, CV_BGR2GRAY) ;
   IplImage* _src = resize_640x480 (src);
   //cvSmooth ( _src, _src, CV_GAUSSIAN, 15, 0, 0, 0);
 
   cvCreateShowWindow(" input", _src);
 
  cvCreateShowWindow("Output",_src  );
 
  cvCreateTrackbar("LowHue", "Output", &lowHue, max, onLowHue);
  cvCreateTrackbar("HighHue", "Output", &highHue, max, onHighHue);
 
  cvCreateTrackbar("LowSat", "Output", &lowSat, max, onLowSat);
  cvCreateTrackbar("HighSat", "Output", &highSat, max, onHighSat);
 
  cvCreateTrackbar("LowVal", "Output", &lowVal, max, onLowVal);
  cvCreateTrackbar("HighVal", "Output", &highVal, max, onHighVal);
 
  CvMemStorage* storage = cvCreateMemStorage(0);
  IplImage* hsved = hsv_from_rgb ( _src );
  IplImage* res ;
 while ( 1 )
 {
   res = hsv_threshold( hsved, 
                        cvScalar( lowHue, lowSat, lowVal, 0),
                        cvScalar( highHue, highSat, highVal, 255) );
   cvWaitKey(30);
   cvShowImage("Output", res );
  
 } // End of while loop
   
  cvCreateShowWindow("res", res);
  cvWaitKey(0);
  cvDestroyWindow("res");
  cvDestroyAllWindows();
}  
 
IplImage* hsv_from_rgb(IplImage* _src)
{
  IplImage* img = cvCloneImage ( _src ) ;
  cvCvtColor ( _src, img, CV_BGR2HSV );
  return img;
}
 
IplImage* hsv_threshold ( IplImage* _hsv_src,
     CvScalar _min,
     CvScalar _max )
{
    IplImage* thresholded = cvCreateImage(cvGetSize( _hsv_src ), 8, 1 );
    cvInRangeS( _hsv_src, _min, _max, thresholded );  
    return thresholded;  
}
