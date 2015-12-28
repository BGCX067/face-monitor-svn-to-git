// FaceDetector.cpp : Defines the exported functions for the DLL application.
//

#include "FaceDetector.h"
#include <iostream>

FaceDetector::FaceDetector(std::string cascadeFile)
{
	this->storage = cvCreateMemStorage(0);
	this->cascade = (CvHaarClassifierCascade*)cvLoad(cascadeFile.c_str(), 0, 0, 0);
	if (!this->cascade){
		//std::runtime_error(std::string("cascade file cannot be loaded: ") +  cascadeFile + "!");
		std::cout << "cascade file cannot be loaded" << std::endl;
		std::runtime_error("cascade file cannot be loaded");
	}
}

FaceDetector::~FaceDetector()
{
	cvFree(&storage);
	cvFree(&cascade);
}

CvSeq *FaceDetector::detectFaces(IplImage *iplImage)
{
	return cvHaarDetectObjects(iplImage, cascade, storage,  1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(30, 30));
}
