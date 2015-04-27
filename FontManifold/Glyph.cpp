#include "stdafx.h"
#include "Glyph.h"


Glyph::Glyph(std::string ftname)
{
	fontName = ftname;
}


Glyph::~Glyph()
{
}

std::string Glyph::GetFontName() const
{
	return fontName;
}

void Glyph::push_back(Outline outl)
{
	polyline.push_back(outl);
}

Outline *Glyph::GetOutline(int index)
{
	return &polyline[index];
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
	Point ld = LeftDown();
	Point ru = RightUp();
	for (auto it = polyline.cbegin(); it != polyline.cend(); ++it)
	{
		it->DrawPolylines(image, ld, ru);
	}
}

void Glyph::ShowSamplePoints(IplImage *image) const
{
	Point ld = LeftDown();
	Point ru = RightUp();
	for (auto it = polyline.cbegin(); it != polyline.cend(); ++it)
	{
		it->DrawPoints(image, ld, ru);
	}
}

IplImage* Glyph::NewImage() const
{
	Point ld = LeftDown();
	Point ru = RightUp();
	IplImage *image = cvCreateImage(cvSize(ru.x - ld.x + 10, ru.y - ld.y + 10), 8, 3);
	return image;
}

int Glyph::size() const
{
	return (int)polyline.size();
}

void Glyph::Normalize()
{
	for (auto it = polyline.begin(); it != polyline.end(); ++it)
	{
		it->Normalize();
	}
}

void Glyph::Alignment(Glyph &alignobj)
{
	if (alignobj.size() != polyline.size()) return;
	int m = polyline.size();
	std::vector <int> permutation;
	std::vector <int> best_per;
	int min_cost = 0xFFFFFFFF;
	// initialize permutation , p[i] = i
	for (int i = 0; i < m; ++i)
	{
		permutation.push_back(i);
	}
	best_per = permutation;
	while (true)
	{
		int cost = 0;
		// permutation.next_permutation();
		for (int i = 0; i < m; ++i)
		{
			Outline *o = alignobj.GetOutline(i);
			cost += polyline[permutation[i]].Alignment(o);
		}
		if (cost < min_cost)
		{
			min_cost = cost;
			best_per = permutation;
		}
	}
	for (int i = 0; i < m; ++i)
	{
		Outline *o = alignobj.GetOutline(i);
		polyline[permutation[i]].Alignment(o);
	}
}
