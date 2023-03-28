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

#include "Cylinder.h"


Cylinder::Cylinder(std::wstring name) : Object(name)
{
    Name = name;
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

    return (pow(x, 2) + pow(z, 2)) <= 1;
}


void Cylinder::IntersectCaps(Intersections& i, Ray& r)
{
    if (!Closed || abs(r.Direction.y) < epsilon) 
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
    double a = pow(rt.Direction.x, 2) + pow(rt.Direction.z, 2);

    if (abs(a) < epsilon)
    {
        return;
    }

    double b = 2 * rt.Origin.x * rt.Direction.x + 2 * rt.Origin.z * rt.Direction.z;
    double c = pow(rt.Origin.x, 2) + pow(rt.Origin.z, 2) - 1;

    double disc = pow(b, 2) - 4 * a * c;

    if (disc < 0)
    { 
        return;
    }

    double t0 = (-b - sqrt(disc)) / (2 * a);
    double t1 = (-b + sqrt(disc)) / (2 * a);
    
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
    auto dist = pow(world_point.x, 2) + pow(world_point.z, 2);

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
    return L"Cylinder.";
}