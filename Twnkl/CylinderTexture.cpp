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


CylinderTexture::CylinderTexture(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour CylinderTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = CylindricalMap(pattern_point);

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


std::pair<double, double> CylinderTexture::CylindricalMap(Quaternion& p)
{
	// compute the azimuthal angle, same as with spherical_map()
	double theta = atan2(p.x, p.z);
	double raw_u = theta / (2.0 * 3.1415926535);
	double u = 1.0 - (raw_u + 0.5);

	// let v go from 0 to 1 between whole units of y
	double v = static_cast<int>(floor(p.y)) % 1;

	return { u, v };
}


std::wstring CylinderTexture::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}