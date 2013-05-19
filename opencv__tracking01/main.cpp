#include <QCoreApplication>
/*
 * @author: Lothar Rubusch
 * @date: 2013-may-18
 *
 * opencv version: 2.4.5
 *
 * resources:
 * www.aishack.in/2010/07/tracking-colored-objects-in-opencv
 * opencv-srf.blogspot.ch/2010/09/object-detection-using-color-seperation.html
 *
 */

// Qt standards, not sure if necessry (but qmake needs it)
#include <QtGui>
#include <QtCore>
#include <QCoreApplication>

// openCV
#include <opencv/cv.h>
#include <opencv/highgui.h>

// This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage( IplImage* frame )
{
       // generate hsv image from rgb
       IplImage* imgHSV = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 3 );
       cvCvtColor( frame, imgHSV, CV_BGR2HSV ); // Change the color format from BGR to HSV

       // create a threshed image copy
       IplImage* imgThresh = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 1 );

       /*
        * HSV (Hue / Saturation / Value)
        *
        * hue        - the color
        * saturation - the "amount" of color
        * value      - the brightness of the color
        */
       // red color sceme
//       cvInRangeS( imgHSV, cvScalar( 170, 160, 60 ), cvScalar( 180, 256, 256 ), imgThresh );

       // Hue for gree: 38 - 75 (by link)
//       cvInRangeS( imgHSV, cvScalar( 38, 70, 70 ), cvScalar( 75, 256, 256 ), imgThresh );

       cvInRangeS( imgHSV, cvScalar( 38, 140, 100 ), cvScalar( 75, 256, 256 ), imgThresh );

       cvReleaseImage( &imgHSV );
       return imgThresh;
}



int main(int argc, char *argv[]){
      QCoreApplication a(argc, argv);

      /*
       * initialize capturing live feed from the camera
       */
      CvCapture *capture = 0;
      if( NULL == (capture = cvCaptureFromCAM( 0 ))){
            qDebug( "Capture failure" );
            return -1;
      }

      // set up a window
      cvNamedWindow( "threshed" );

      // iterate through each frames of the video
      IplImage *imgScribble = NULL;
      while( true ){

	    // obtain a new frame
            IplImage *frame = NULL;
            if( NULL == (frame = cvQueryFrame( capture ))){ break; }

            // apply blurrer
            frame = cvCloneImage( frame );
            //            cvSmooth( frame, frame, CV_GAUSSIAN, 3, 3 ); // smooth the original image using Gaussian kernel

	    // initialize scribble data for the moving target
	    if( NULL == imgScribble ){
                    imgScribble = cvCreateImage( cvGetSize( frame ), 8, 3 );
	    }

	    // get threshed image out of frame
            IplImage *imgThresh = GetThresholdedImage( frame );   
            cvSmooth( imgThresh, imgThresh, CV_GAUSSIAN, 3, 3 ); // smooth the binary image using Gaussian kernel

/* TODO failing
	    // compute the moments to estimate the position of the target object
	    CvMoments *moments = NULL;
	    if( NULL == (moments = (CvMoments*) malloc( sizeof( CvMoments ) )) ){
   	            qDebug( "ERROR: allocation failed\n" );
                    break;
	    }
	    cvMoments( imgThresh, moments, 1 );

	    // the actual moment value
	    double area = cvGetCentralMoment( moments, 0, 0 );

	    // the x-coord
	    double moment10 = cvGetSpatialMoment( moments, 1, 0 );

	    // the y-coord
	    double moment01 = cvGetSpatialMoment( moments, 0, 1 );

	    static int xpos = 0;
	    static int ypos = 0;

	    int xlast = moment10 / area;
	    int ylast = moment01 / area;

	    printf("position (%d, %d)\n", xpos, ypos );

	    // draw a line if it is a valid position
	    if( xlast > 0
		&& ylast > 0
		&& xpos > 0
		&& ypos > 0
		){
	      // draw a yellow line, width 5 pixels
	      cvLine( imgScribble, cvPoint( xpos, ypos ), cvPoint( xlast, ylast ), cvScalar( 0, 255, 255 ), 5 );
	    }
	    cvAdd( frame, imgScribble, frame );
//*/

            // show image in window
            cvShowImage("threshed", imgThresh);

            // clean up used images
            cvReleaseImage(&imgThresh);
            cvReleaseImage(&frame);
//	    delete moments;

            // wait 50ms; if 'ESC' is pressed, break the loop
            if( 27 == (char) cvWaitKey(10) ){ break; }
      }

      cvDestroyAllWindows() ;
      cvReleaseCapture(&capture);

      return a.exec();
}
