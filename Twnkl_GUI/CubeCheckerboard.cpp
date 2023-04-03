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

#include "CubeCheckerboard.h"
#include "PatternCommon.h"


CubeChecker::CubeChecker(std::wstring name) : Pattern(name)
{
	Name = name;
}


void CubeChecker::SetDimensions(double u, double v)
{
	Width = u;
	Height = v;
}


Colour CubeChecker::ColourAt(Object* o, Quaternion& q)
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


Colour CubeChecker::UVColourAt(double u, double v)
{
	int x = std::abs(static_cast<int>(u * Width));
	int y = std::abs(static_cast<int>(v * Height));

	if ((x + y) % 2 == 0)
	{
		return Colours[0];
	}

	return Colours[1];
}


std::wstring CubeChecker::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString() + L", Dimensions " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}