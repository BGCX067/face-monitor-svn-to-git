// FaceDetectApp.cpp : Defines the entry point for the console application.
//
#include <FaceDetector.h>
#include <highgui.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	//CvCapture* capture = cvCaptureFromCAM(0);
	CvCapture* capture = cvCaptureFromAVI("..\\..\\.data\\MelissaTheuriau.avi");
	CvSeq *seq;
	IplImage *img;
	std::string cascadeFile = "..\\..\\.data\\haarcascade_frontalface_alt.xml";
	FaceDetector faceDetector(cascadeFile);

	cvNamedWindow("inputImg", CV_WINDOW_AUTOSIZE);

	for (;;) {
		img = cvQueryFrame(capture);
		
		if (img == NULL) break;

		if (img->origin != IPL_ORIGIN_TL) {
			cvFlip(img, img, 0);
			img->origin = 0;
		}

		seq = faceDetector.detectFaces(img);

		if (seq) {
			IplImage *cpy = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);
			cvCopy(img, cpy, 0); // dst's origin is zero (independently from src's origin)

			//drawRects
			for (int i = 0; i < (seq ? seq->total : 0); i++) {
				CvRect *rect = (CvRect*)cvGetSeqElem(seq, i);
				cvRectangle(cpy, cvPoint(rect->x, rect->y), cvPoint(rect->x + rect->width, rect->y + rect->height),
							CV_RGB(255, 255, 255), 3, 8, 0);
			}

			cvShowImage("inputImg", cpy);
			cvReleaseImage(&cpy);
		} 
		else {
			cvShowImage("inputImg", img);
		}

		if (cvWaitKey(10) >= 0) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("inputImg");

	return 0;
}

