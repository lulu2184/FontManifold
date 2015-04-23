#include "stdafx.h"
#include "Letter.h"

Letter::Letter()
{
}


Letter::~Letter()
{
}

void Letter::SetCharacter(char ch)
{
	character = ch;
}

void Letter::append(Glyph g)
{
	glyphset.push_back(g);
}

void Letter::Normalize()
{
	for (auto it = glyphset.begin(); it != glyphset.end(); ++it)
	{
		it->Normalize();
	}
}

void Letter::Output()
{
	for (auto it = glyphset.cbegin(); it != glyphset.cend(); ++it)
	{
		IplImage *image = it->NewImage();
		it->ShowPolylines(image);
		it->ShowSamplePoints(image);
		std::string fname = it->GetFontName();
		fname = "D:\\font\\output_result\\" + fname + "_" + character + ".bmp";
		cvSaveImage(fname.data(), image);
	}
}