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

#include "CubeTexture.h"
#include "PatternCommon.h"


CubeTexture::CubeTexture(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour CubeTexture::ColourAt(Object* o, Quaternion& q)
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

	return UVColourAt(/*cube_map.faces[face]*/ uv.first, uv.second);
}


Colour CubeTexture::UVColourAt(double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - std::abs(v);
	u = 1.0 - std::abs(u);

	int x = std::abs(static_cast<int>(u * (Width - 1)));
	int y = std::abs(static_cast<int>(v * (Height - 1)));

	return Texture[y * Width + x];
}


std::wstring CubeTexture::ToString()
{
	return L"Dimensions " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}