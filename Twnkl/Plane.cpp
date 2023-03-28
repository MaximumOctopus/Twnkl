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

#include "Constants.h"
#include "Plane.h"


Plane::Plane(std::wstring name): Object(name)
{
	Name = name;
}


void Plane::LocalIntersect(Intersections& i, Ray& rt)
{
	if (abs(rt.Direction.y) < epsilon)
	{
		return;
	}

	double t = -rt.Origin.y / rt.Direction.y;

	i.List.push_back(Intersect(t, this));
}


Quaternion Plane::LocalNormalAt(Quaternion& q)
{
	return Quaternion(0, 1, 0, 0);
}


void Plane::PostSetup(int i)
{

}


std::wstring Plane::ToString()
{
	return L"Plane.";
}