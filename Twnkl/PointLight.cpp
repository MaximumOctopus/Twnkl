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

#include "PointLight.h"


PointLight::PointLight(double r, double g, double b, double x, double y, double z) : Light(r, g, b, x, y, z)
{
	Intensity.r = r;
	Intensity.g = g;
	Intensity.b = b;

	Position.x = x;
	Position.y = y;
	Position.z = z;
	Position.w = 1.0;

	deltau = 1;
	deltav = 1;

	Samples = deltau * deltav;
}


Quaternion PointLight::PointOn(double, double)
{
	return Position;
}


std::wstring PointLight::ToString()
{
	return L"Point.";
}