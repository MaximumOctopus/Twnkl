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

#include "Light.h"


Light::Light(std::wstring name, double r, double g, double b, double x, double y, double z)
{
	Name = name;

	Intensity.r = r;
	Intensity.g = g;
	Intensity.b = b;

	Position.x = x;
	Position.y = y;
	Position.z = z;
	Position.w = 1.0;
}


Quaternion Light::PointOn(double, double)
{
	return Quaternion();
}


std::wstring Light::ToString()
{
	return L"";
}


void Light::ToFile(std::ofstream& ofile)
{
}