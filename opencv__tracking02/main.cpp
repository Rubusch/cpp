#include <QCoreApplication>
/*
 * @author: Lothar Rubusch
 * @date: 2013-may-18
 *
 * resources:
 * www.aishack.in/2010/07/tracking-colored-objects-in-opencv
 * opencv-srf.blogspot.ch/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <QtGui>
#include <QtCore>
#include <QCoreApplication>

#include <opencv/cv.h>
#include <opencv/highgui.h>


//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage( IplImage* imgHSV )
{
       // create a threshed image copy
       IplImage* imgThresh = cvCreateImage( cvGetSize( imgHSV ), IPL_DEPTH_8U, 1 );

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

       cvInRangeS( imgHSV, cvScalar( 38, 90, 70 ), cvScalar( 75, 256, 256 ), imgThresh );



       return imgThresh;
}

int main(int argc, char* argv[]){
      QCoreApplication a(argc, argv);

      /*
       * initialize capturing live feed from the camera
       */
      CvCapture* capture = 0;
      if( NULL == (capture = cvCaptureFromCAM( 0 ))){
            qDebug( "Capture failure" );
            return -1;
      }

      // set up a window
      cvNamedWindow( "target" );

      // iterate through each frames of the video
      IplImage* imgScriple = NULL;
      IplImage* frame = NULL;
      while( true ){

	// obtain a new frame
	if( NULL == (frame = cvQueryFrame( capture ))){ break; }

            frame = cvCloneImage( frame );
            cvSmooth( frame, frame, CV_GAUSSIAN, 3, 3 ); // smooth the original image using Gaussian kernel

            IplImage* imgHSV = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 3 );
            cvCvtColor( frame, imgHSV, CV_BGR2HSV ); // Change the color format from BGR to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);

            cvSmooth(imgThresh, imgThresh, CV_GAUSSIAN,3,3); //smooth the binary image using Gaussian kernel

            // show image in window
            cvShowImage("target", imgThresh);

            //Clean up used images
            cvReleaseImage(&imgHSV);
            cvReleaseImage(&imgThresh);
            cvReleaseImage(&frame);

            //Wait 50mS
            int c = cvWaitKey(10);
            //If 'ESC' is pressed, break the loop
            if((char)c==27 ) break;
      }

      cvDestroyAllWindows() ;
      cvReleaseCapture(&capture);

/*
    QLabel *label = new QLabel();
        label->setPixmap( png_new );
        label->show();
        return app.exec();
*/
      return a.exec();
}
