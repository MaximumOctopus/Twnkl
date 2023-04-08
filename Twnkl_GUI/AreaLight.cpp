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

#include "AreaLight.h"


AreaLight::AreaLight(std::wstring name, double r, double g, double b, double x, double y, double z) : Light(name, r, g, b, x, y, z)
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


Quaternion AreaLight::PointOn(double u, double v)
{
	Quaternion p = Position;

	Quaternion ux = uvec.Mult(u + (rand() / (RAND_MAX + 1.0)));
	Quaternion vx = vvec.Mult(v + (rand() / (RAND_MAX + 1.0)));

	p.Add(ux);
	p.Add(vx);

	return p;
}


void AreaLight::SetDimensions(Quaternion u, Quaternion v, int sample_count)
{
	OriginalUVector = u;
	OriginalVVector = v;

	uvec = u.Mult(1.0 / (double)sample_count);
	vvec = v.Mult(1.0 / (double)sample_count);
	
	deltau = sample_count;
	deltav = sample_count;

	Samples = deltau * deltav;
}


std::wstring AreaLight::ToString()
{
	return L"Area. Samples: " + std::to_wstring(Samples) + L" u: " + uvec.ToString() + L" v : " + vvec.ToString();
}


void AreaLight::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkAreaLight + L"\n");
	ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Intensity.ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"position=" + std::to_wstring(Position.x) + L", " + std::to_wstring(Position.y) + L", " + std::to_wstring(Position.z) + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"uvector=" + std::to_wstring(OriginalUVector.x) + L", " + std::to_wstring(OriginalUVector.y) + L", " + std::to_wstring(OriginalUVector.z) + L"\n");
	ofile << Formatting::to_utf8(L"vvector=" + std::to_wstring(OriginalVVector.x) + L", " + std::to_wstring(OriginalVVector.y) + L", " + std::to_wstring(OriginalVVector.z) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");
}