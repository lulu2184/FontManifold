#pragma once
#include <vector>
#include "Outline.h"
class Glyph
{
public:
	Glyph();
	~Glyph();
	void ShowSamplePoints(IplImage *image) const;
	void ShowPolylines(IplImage *image) const;
	IplImage* NewImage() const;

private:
	Point LeftDown() const;
	Point RightUp() const;

	std::vector<Outline> polyline;
};

