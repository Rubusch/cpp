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
#include <QtCore>
#include <QCoreApplication>

// openCV
#include <opencv/cv.h>
#include <opencv/highgui.h>

// c
#include <cstdlib>

IplImage *imgTracking = NULL;

// threshold hsv image
IplImage* get_threshold_image( IplImage *frame )
{
    cvSmooth( frame, frame, CV_GAUSSIAN, 3, 3 );

    // generate hsv image from rgb
    IplImage* imgHSV = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 3 );
    cvCvtColor( frame, imgHSV, CV_BGR2HSV ); // Change the color format from BGR to HSV
    IplImage* imgThresh = cvCreateImage( cvGetSize( frame ), IPL_DEPTH_8U, 1 );

    /*
     * settings - several callibrations set up here
     */

    // home
//    cvInRangeS( imgHSV, cvScalar( 38, 140, 100 ), cvScalar( 75, 256, 256 ), imgThresh );


    // lab
    cvInRangeS( imgHSV, cvScalar( 38, 100, 70 ), cvScalar( 75, 256, 256 ), imgThresh );


    cvReleaseImage( &imgHSV );
    return imgThresh;
}


void track_object( IplImage *imgThresh )
{
    // compute the "moments" in imgThresh
    CvMoments *moments = NULL;
    if( NULL == (moments = (CvMoments *) malloc( sizeof(*moments) )) ){
        printf("ERROR: allocation failed\n");
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
        qDebug("DEBUG: area too small");
        return;
    }

    // compute position
    int xpos = moment10 / area;
    int ypos = moment01 / area;

    if( 0 <= xpos
        && 0 <= ypos
    ){
        // draw trace..
        char rc5_id[] = "7";
        char rc5_xpos[8]; sprintf( rc5_xpos, "%d", xpos );
        char rc5_ypos[8]; sprintf( rc5_ypos, "%d", ypos );
        char rc5_xtarget[] = "600";
        char rc5_ytarget[] = "350";

        // no exec because, in Qt no fork() possible, thus should be at least some qthread...
        char rc5_cmd[64]; sprintf( rc5_cmd, "/opt/git_cpp/irtransclientmac/sendpackets %s %s %s %s %s", rc5_id, rc5_xpos, rc5_ypos, rc5_xtarget, rc5_ytarget);
        printf( "'%s'\n", rc5_cmd);
        system( rc5_cmd );
    }
}


int main( int argc, char *argv[] )
{
    QCoreApplication a(argc, argv);
    CvCapture *capture = 0;
    if( NULL == (capture = cvCaptureFromCAM( 0 )) ){
        printf( "ERROR: capture failed\n");
        return -1;
    }

    // fetch first frame
    IplImage *frame = NULL;
    if( NULL == (frame = cvQueryFrame( capture )) ){
        printf( "ERROR: frame query failed.\n" );
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
            printf( "ERROR: frame query failed\n");
            break;
        }
        frame = cvCloneImage( frame );
        IplImage *imgThresh = get_threshold_image( frame );

                // blur binary image, using gaussian kernel
        cvSmooth( imgThresh, imgThresh, CV_GAUSSIAN, 3, 3 );

        track_object( imgThresh );

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
