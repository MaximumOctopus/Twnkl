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


PointLight::PointLight(std::wstring name, double r, double g, double b, double x, double y, double z) : Light(name, r, g, b, x, y, z)
{
	Name = name;

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


void PointLight::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkPointLight + L"\n");
	ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Intensity.ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"position=" + std::to_wstring(Position.x) + L", " + std::to_wstring(Position.y) + L", " + std::to_wstring(Position.z) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");
}