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

// openCV
#include <opencv/cv.h>
#include <opencv/highgui.h>

// c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

IplImage *imgTracking = NULL;


// threshold hsv image
IplImage *get_threshold_image(IplImage *frame)
{
  cvSmooth(frame, frame, CV_GAUSSIAN, 3, 3, 0, 0);

  // generate hsv image from rgb
  IplImage *imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
  cvCvtColor(frame, imgHSV,
             CV_BGR2HSV); // Change the color format from BGR to HSV
  IplImage *imgThresh = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);

  /*
   * settings - several callibrations set up here
   */

  // home
  //    cvInRangeS( imgHSV, cvScalar( 38, 140, 100 ), cvScalar( 75, 256, 256 ),
  //    imgThresh );


  // lab
  cvInRangeS(imgHSV, cvScalar(38, 100, 70, 0), cvScalar(75, 256, 256, 0),
             imgThresh);


  cvReleaseImage(&imgHSV);
  return imgThresh;
}


void track_object(IplImage *imgThresh)
{
  // compute the "moments" in imgThresh
  CvMoments *moments = NULL;
  if (NULL == (moments = ( CvMoments * )malloc(sizeof(*moments)))) {
    perror("ERROR: allocation failed");
    return;
  }
  cvMoments(imgThresh, moments, 1);
  double area = cvGetCentralMoment(moments, 0, 0);
  double moment10 = cvGetSpatialMoment(moments, 1, 0);
  double moment01 = cvGetSpatialMoment(moments, 0, 1);
  free(moments);

  /*
    if the area is <1000, area is considered noise and ignored
  */
  if (1000 >= area) {
    puts("DEBUG: area too small");
    return;
  }

  // compute position
  int xpos = moment10 / area;
  int ypos = moment01 / area;

  // for waitpid
  int childExitStatus = 0;
  pid_t pid_wait = -1;

  if (0 <= xpos && 0 <= ypos) {
    // draw trace..
    char rc5_prg[] = "./irtransclientmac/sendpackets";
    char rc5_id[] = "7";
    char rc5_xpos[8];
    sprintf(rc5_xpos, "%d", xpos);
    char rc5_ypos[8];
    sprintf(rc5_ypos, "%d", ypos);
    char rc5_xtarget[] = "600";
    char rc5_ytarget[] = "350";

    char *rc5_args[16] = {rc5_prg,     rc5_id,      rc5_xpos,   rc5_ypos,
                          rc5_xtarget, rc5_ytarget, ( char * )0};

    /*
      since we don't want to mess with syncing, etc. avoid pthreads,
      and choose fork/waitpid solution executing an execv call, else
      waiting untill it's pid has expired ( = that is, when the external
      program has executed )
     */
    pid_t pid = 0;
    if (0 != waitpid(pid_wait, &childExitStatus, WNOHANG)) {
      if (0 > (pid = fork())) {
        perror("fork() failed");
        exit(EXIT_FAILURE);

      } else if (pid == 0) {
        // child
        printf("%s %s %s %s %s %s\n", rc5_prg, rc5_id, rc5_xpos, rc5_ypos,
               rc5_xtarget, rc5_ytarget);
        execv(rc5_prg, rc5_args);
        exit(EXIT_SUCCESS);
      } else {
        // parent
        pid_wait = pid;
      }
    } else {
      puts("...skipping, sending busy");
    }
  }
}


int main(int argc, char *argv[])
{
  CvCapture *capture = 0;
  if (NULL == (capture = cvCaptureFromCAM(0))) {
    perror("capture failed\n");
    return -1;
  }

  // fetch first frame
  IplImage *frame = NULL;
  if (NULL == (frame = cvQueryFrame(capture))) {
    perror("frame query failed.");
    return -1;
  }

  // create a blank image and assigned to "imgTracking"
  imgTracking = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
  cvZero(imgTracking); // convert imgTracking to black


  //    cvNamedWindow( "target" );
  cvNamedWindow("target", CV_WINDOW_NORMAL);
  while (1) {

    // fetch regular frames
    IplImage *frame = NULL;
    frame = NULL;
    if (NULL == (frame = cvQueryFrame(capture))) {
      perror("frame query failed");
      break;
    }
    frame = cvCloneImage(frame);
    IplImage *imgThresh = get_threshold_image(frame);

    // blur binary image, using gaussian kernel
    cvSmooth(imgThresh, imgThresh, CV_GAUSSIAN, 3, 3, 0, 0);

    track_object(imgThresh);

    cvShowImage("target", imgThresh);

    // cleanup
    cvReleaseImage(&imgThresh);
    cvReleaseImage(&frame);

    // wait 10 ms, then if ESC is pressed, beak
    if (27 == cvWaitKey(10)) {
      break;
    }
  }

  cvDestroyAllWindows();
  cvReleaseImage(&imgTracking);
  cvReleaseCapture(&capture);

  exit(EXIT_SUCCESS);
}
