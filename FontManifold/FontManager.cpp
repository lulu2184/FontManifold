#include "stdafx.h"
#include "FontManager.h"
#include <fstream>
#include <iostream>

const char FontManager::letterList[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

FontManager::FontManager()
{
	letterSet.resize(numOfLetter);
	for (int i = 0; i < numOfLetter; ++i)
	{
		letterSet[i].SetCharacter(letterList[i]);
	}
}


FontManager::~FontManager()
{
}

void FontManager::Initialize(const char *configfile, std::string fontpath)
{
	std::ifstream config(configfile);
	std::string fontname;
	while (config.good())
	{
		getline(config, fontname);
		std::string path = fontpath + "\\" +  fontname + ".ttf";
		OutlinePreparation Font(fontname);
		Font.InitFont(path);
		for (int i = 0; i < numOfLetter; i++)
		{
			letterSet[i].append(Font.GetPolyline((int)letterList[i], sampleNum));
		}
	}
}

void FontManager::Normalize()
{
	for (int i = 0; i < numOfLetter; i++)
	{
		letterSet[i].Normalize();
	}
}

void FontManager::Alignment()
{
	for (auto it = letterSet.begin(); it != letterSet.end(); ++it)
	{
		it->Alignment();
	}
}

void FontManager::Output()
{
	for (int i = 0; i < numOfLetter; ++i)
	{
		letterSet[i].Output();
	}
}