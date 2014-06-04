#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

CascadeClassifier cascade;

void detectVehicles(Mat* img){

    vector<Rect> vehicles;

    Mat gray;

    // convert to Grayscale
    cvtColor( *img, gray, CV_BGR2GRAY );

    // Histogram Equalization
    equalizeHist( gray, gray );

    /* Detect Multiscale : Prototype
     *
     * void CascadeClassifier::detectMultiScale(InputArray image,
     *          vector<Rect>& objects, double scaleFactor=1.1, 
     *          int minNeighbors=3, int flags=0, Size minSize=Size(), 
     *          Size maxSize=Size())
     */
    cascade.detectMultiScale( gray, vehicles,
        1.1, 2, 0, Size(5, 5) );

    for( int i = 0; i < vehicles.size(); i++ ){

        Point center( vehicles[i].x + vehicles[i].width*0.5,
                vehicles[i].y + vehicles[i].height*0.5 );
        ellipse( *img, center, Size( vehicles[i].width*0.5,
                    vehicles[i].height*0.5), 0, 0, 360,
                        Scalar( 255, 0, 255 ), 4, 8, 0 );


/*      void rectangle(Mat& img, Point pt1, Point pt2,
 *      const Scalar& color,
 *      int thickness=1, int lineType=8, int shift=0)
 */
    }


}

int main(int argc, char** argv){

    Mat frame;

    // load cascade
    cascade.load("cars3.xml");

    VideoCapture cap(argv[1]);

    if ( !cap.isOpened() ){ 

        printf("\n\nCannot open the video file\n");
    }

    cap.set(CV_CAP_PROP_POS_MSEC, 300); 

    double fps = cap.get(CV_CAP_PROP_FPS); 


    while(1){

        if( !cap.read(frame) )
            break;

        detectVehicles(&frame);

        // lets detect vehicles!
        imshow("Detected",frame);

        waitKey(90);

    }


    cvDestroyWindow("Detected");

    return 0;
}

