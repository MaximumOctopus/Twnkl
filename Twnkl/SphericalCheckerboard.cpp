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
#include "SphericalCheckerboard.h"


SphericalCheckerboard::SphericalCheckerboard(std::wstring name) : Pattern(name)
{
	Name = name;
}


void SphericalCheckerboard::SetDimensions(double u, double v)
{
	Width = u;
	Height = v;
}


Colour SphericalCheckerboard::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = PatternCommon::SphericalMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour SphericalCheckerboard::UVColourAt(double u, double v)
{
	int u2 = static_cast<int>(floor(u * Width));
	int v2 = static_cast<int>(floor(v * Height));

	if ((u2 + v2) % 2 == 0)
	{
		return Colours[0];
	}
	
	return Colours[1];
}


std::wstring SphericalCheckerboard::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}