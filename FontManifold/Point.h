#pragma once
#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")

class Point
{
public:
	Point();
	Point(int vx, int vy) :x(vx), y(vy){};
	~Point();
	friend bool operator ==(Point a, Point b);
	Point Min(Point b) const;
	Point Max(Point b) const;
	CvPoint ToCvPoint() const;

	int x, y;
};