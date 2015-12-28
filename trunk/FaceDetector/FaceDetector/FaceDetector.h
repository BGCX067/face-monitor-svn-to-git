#pragma once

#include <cv.h>
#include <iostream>

class __declspec(dllexport) FaceDetector
{
public:
	FaceDetector(std::string cascadeFile = "../.data/");
	~FaceDetector();

	CvSeq *detectFaces(IplImage* image);

private:
	CvHaarClassifierCascade *cascade;
	CvMemStorage *storage;
};
