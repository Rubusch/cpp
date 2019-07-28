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

// Qt
#include <QtGui>
#include <QtCore>
#include <QCoreApplication>

// openCV
#include <opencv/cv.h>
#include <opencv/highgui.h>


IplImage *imgTracking = NULL;
int xlast = -1;
int ylast = -1;

// threshold hsv image
IplImage* get_threshold_image( IplImage *frame )
{
	cvSmooth( frame, frame, CV_GAUSSIAN, 3, 3 );

	// generate hsv image from rgb
	IplImage* imgHSV = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 3 );
	cvCvtColor( frame, imgHSV, CV_BGR2HSV ); // Change the color format from BGR to HSV
	IplImage* imgThresh = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 1 );
	cvInRangeS( imgHSV, cvScalar( 38, 140, 100 ), cvScalar( 75, 256, 256 ), imgThresh );
	cvReleaseImage( &imgHSV );
	return imgThresh;
}


void track_object( IplImage *imgThresh )
{
	// compute the "moments" in imgThresh
	CvMoments *moments = NULL;
	if( NULL == (moments = (CvMoments *) malloc( sizeof(*moments) )) ){
		// XXX why the hack "malloc" in cpp??!!!
		QMessageBox::critical(0, QString( "ERROR" ), QString( "Allocation failed." ));
		return;
	}
	cvMoments( imgThresh, moments, 1 );
	double area = cvGetCentralMoment( moments, 0, 0 );
	double moment10 = cvGetSpatialMoment( moments, 1, 0 );
	double moment01 = cvGetSpatialMoment( moments, 0, 1 );
	free( moments );

	/*
	  if the area is <1000, area is considered noise and ignored
	*/
	if( 1000 >= area ){
		printf("area too small\n");
		return;
	}

	// compute position
	int xpos = moment10 / area;
	int ypos = moment01 / area;

	if( 0 <= xlast
	    && 0 <= ylast
	    && 0 <= xpos
	    && 0 <= ypos
	){
		// draw trace..
		printf("x:y - %d:%d\n", xpos, ypos);
		cvLine( imgTracking, cvPoint( xpos, ypos ), cvPoint( xlast, ylast ), cvScalar( 0, 0, 255), 5 );
	}

	xlast = xpos;
	ylast = ypos;
}


int main( int argc, char *argv[] )
{
	QCoreApplication a(argc, argv);



        CvCapture *capture = 0;
	if( NULL == (capture = cvCaptureFromCAM( 0 )) ){
		QMessageBox::critical( 0, QString( "ERROR" ), QString( "capture failed." ));
		return -1;
	}


	// fetch first frame
	IplImage *frame = NULL;
	if( NULL == (frame = cvQueryFrame( capture )) ){
		QMessageBox::critical( 0, QString( "Error" ), QString( "frame query failed." ));
		return -1;
	}

	// create a blank image and assigned to "imgTracking"
	imgTracking = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 3 );
	cvZero( imgTracking ); // convert imgTracking to black


	cvNamedWindow( "target" );
	while( true ){

		// fetch regular frames
		IplImage *frame = NULL;
		frame = NULL;
		if( NULL == (frame = cvQueryFrame( capture )) ){
			QMessageBox::critical( 0, QString( "Error" ), QString( "frame query failed." ));
			break;
		}
		frame = cvCloneImage( frame );
		IplImage *imgThresh = get_threshold_image( frame );

                // blur binary image, using gaussian kernel
		cvSmooth( imgThresh, imgThresh, CV_GAUSSIAN, 3, 3 );

		track_object( imgThresh );
/*
		cvAdd( frame, imgTracking, frame );
/*/
  // DEBUG: nice to have: how to draw within imgThresh? Anyway coords are printed
//		cvAdd( imgThresh, imgTracking, imgThresh );
//*/

		cvShowImage( "target", imgThresh );

		// cleanup
		cvReleaseImage( &imgThresh );
		cvReleaseImage( &frame );

		// wait 10 ms, then if ESC is pressed, beak
		if( 27 == cvWaitKey(10) ){
			break;
		}
	}

	cvDestroyAllWindows();
	cvReleaseImage( &imgTracking );
	cvReleaseCapture( &capture );

	return a.exec();
}
