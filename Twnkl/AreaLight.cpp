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