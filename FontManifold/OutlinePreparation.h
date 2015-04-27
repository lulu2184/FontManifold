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
#include "Glyph.h"

class OutlinePreparation
{
public:
	OutlinePreparation(std::string fontname);
	~OutlinePreparation();

	void InitFont(std::string filepath);
	Glyph GetPolyline(int codenum, int sampleNum);
	IplImage* NewImage(const std::vector<Outline> *polys) const;
	

private:
	stbtt_fontinfo fontInfo;
	std::string fontName;
	void GetSamples(Outline *outline, stbtt_vertex P1, stbtt_vertex P2);
	double GetLength(stbtt_vertex P1, stbtt_vertex P2);
	Point CalculatePoint(stbtt_vertex P1, stbtt_vertex P2, double t);
	double GetLengthOfContour(stbtt_vertex *vertices, int begin, int end, std::vector<double> &len);
	Outline SamplingOnContour(stbtt_vertex *vertices, int begin, int end, int sampleNum);
	Outline SamplingOnContourNotEvenly(stbtt_vertex *vertices, int begin, int end, int sampleNum);
};

