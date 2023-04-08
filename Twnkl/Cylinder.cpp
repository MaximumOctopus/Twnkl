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

#include <cmath>

#include "Cylinder.h"


Cylinder::Cylinder(std::wstring name) : Object(name)
{
    Name = name;
    Primitive = PrimitiveType::Cylinder;
}


void Cylinder::SetParameters(int min, int max, bool caps)
{
    Minimum = min;
    Maximum = max;
    Closed = caps;
}


bool Cylinder::CheckCap(double t, Ray& r)
{
    auto x = r.Origin.x + t * r.Direction.x;
    auto z = r.Origin.z + t * r.Direction.z;

    return (x * x + z * z) <= 1;
}


void Cylinder::IntersectCaps(Intersections& i, Ray& r)
{
    if (!Closed || std::abs(r.Direction.y) < epsilon)
    {
        return;
    }

    auto t = (Minimum - r.Origin.y) / r.Direction.y;
    
    if (CheckCap(t, r))
    {
        i.List.push_back(Intersect(t, this));
    }

    t = (Maximum - r.Origin.y) / r.Direction.y;

    if (CheckCap(t, r)) 
    {
        i.List.push_back(Intersect(t, this));
    }
}


void Cylinder::LocalIntersect(Intersections& i, Ray& rt)
{
    double a = rt.Direction.x * rt.Direction.x + rt.Direction.z * rt.Direction.z;

    if (std::abs(a) < epsilon)
    {
        return;
    }

    double b = 2 * rt.Origin.x * rt.Direction.x + 2 * rt.Origin.z * rt.Direction.z;
    double c = rt.Origin.x * rt.Origin.x + rt.Origin.z * rt.Origin.z - 1;

    double disc = b * b - 4 * a * c;

    if (disc < 0)
    { 
        return;
    }

    double t0 = (-b - std::sqrt(disc)) / (2 * a);
    double t1 = (-b + std::sqrt(disc)) / (2 * a);
    
    if (t0 > t1) 
    {
        std::swap(t0, t1); 
    }

    double y0 = rt.Origin.y + t0 * rt.Direction.y;

    if (Minimum < y0 && y0 < Maximum) 
    {
        i.List.push_back(Intersect(t0, this));
    }

    double y1 = rt.Origin.y + t1 * rt.Direction.y;

    if (Minimum < y1 && y1 < Maximum) 
    {
        i.List.push_back(Intersect(t0, this));
    }

    IntersectCaps(i, rt);
}


// calculates the normal at a space in world space
Quaternion Cylinder::LocalNormalAt(Quaternion& world_point)
{
    auto dist = world_point.x * world_point.x + world_point.z * world_point.z;

    if (dist < 1 && world_point.y >= (Maximum - epsilon))
    {
        return { 0, 1, 0, 0 };
    }
    else if (dist < 1 && world_point.y <= Minimum + epsilon) 
    {
        return { 0, -1, 0, 0 };
    }
    else 
    {
        return { world_point.x, 0, world_point.z, 0 };
    }
}


void Cylinder::PostSetup(int i)
{

}


std::wstring Cylinder::ToString()
{
    return L"Cylinder. Min " + std::to_wstring(Minimum) + L", Max " + std::to_wstring(Maximum);
}


void Cylinder::ToFile(std::ofstream& ofile)
{
    ofile << Formatting::to_utf8(__SceneChunkObjectCylinder + L"\n");
    ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
    ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
    ofile << Formatting::to_utf8(L"minimum=" + std::to_wstring(Minimum) + L"\n");
    ofile << Formatting::to_utf8(L"maximum=" + std::to_wstring(Maximum) + L"\n");
    if (Closed)
    {
        ofile << Formatting::to_utf8(L"closed=yes\n");
    }

    for (int t = 0; t < Transforms.size(); t++)
    {
        Transforms[t].ToFile(ofile);
    }

    Material->ToFile(ofile);
}