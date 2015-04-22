#include "stdafx.h"
#include "Glyph.h"


Glyph::Glyph()
{
}


Glyph::~Glyph()
{
}

Point Glyph::LeftDown() const
{
	bool fir = true;
	Point result;
	for (auto it = polyline.cbegin(); it != polyline.cend(); ++it)
	{
		Outline lines = *it;
		if (fir)
		{
			fir = false;
			result = lines.LeftDown();
		}
		else
		{
			result = result.Min(lines.LeftDown());
		}
	}
	return result;
}

Point Glyph::RightUp() const
{
	bool fir = true;
	Point result;
	for (auto it = polyline.cbegin(); it != polyline.cend(); ++it)
	{
		Outline lines = *it;
		if (fir)
		{
			fir = false;
			result = lines.RightUp();
		}
		else
		{
			result = result.Max(lines.RightUp());
		}
	}
	return result;
}

void Glyph::ShowPolylines(IplImage *image) const
{

}

void Glyph::ShowSamplePoints(IplImage *image) const
{

}

IplImage* Glyph::NewImage() const
{

}