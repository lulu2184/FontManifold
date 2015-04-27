#pragma once
#include "Letter.h"
#include "OutlinePreparation.h"
#include <string>
#include <array>
class FontManager
{
public:
	FontManager();
	~FontManager();
	void Initialize(const char *configfile, std::string fontpath);
	void Normalize();
	void Alignment();
	void Output();

private:
	const static char letterList[63];// = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	const static int numOfLetter = 62;
	const static int sampleNum = 300;

	std::vector<Letter> letterSet;
};

