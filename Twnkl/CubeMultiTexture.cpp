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

#include "CubeMultiTexture.h"
#include "PatternCommon.h"


CubeMultiTexture::CubeMultiTexture(std::wstring name) : Pattern(name)
{
	Name = name;
	Design = PatternDesign::CubeMultiTexture;
}


CubeMultiTexture::~CubeMultiTexture()
{
	for (int t = 0; t < 6; t++)
	{
		delete Texture[t];
	}
}


Colour CubeMultiTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = { 0, 0 };

	int face = PatternCommon::FaceFromPoint(pattern_point);

	if (face == 1)
		uv = PatternCommon::CubeUVLeft(pattern_point);
	else if (face == 0)
		uv = PatternCommon::CubeUVRight(pattern_point);
	else if (face == 4)
		uv = PatternCommon::CubeUVFront(pattern_point);
	else if (face == 5)
		uv = PatternCommon::CubeUVBack(pattern_point);
	else if (face == 2)
		uv = PatternCommon::CubeUVUp(pattern_point);
	else
		uv = PatternCommon::CubeUVDown(pattern_point);

	return UVColourAt(face, uv.first, uv.second);
}


Colour CubeMultiTexture::UVColourAt(int face, double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - std::abs(v);
	u = 1.0 - std::abs(u);

	int x = std::abs(static_cast<int>(u * (Width - 1)));
	int y = std::abs(static_cast<int>(v * (Height - 1)));

	return Texture[face][y * Width + x];
}


std::wstring CubeMultiTexture::ToString()
{
	return L"Texture " + std::to_wstring(Width) + L" x " + std::to_wstring(Height) + L" (x6)";
}


void CubeMultiTexture::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkTexture + L"\n");
	ofile << Formatting::to_utf8(L"filename=" + FileName + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}