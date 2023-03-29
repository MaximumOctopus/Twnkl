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

#include "Cone.h"


Cone::Cone(std::wstring name) : Object(name)
{
    Name = name;
}


void Cone::SetParameters(int min, int max, bool caps)
{
    Minimum = min;
    Maximum = max;
    Closed = caps;
}


bool Cone::CheckCap(double t, double y, Ray& r)
{
    auto x = r.Origin.x + t * r.Direction.x;
    auto z = r.Origin.z + t * r.Direction.z;

    return x * x + z * z <= y * y;
}


void Cone::IntersectCaps(Intersections& i, Ray& r)
{
    if (!Closed || abs(r.Direction.y) < epsilon) 
    {
        return;
    }
        
    auto t = (Minimum - r.Origin.y) / r.Direction.y;

    if (CheckCap(t, abs(Minimum), r))
    {
        i.List.push_back(Intersect(t, this));
    }

    t = (Maximum - r.Origin.y) / r.Direction.y;

    if (CheckCap(t, abs(Maximum), r))
    {
        i.List.push_back(Intersect(t, this));
    }
}


void Cone::LocalIntersect(Intersections& i, Ray& rt)
{
    double a = pow(rt.Direction.x, 2) - pow(rt.Direction.y, 2) + pow(rt.Direction.z, 2);

    if (abs(a) < epsilon) 
    {
        return; 
    }

    double b = 2 * rt.Origin.x * rt.Direction.x - 2 * rt.Origin.y * rt.Direction.y + 2 * rt.Origin.z * rt.Direction.z;
    double c = pow(rt.Origin.x, 2) - pow(rt.Origin.y, 2) + pow(rt.Origin.z, 2);

    if (abs(a) < epsilon && abs(b) >= epsilon)
    {
        double t = -c / (2 * b);

        i.List.push_back(Intersect(t, this));

        return;
    }

    double disc = b * b - 4 * a * c;

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
        i.List.push_back(Intersect(t1, this));
    }

    IntersectCaps(i, rt);
}


// calculates the normal at a space in world space
Quaternion Cone::LocalNormalAt(Quaternion& world_point)
{
    double dist = world_point.x * world_point.x + world_point.z * world_point.z;

    if (dist < 1 && world_point.y >= (Maximum - epsilon))
    {
        return { 0, 1, 0, 0 };
    }
    else if (dist < 1 && world_point.y <= Minimum + epsilon)
    {
        return { 0, -1, 0, 0 };
    }
     
    double y = sqrt(dist);

    if (world_point.y > 0) 
    {
        y = -y; 
    }

    return Quaternion(world_point.x, y, world_point.z, 0);
}


void Cone::PostSetup(int i)
{

}


std::wstring Cone::ToString()
{
    return L"Cone. Min " + std::to_wstring(Minimum) + L", Max " + std::to_wstring(Maximum);
}