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

void OutlinePreparation::GetSamples(Outline *outline, stbtt_vertex P1, stbtt_vertex P2)
{
	for (double t = 0.0; t < 1.0; t += 0.1)
	{
		int x, y;
		outline->push_back(CalculatePoint(P1, P2, t));
	}
}

Point OutlinePreparation::CalculatePoint(stbtt_vertex P1, stbtt_vertex P2, double t)
{
	if (P1.type == STBTT_vline)
	{
		x = P1.x * t + P2.x * (1 - t);
		y = P1.y * t + P2.y * (1 - t);
	}
	else
	{
		x = P1.x * t * t + 2 * P1.cx * t * (1 - t) + (1 - t) * (1 - t) * P2.x;
		y = P1.y * t * t + 2 * P1.cy * t * (1 - t) + (1 - t) * (1 - t) * P2.y;
	}
	return Point(x, y);
}

double OutlinePreparation::GetLength(stbtt_vertex P1, stbtt_vertex P2)
{
	if (P1.type == STBTT_vline)
	{
		return sqrt(sqr(P1.x - P2.x) + sqr(P1.y - P2.y));
	}
	else
	{
		double t1 = 2 * P2.x - 4 * P2.cx + 2 * P1.x;
		double t2 = 2 * P2.cx - 2 * P1.x;
		double A = t1 * t1;
		double B = 2 * t1 * t2;
		double C = t2 * t2;
		t1 = 2 * P2.y - 4 * P2.cy + 2 * P1.y;
		t2 = 2 * P2.cy - 2 * P1.y;
		A += t1 * t1;
		B += 2 * t1 * t2;
		C += t2 * t2;
		double t3 = A * C - B * B;
		double result = (1 + B / A) * sqrt(C + 2 * B + A);
		result += t3 / pow(A, 1.5) * arsinh((A + B) / sqrt(t3));
		result -= B / A * sqrt(C);
		result -= t3 / pow(A, 1.5) * arsinh(B / sqrt(t3));
		return result;
	}
}

double OutlinePreparation::GetLengthOfContour(stbtt_vertex *vertices, int begin, int end, std::vector<double> &len)
{
	double perimeter = 0;
	for (int i = begin; i < end; ++i)
	{
		double l = GetLength(vertices[i + 1], vertices[i]);
		perimeter += l;
		len.push_back(l);
	}
	return perimeter;
}

Outline OutlinePreparation::SamplingOnContour(stbtt_vertex *vertices, int begin, int end, int sampleNum)
{
	std::vector <double> len;
	double perimeter = GetLengthOfContour(vertices, begin, end, len);
	auto len_it = len.begin();
	double T = 0;
	double nextT = 0;
	double gap = perimeter / sampleNum;
	int now = begin;
	Glyph result;
	while ()
	{
		if (nextT > T + *len_it)
		{
			T += *len_it;
			++now;
			++len_it;
			if (len_it == len.end()) break;
		}
		double t_sig = (nextT - T) / *len_it;
		result.push_back(CalculatePoint(vertices[i + 1], vertices[i], t_sig));
		nextT += gap;
	}	
	return std::move(result);
}

Glyph OutlinePreparation::GetPolyline(int codenum, int sampleNum)
{
	stbtt_vertex *vertices;
	int glyphIndex = stbtt_FindGlyphIndex(&fontInfo, codenum);
	int ptsnum = stbtt_GetGlyphShape(&fontInfo, glyphIndex, &vertices);
	bool incir = false;
	Point startP;
	int begin = 0;
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
			//GetSamples(&ot, vertices[i], vertices[i - 1]);
			if (nowPoint == startP)
			{
				incir = false;
				//double total_length = GetLengthOfContour(vertices, begin, i);
				result.push_back(SamplingOnContour(vertices, begin, i, total_length, sampleNum));
//				ot.clear();
			}
		}
	}
	return std::move(result);
}
