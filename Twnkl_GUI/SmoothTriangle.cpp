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

#include "SmoothTriangle.h"


SmoothTriangle::SmoothTriangle(std::wstring name) : Object(name)
{
	Name = name;
	Primitive = PrimitiveType::SmoothTriangle;
}


void SmoothTriangle::SetPointsNormals(Quaternion p1, Quaternion p2, Quaternion p3, Quaternion n1, Quaternion n2, Quaternion n3)
{
	Points[0] = p1;
	Points[1] = p2;
	Points[2] = p3;

	Normals[0] = n1;
	Normals[1] = n2;
	Normals[2] = n3;

	Finalise();
}


void SmoothTriangle::LocalIntersect(Intersections& i, Ray& rt)
{
	auto dir_cross_e2 = rt.Direction.Cross(e2);
	auto det = e1.Dot(dir_cross_e2);

	if (std::abs(det) < epsilon)
	{
		return;
	}

	auto f = 1.0 / det;
	auto p1_to_origin = rt.Origin;
	rt.Origin.Sub(Points[0]);

	auto u = f * p1_to_origin.Dot(dir_cross_e2);

	if (u < 0 || u > 1)
	{
		return;
	}

	auto origin_cross_e1 = p1_to_origin.Cross(e1);
	auto v = f * rt.Direction.Dot(origin_cross_e1);

	if (v < 0 || (u + v) > 1)
	{
		return;
	}

	auto t = f * e2.Dot(origin_cross_e1);

	i.List.push_back(Intersect(t, u, v, this));
}


Quaternion SmoothTriangle::LocalNormalAt(Quaternion& q) // Intersect hit);
{
	return Quaternion(0, 0, 0, 0);

	/*Quaternion a = Normals[1];
	Quaternion b = Normals[2];
	Quaternion c = Normals[0];

	a.Scale(hit.u);
	b.Scale(hit.v);
	c.Scale(1 - hit.u - hit.v);

	a.Add(b);
	a.Add(c);

	return a;*/
}


void SmoothTriangle::Finalise()
{
	e1 = Points[1];
	e2 = Points[2];

	e1.Sub(Points[0]);
	e2.Sub(Points[0]);
}


void SmoothTriangle::PostSetup(int i)
{

}


std::wstring SmoothTriangle::ToString()
{
	return L"SmoothTriangle.";
}


void SmoothTriangle::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkObjectSmoothTriangle + L"\n");
	ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"}\n");
}