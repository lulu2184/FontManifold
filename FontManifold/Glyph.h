#pragma once
#include <vector>
#include "Outline.h"
class Glyph
{
public:
	Glyph(std::string ftname);
	~Glyph();
	void ShowSamplePoints(IplImage *image) const;
	void ShowPolylines(IplImage *image) const;
	IplImage* NewImage() const;
	void push_back(Outline outl);
	std::string GetFontName() const;
	void Normalize();
	void Alignment(const Glyph &alignobj);
	int size() const;

private:
	Point LeftDown() const;
	Point RightUp() const;

	std::vector<Outline> polyline;
	std::string fontName;
};

