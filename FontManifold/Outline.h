#pragma once

#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")


#include <vector>
#include "Point.h"

class Outline
{
public:
	Outline();
	~Outline();
	bool empty() const;
	void clear();
	int size();
	void push_back(Point P);
	Point LeftDown() const;
	Point RightUp() const;
	void DrawPolylines(IplImage *image, Point leftDown, Point rightUp)const;
	void DrawPoints(IplImage *image, Point leftDown, Point rightUp)const;
	void Normalize();
	int Alignment(Outline *std_outline);
	Point ptAt(int index);

private:
	std::vector<Point> ptlist;
	Point offset;
	Point scale;

	const static double bound;// = 100.00;
	const static int colorNum;
	const static CvScalar colorSet[15];
};

