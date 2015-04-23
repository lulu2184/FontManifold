// FontManifold.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "OutlinePreparation.h"
#include "FontManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
//	OutlinePreparation Font;
//	Font.InitFont("D:\\andlso.tff");
	//Font.ShowGlyphImage(103, "D:\\a.bmp");
//	std::vector<Outline> ots1 = Font.GetPolyline(97, 1000);
//	IplImage *image = Font.NewImage(&ots1);
//	Font.ShowGlyphPolylines(&ots1, image);
//	Font.ShowGlyphSamplePoints(&ots1, image);
//	cvSaveImage("D:\\a.bmp", image);
	FontManager fm;
	fm.Initialize("D:\\font\\config.txt", "D:\\font");
//	fm.Output();
	fm.Normalize();
	fm.Output();

	return 0;
}

