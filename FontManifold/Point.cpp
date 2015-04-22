#include "stdafx.h"
#include "Point.h"
#include <algorithm>


Point::Point()
{
}

Point::~Point()
{
}

bool operator ==(Point a, Point b)
{
	return a.x == b.x && a.y == b.y;
}

Point Point::Max(Point b)const
{
	return Point(std::max(x, b.x), std::max(y, b.y));
}

Point Point::Min(Point b)const
{
	return Point(std::min(x, b.x), std::min(y, b.y));
}

CvPoint Point::ToCvPoint() const
{
	return cvPoint(x, y);
}