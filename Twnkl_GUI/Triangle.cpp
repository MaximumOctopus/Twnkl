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

#include "Triangle.h"


Triangle::Triangle(std::wstring name) : Object(name)
{
	Name = name;
}


void Triangle::SetPoints(Quaternion p1, Quaternion p2, Quaternion p3)
{
	Points[0] = p1;
	Points[1] = p2;
	Points[2] = p3;

	Finalise();
}


void Triangle::SetPointsWithNormal(Quaternion p1, Quaternion p2, Quaternion p3, Quaternion n)
{
	Points[0] = p1;
	Points[1] = p2;
	Points[2] = p3;

	Finalise();

	Normal = n;
	Normal.Normalise();
}


void Triangle::LocalIntersect(Intersections& i, Ray& rt)
{
	Quaternion dir_cross_e2 = rt.Direction.Cross(e2);
	double det = e1.Dot(dir_cross_e2);

	if (std::abs(det) < epsilon)
	{
		return;
	}

	double f = 1.0 / det;
	Quaternion p1_to_origin = rt.Origin;
	p1_to_origin.Sub(Points[0]);

	double u = f * p1_to_origin.Dot(dir_cross_e2);

	if (u < 0 || u > 1.0) 
	{
		return; 
	}

	Quaternion origin_cross_e1 = p1_to_origin.Cross(e1);
	double v = f * rt.Direction.Dot(origin_cross_e1);

	if (v < 0 || (u + v) > 1.0) 
	{ 
		return; 
	}

	double t = f * e2.Dot(origin_cross_e1);

	i.List.push_back(Intersect(t, u, v, this));
}


Quaternion Triangle::LocalNormalAt(Quaternion& q)
{
	return Normal;
}


void Triangle::PostSetup(int i)
{

}


void Triangle::Finalise()
{
	e1 = Points[1];
	e2 = Points[2];

	e1.Sub(Points[0]);
	e2.Sub(Points[0]);

	Normal = e2.Cross(e1);
	Normal.Normalise();
}


std::wstring Triangle::ToString()
{
	return L"Triangle.";
}