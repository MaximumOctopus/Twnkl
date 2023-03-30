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

#include "PatternCommon.h"
#include "SphericalTexture.h"


SphericalTexture::SphericalTexture(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour SphericalTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = PatternCommon::SphericalMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour SphericalTexture::UVColourAt(double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - v;

	int x = static_cast<int>(u * (Width - 1));
	int y = static_cast<int>(v * (Height - 1));

	// be sure and round x and y to the nearest whole number
	return Texture[y * Width + x];
}


std::wstring SphericalTexture::ToString()
{
	return L"Dimensions " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}