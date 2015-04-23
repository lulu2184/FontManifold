#pragma once
#include "Glyph.h"
class Letter
{
public:
	Letter();
	~Letter();
	void append(Glyph g);
	void Normalize();
	void Output();
	void SetCharacter(char ch);

private:
	std::vector<Glyph> glyphset;
	char character;
};

