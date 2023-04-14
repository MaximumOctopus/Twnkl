//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 
// 

#include <iostream>

#include "PlanarTexture.h"


PlanarTexture::PlanarTexture(std::wstring name) : Pattern(name)
{
	Name = name;
	Design = PatternDesign::PlanarTexture;
}


PlanarTexture::~PlanarTexture()
{
	delete Texture;
}


Colour PlanarTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = PlanarMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour PlanarTexture::UVColourAt(double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - std::abs(v);

	int x = std::abs(static_cast<int>(u * (Width - 1)));
	int y = std::abs(static_cast<int>(v * (Height - 1)));

	// be sure and round x and y to the nearest whole number
	return Texture[y * Width + x];
}


std::pair<double, double> PlanarTexture::PlanarMap(Quaternion& p)
{
	if (p.x < 0)
	{
		p.x = 1.0 - std::abs(std::fmod(p.x, 1));
	}

	if (p.z < 0)
	{
		p.z = 1.0 - std::abs(std::fmod(p.z, 1));
	}

	double u = std::fmod(p.x, 1);
	double v = std::fmod(p.z, 1);

	return { u, v };
}


std::wstring PlanarTexture::ToString()
{
	return L"Dimensions " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}


void PlanarTexture::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkTexture + L"\n");
	ofile << Formatting::to_utf8(L"filename=" + FileName + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}