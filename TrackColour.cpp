// TrackColour.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

using namespace cv;

IplImage* GetThresholdedImage(IplImage* img)
{
	// Convert the image into an HSV image
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, imgHSV, CV_BGR2HSV);

	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

	// Values 20,100,100 to 30,255,255 working perfect for yellow at around 6pm
	cvInRangeS(imgHSV, cvScalar(112, 100, 100), cvScalar(124, 255, 255), imgThreshed);

	cvReleaseImage(&imgHSV);

	return imgThreshed;
}

int main()
{

	Mat A=Mat(3,3,CV_32FC1);
Mat B=Mat(3,3,CV_32FC1);
Mat C=Mat(3,3,CV_32FC1);

float* ptr = A.ptr<float>(0);

for(int i=1;i<10;i++)
	ptr[i-1] = i;

ptr = B.ptr<float>(0);

ptr[0]=-1;
ptr[1]=-2;
ptr[2]=-1;
ptr[3]=0;
ptr[4]=0;
ptr[5]=0;
ptr[6]=1;
ptr[7]=2;
ptr[8]=1;

	Mat kernel;
	flip(B,kernel,-1);

	Point anchor=Point(1,1);//set to the middle of the kernal

	filter2D(A,C,-1,kernel,Point(1,1), 0, BORDER_CONSTANT);

	// Initialize capturing live feed from the camera
	/*CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);	

	// Couldn't get a device? Throw an error and quit
	if(!capture)
    {
        printf("Could not initialize capturing...\n");
        return -1;
    }

	// The two windows we'll be using
    cvNamedWindow("video");
	cvNamedWindow("thresh");

	// This image holds the "scribble" data...
	// the tracked positions of the ball
	IplImage* imgScribble = NULL;

	// An infinite loop
	while(true)
    {
		// Will hold a frame captured from the camera
		IplImage* frame = 0;
		frame = cvQueryFrame(capture);

		// If we couldn't grab a frame... quit
        if(!frame)
            break;
		
		// If this is the first frame, we need to initialize it
		if(imgScribble == NULL)
		{
			imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
		}

		// Holds the yellow thresholded image (yellow = white, rest = black)
		IplImage* imgYellowThresh = GetThresholdedImage(frame);

		// Calculate the moments to estimate the position of the ball
		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgYellowThresh, moments, 1);

		// The actual moment values
		double moment10 = cvGetSpatialMoment(moments, 1, 0);
		double moment01 = cvGetSpatialMoment(moments, 0, 1);
		double area = cvGetCentralMoment(moments, 0, 0);

		// Holding the last and current ball positions
		static int posX = 0;
		static int posY = 0;

		int lastX = posX;
		int lastY = posY;

		posX = moment10/area;
		posY = moment01/area;

		// Print it out for debugging purposes
		printf("position (%d,%d)\n", posX, posY);

		// We want to draw a line only if its a valid position
		if(lastX>0 && lastY>0 && posX>0 && posY>0)
		{
			// Draw a yellow line from the previous point to the current point
			cvLine(imgScribble, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 5);
		}

		// Add the scribbling image and the frame... and we get a combination of the two
		cvAdd(frame, imgScribble, frame);
		cvShowImage("thresh", imgYellowThresh);
		cvShowImage("video", frame);

		// Wait for a keypress
		int c = cvWaitKey(10);
		if(c!=-1)
		{
			// If pressed, break out of the loop
            break;
		}

		// Release the thresholded image... we need no memory leaks.. please
		cvReleaseImage(&imgYellowThresh);

		delete moments;
    }

	// We're done using the camera. Other applications can now use it
	cvReleaseCapture(&capture);*/
    return 0;
}