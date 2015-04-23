#include "stdafx.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "OutlinePreparation.h"
#include <cstdlib>
#include <cstdio>


OutlinePreparation::OutlinePreparation(std::string fontname)
{
	fontName = fontname;
}


OutlinePreparation::~OutlinePreparation()
{
}

unsigned char buffer[8000000];

void OutlinePreparation::InitFont(std::string filepath)
{
	const char *filename = filepath.data();
	FILE *stream;
	if ((stream = fopen(filename, "rb")) == NULL)
	{
		return;
	}
	fread(buffer, 1, 8000000, stream);
	int error = stbtt_InitFont(&fontInfo, buffer, 0);
	if (0 == error)
	{
		//
		return;
	}
	error = 1;
}
/*
Point OutlinePreparation::GetLeftDownOfGlyph(const std::vector<Outline> *polys) const
{
	bool fir = true;
	Point result;
	for (auto it = polys->cbegin(); it != polys->cend(); ++it)
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

Point OutlinePreparation::GetRightUpOfGlyph(const std::vector<Outline> *polys) const
{
	bool fir = true;
	Point result;
	for (auto it = polys->cbegin(); it != polys->cend(); ++it)
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
}*/

void OutlinePreparation::GetSamples(Outline *outline, stbtt_vertex P1, stbtt_vertex P2)
{
	for (double t = 0.0; t < 1.0; t += 0.1)
	{
		int x, y;
		if (P1.cx == 0 && P1.cy == 0)
		{
			x = P1.x * t + P2.x * (1 - t);
			y = P1.y * t + P2.y * (1 - t);
		}
		else
		{
			x = P1.x * t * t + 2 * P1.cx * t * (1 - t) + (1 - t) * (1 - t) * P2.x;
			y = P1.y * t * t + 2 * P1.cy * t * (1 - t) + (1 - t) * (1 - t) * P2.y;
		}
		outline->push_back(Point(x, y));
	}
}

Glyph OutlinePreparation::GetPolyline(int codenum, int sampleNum)
{
	stbtt_vertex *vertices;
	int glyphIndex = stbtt_FindGlyphIndex(&fontInfo, codenum);
	int ptsnum = stbtt_GetGlyphShape(&fontInfo, glyphIndex, &vertices);
	bool incir = false;
	Point startP;
	Outline ot;
	Glyph result(fontName);
	for (int i = 0; i < ptsnum; ++i)
	{
		if (!incir)
		{

			incir = true;
		}
		else
		{
			Point nowPoint = Point((int)vertices[i].x, (int)vertices[i].y);
			GetSamples(&ot, vertices[i], vertices[i - 1]);
			if (nowPoint == startP)
			{
				incir = false;
				result.push_back(ot);
				ot.clear();
			}
		}
	}
	return std::move(result);
}
/*
void OutlinePreparation::ShowGlyphPolylines(const std::vector<Outline> *polys, IplImage *image) const
{
	Point ld = GetLeftDownOfGlyph(polys);
	Point ru = GetRightUpOfGlyph(polys);
	for (auto it = polys->cbegin(); it != polys->cend(); ++it)
	{
		it->DrawPolylines(image, ld, ru);
	}
}

void OutlinePreparation::ShowGlyphSamplePoints(const std::vector<Outline> *polys, IplImage *image) const
{
	Point ld = GetLeftDownOfGlyph(polys);
	Point ru = GetRightUpOfGlyph(polys);
	for (auto it = polys->cbegin(); it != polys->cend(); ++it)
	{
		it->DrawPoints(image, ld, ru);
	}
}

IplImage* OutlinePreparation::NewImage(const std::vector<Outline> *polys) const
{
	Point ld = GetLeftDownOfGlyph(polys);
	Point ru = GetRightUpOfGlyph(polys);
	IplImage *image = cvCreateImage(cvSize(ru.x - ld.x + 10, ru.y - ld.y + 10), 8, 3);
	return image;
}*/