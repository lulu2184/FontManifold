#include "stdafx.h"
#include "Outline.h"
#include <assert.h>
#include <iostream>

const double Outline::bound = 500.00;
const int Outline::colorNum = 15;
const CvScalar Outline::colorSet[15] = { cvScalar(0, 139, 139), cvScalar(0, 139, 69), cvScalar(255, 215, 0), cvScalar(255, 48, 48),cvScalar(148, 0, 211),
										 cvScalar(255,245,238), cvScalar(209, 95, 238), cvScalar(238, 213,210), cvScalar(240, 255,240), cvScalar(255, 255, 0),
										 cvScalar(255, 99, 71), cvScalar(205, 92, 92), cvScalar(173, 255, 47), cvScalar(230, 230, 450), cvScalar(139, 139, 122)};

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
	int color = 0;
	for (auto it = ptlist.cbegin(); it != ptlist.cend(); ++it)
	{
		CvPoint pt = it->ToCvPoint();
		pt.x -= leftDown.x;
		pt.y = rightUp.y - pt.y;
		color = (color + 1) % colorNum;
		cvCircle(image, pt, 10, colorSet[color], -1);
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

int Outline::size(){
	return ptlist.size();
}

Point Outline::ptAt(int index){
	return ptlist[index];
}

int Outline::Alignment(Outline *std_outline)
{
	assert(std_outline->size() == ptlist.size());
	int len = this->size();
	double min_cost = 1e100;
	int min_delta = -1;
	for (int delta = 0; delta < len; ++delta){
		double cost = 0;
		for (int i = 0; i < len; ++i){
			int j = (i + delta) % len;
			cost += Point::dist(this->ptAt(j), std_outline->ptAt(i));
		}
		if (cost < min_cost){
			min_delta = delta;
			min_cost = cost;
		}
	}
	std::rotate(ptlist.begin(), ptlist.begin() + min_delta, ptlist.end());
	return min_cost;
}