#include "stdafx.h"
#include "Outline.h"

const double Outline::bound = 500.00;

Outline::Outline()
{
}


Outline::~Outline()
{

}

void Outline::clear()
{
	ptlist.clear();
}

bool Outline::empty() const
{
	return ptlist.empty();
}

Point Outline::LeftDown() const
{
	Point res;
	bool flag = false;
	for (auto it = ptlist.cbegin(); it != ptlist.cend(); ++it)
	{
		if (!flag) res = *it;
		res.x = std::min(res.x, it->x);
		res.y = std::min(res.y, it->y);
		flag = true;
	}
	return res;
}

Point Outline::RightUp() const
{
	Point res;
	bool flag = false;
	for (auto it = ptlist.cbegin(); it != ptlist.cend(); ++it)
	{
		if (!flag) res = *it;
		res.x = std::max(res.x, it->x);
		res.y = std::max(res.y, it->y);
		flag = true;
	}
	return res;
}

void Outline::push_back(Point P)
{
	ptlist.push_back(P);
}

void Outline::DrawPolylines(IplImage *image, Point leftDown, Point rightUp) const
{
	int num = 0;
	CvPoint *samplePts = (CvPoint *)malloc(sizeof(CvPoint) * ptlist.size());
	for (auto it = ptlist.cbegin(); it != ptlist.cend(); ++it)
	{
		samplePts[num] = it->ToCvPoint();
		samplePts[num].x -= leftDown.x;
		samplePts[num].y = rightUp.y - samplePts[num].y;
		++num;
	}
	cvPolyLine(image, &samplePts, &num, 1, 1, CV_RGB(0, 0, 0));
}

void Outline::DrawPoints(IplImage *image, Point leftDown, Point rightUp) const
{
	for (auto it = ptlist.cbegin(); it != ptlist.cend(); ++it)
	{
		CvPoint pt = it->ToCvPoint();
		pt.x -= leftDown.x;
		pt.y = rightUp.y - pt.y;
		cvCircle(image, pt, 10, CV_RGB(0, 0, 0));
	}
}

void Outline::Normalize()
{
	Point ld = LeftDown();
	Point ru = RightUp();
	offset = (ru + ld) / 2;
	ld = ld - offset;
	ru = ru - offset;
	scale.x = std::max(std::abs(ld.x), std::abs(ru.x)) / bound;
	scale.y = std::max(std::abs(ld.y), std::abs(ru.y)) / bound;
	for (auto it = ptlist.begin(); it != ptlist.end(); ++it)
	{
		*it = (*it - offset) / scale;
	}	
}