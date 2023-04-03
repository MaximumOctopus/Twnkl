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

#include "Sphere.h"


Sphere::Sphere(std::wstring name) : Object(name)
{
	Name = name;
}


void Sphere::LocalIntersect(Intersections& i, Ray& rt)
{
	Quaternion s2r = rt.Origin.SubQ(Position);

	double a = rt.Direction.Dot(rt.Direction);
	double b = 2.0 * rt.Direction.Dot(s2r);
	double c = s2r.Dot(s2r) - 1.0;

	double d = b * b - (4.0 * a * c);

	if (d < 0)
	{
		return;
	}

	double i1 = (-b - std::sqrt(d)) / (2.0 * a);
	double i2 = (-b + std::sqrt(d)) / (2.0 * a);

	if (i1 != i2)
	{
		i.List.push_back(Intersect(i1, this));
		i.List.push_back(Intersect(i2, this));
	}
	else
	{
		i.List.push_back(Intersect(i1, this));
	}
}


// calculates the normal at a space in world space
Quaternion Sphere::LocalNormalAt(Quaternion& world_point)
{
	return Quaternion(world_point.x - Position.x,
		world_point.y - Position.y,
		world_point.z - Position.z,
		0);// object_point.w - Position.w);
}


void Sphere::PostSetup(int i)
{

}


std::wstring Sphere::ToString()
{
	return L"Sphere.";
}