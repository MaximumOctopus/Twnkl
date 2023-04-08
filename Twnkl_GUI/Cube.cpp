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

#include "Cube.h"


Cube::Cube(std::wstring name) : Object(name)
{
	Name = name;
	Primitive = PrimitiveType::Cube;
}


std::pair<double, double> Cube::CheckAxis(double origin, double direction) 
{
	double tminNumerator = (-1 - origin);
	double tmaxNumerator = (1 - origin);

	double tmin(0);
	double tmax(0);

	if (std::abs(direction) >= epsilon)
	{
		tmin = tminNumerator / direction;
		tmax = tmaxNumerator / direction;
	}
	else
	{
		tmin = tminNumerator * 9999999;
		tmax = tmaxNumerator * 9999999;
	}

	if (tmin > tmax)
	{
		std::swap(tmin, tmax);
	}

	return { tmin, tmax };
}


void Cube::LocalIntersect(Intersections& i, Ray& rt)
{
	auto [xtmin, xtmax] = CheckAxis(rt.Origin.x, rt.Direction.x);
	auto [ytmin, ytmax] = CheckAxis(rt.Origin.y, rt.Direction.y);
	auto [ztmin, ztmax] = CheckAxis(rt.Origin.z, rt.Direction.z);

	auto tmin = std::max(std::max(xtmin, ytmin), ztmin);
	auto tmax = std::min(std::min(xtmax, ytmax), ztmax);

	if (tmin > tmax)
	{
		return;
	}

	i.List.push_back(Intersect(tmin, this));
	i.List.push_back(Intersect(tmax, this));
}


// calculates the normal at a space in world space
Quaternion Cube::LocalNormalAt(Quaternion& world_point)
{
	auto maxc = std::max(std::max(std::abs(world_point.x), std::abs(world_point.y)), std::abs(world_point.z));

	if (std::abs(maxc) - std::abs(world_point.x) <= epsilon)
	{
		return { world_point.x, 0, 0, 0 };
	}
	else if (std::abs(maxc) - std::abs(world_point.y) <= epsilon)
	{
		return { 0, world_point.y, 0, 0 };
	}
	else
	{
		return { 0, 0, world_point.z, 0 };
	}
}


void Cube::PostSetup(int i)
{

}


std::wstring Cube::ToString()
{
	return L"Cube.";
}


void Cube::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkObjectCube + L"\n");
	ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}

	Material->ToFile(ofile);
}