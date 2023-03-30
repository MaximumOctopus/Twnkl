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

#include "CylinderTexture.h"
#include "PatternCommon.h"


CylinderTexture::CylinderTexture(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour CylinderTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = PatternCommon::CylindricalMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour CylinderTexture::UVColourAt(double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - v;

	int x = static_cast<int>(u * (Width - 1));
	int y = static_cast<int>(v * (Height - 1));

	// be sure and round x and y to the nearest whole number
	return Texture[y * Width + x];
}


std::wstring CylinderTexture::ToString()
{
	return L"Dimensions " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}