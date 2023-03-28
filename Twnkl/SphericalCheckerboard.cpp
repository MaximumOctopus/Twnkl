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

	std::pair<double, double> uv = SphericalMap(pattern_point);

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


std::pair<double, double> SphericalCheckerboard::SphericalMap(Quaternion& p)
{
	// compute the azimuthal angle
	// -pi < theta <= pi
	// angle increases clockwise as viewed from above,
	// which is opposite of what we want, but we'll fix it later.
	double theta = atan2(p.x, p.z);

	// vec is the vector pointing from the sphere's origin (the world origin)
	// to the point, which will also happen to be exactly equal to the sphere's radius.
	Quaternion vec = Quaternion(p.x, p.y, p.z, 0);
	double radius = vec.Magnitude();

	// compute the polar angle
	// 0 <= phi <= pi
	double phi = acos(p.y / radius);

	// -0.5 < raw_u <= 0.5
	double raw_u = theta / (2.0 * 3.1415926535);

	// 0 <= u < 1
	// here's also where we fix the direction of u. Subtract it from 1,
	// so that it increases counterclockwise as viewed from above.
	double u = 1.0 - (raw_u + 0.5);

	// we want v to be 0 at the south pole of the sphere,
	// and 1 at the north pole, so we have to "flip it over"
	// by subtracting it from 1.
	double v = 1.0 - (phi / 3.1415926535);

	return { u, v };
}


std::wstring SphericalCheckerboard::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}