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

#include "CylinderCheckerboard.h"


CylinderCheckerboard::CylinderCheckerboard(std::wstring name) : Pattern(name)
{
	Name = name;
}


void CylinderCheckerboard::SetDimensions(double u, double v)
{
	Width = u;
	Height = v;
}


Colour CylinderCheckerboard::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = CylindricalMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour CylinderCheckerboard::UVColourAt(double u, double v)
{
	int u2 = static_cast<int>(floor(u * Width));
	int v2 = static_cast<int>(floor(v * Height));

	if ((u2 + v2) % 2 == 0)
	{
		return Colours[0];
	}

	return Colours[1];
}


std::pair<double, double> CylinderCheckerboard::CylindricalMap(Quaternion& p)
{
	// compute the azimuthal angle, same as with spherical_map()
	double theta = atan2(p.x, p.z);
	double raw_u = theta / (2.0 * 3.1415926535);
	double u = 1.0 - (raw_u + 0.5);

	// let v go from 0 to 1 between whole units of y
	double v = static_cast<int>(floor(p.y)) % 1;

	return { u, v };
}


std::wstring CylinderCheckerboard::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}