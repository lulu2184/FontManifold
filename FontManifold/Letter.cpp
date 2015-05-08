#include "stdafx.h"
#include "Letter.h"
#include <iostream>
#include <array>

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

std::vector<std::pair<int, int> > Letter::getMST(const std::vector<std::vector<double> > &w) const{
	int n = w.size();
	std::vector<std::pair<int, int> > result;
	std::vector<double> d;
	for (int i = 0; i < n; ++i){
		d.push_back(w[0][i]);
	}
	std::vector<bool> flag(n, false);
	std::vector<int> link(n, 0);
	flag[0] = false;
	for (int times = 2; times <= n; times++){
		int p = -1;
		double min_dist = 1e100;
		for (int i = 0; i < n; ++i){
			if (!flag[i] && d[i] < min_dist){
				min_dist = d[i];
				p = i;
			}
		}
		if (p < 0) break;
		flag[p] = true;
		result.push_back(std::make_pair(p, link[p]));
		for (int i = 0; i < n; ++i){
			if (!flag[i] && w[i][p] < d[i]){
				d[i] = w[i][p];
				link[i] = p;
			}
		}
	}
	return std::move(result);
}

void Letter::Alignment()
{
	if (glyphset.size() < 2) return;
	std::vector<std::vector<double> > dist;
	auto first_font = glyphset.begin();
	int row = 0;
	for (auto glyph1 = glyphset.begin(); glyph1 != glyphset.end(); ++glyph1)
	{
		std::vector<double> layer;
		for (int i = 0; i < row; i++){
			layer.push_back(dist[i][row]);
		}
		layer.push_back(0);
		for (auto glyph2 = glyph1 + 1; glyph2 != glyphset.end(); ++glyph2){
			layer.push_back(glyph1->Alignment(*glyph2));
		}
		dist.push_back(std::move(layer));
		row++;
	}
	std::vector<std::pair<int, int> > link = getMST(dist);
	for (auto link_it = link.begin(); link_it != link.end(); ++link_it){
		glyphset[link_it->first].Alignment(glyphset.at(link_it->second));
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
		fname = std::string("D:\\font\\output_result\\") + char(character) + fname + "_" + character + std::to_string(character) + ".bmp";
	//	std::cout << fname << std::endl;
		cvSaveImage(fname.data(), image);
	}
}
