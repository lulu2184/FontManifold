#pragma once
#include "stb_truetype.h"

#include <opencv2\\highgui\\highgui.hpp>
#include <opencv2\\core\\core.hpp>
//#include <opencv2\\imgproc\\imgproc.hpp>

#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249d.lib")
//#pragma comment(lib, "opencv_imgproc249d.lib")

#include <iostream>
#include "Outline.h"

class OutlinePreparation
{
public:
	OutlinePreparation();
	~OutlinePreparation();

	void InitFont(char *filename);
	//void ShowGlyphImage(int codenum, const char *goalfile);
	std::vector<Outline> GetPolyline(int codenum, int sampleNum);
	void ShowGlyphSamplePoints(const std::vector<Outline> *polys, IplImage *image) const;
	void ShowGlyphPolylines(const std::vector<Outline> *polys, IplImage *image) const;
	IplImage* NewImage(const std::vector<Outline> *polys) const;
	

private:
	stbtt_fontinfo fontInfo;
	Point GetLeftDownOfGlyph(const std::vector<Outline> *polys) const;
	Point GetRightUpOfGlyph(const std::vector<Outline> *polys) const;
	void GetSamples(Outline *outline, stbtt_vertex P1, stbtt_vertex P2);
};
