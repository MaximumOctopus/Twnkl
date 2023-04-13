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

#include <algorithm>

#include "Constants.h"
#include "Bounds.h"


bool BoundingBox::ContainsPoint(Quaternion q)
{
    return (q.x >= Minimum.x && q.x <= Maximum.x &&
        q.y >= Minimum.y && q.y <= Maximum.y &&
        q.z >= Minimum.z && q.z <= Maximum.z);
}


void BoundingBox::Transform(Matrix4 m)
{
    Quaternion points[8];

    Quaternion q1(Minimum.x, Minimum.y, Maximum.z, 1);
    Quaternion q2(Minimum.x, Maximum.y, Minimum.z, 1);
    Quaternion q3(Minimum.x, Maximum.y, Maximum.z, 1);
    Quaternion q4(Maximum.x, Minimum.y, Minimum.z, 1);
    Quaternion q5(Maximum.x, Minimum.y, Maximum.z, 1);
    Quaternion q6(Maximum.x, Maximum.y, Minimum.z, 1);

    points[0] = m.MultQ(Minimum);
    points[1] = m.MultQ(q1);
    points[2] = m.MultQ(q2);
    points[3] = m.MultQ(q3);
    points[4] = m.MultQ(q4);
    points[5] = m.MultQ(q5);
    points[6] = m.MultQ(q6);
    points[7] = m.MultQ(Maximum);

    double minx = points[0].x;
    double miny = points[0].y;
    double minz = points[0].z;
    double maxx = points[0].x;
    double maxy = points[0].y;
    double maxz = points[0].z;

    for (int t = 0; t < 8; t++)
    {
        minx = std::min(minx, points[t].x);
        miny = std::min(miny, points[t].y);
        minz = std::min(minz, points[t].z);

        maxx = std::max(maxx, points[t].x);
        maxy = std::max(maxy, points[t].y);
        maxz = std::max(maxz, points[t].z);
    }

    Minimum.x = minx;
    Minimum.y = miny;
    Minimum.z = minz;

    Maximum.x = maxx;
    Maximum.y = maxy;
    Maximum.z = maxz;
}


std::pair<double, double> BoundingBox::CheckAxis(double origin, double direction, double minx, double maxx)
{
    auto tminNumerator = (minx - origin);
    auto tmaxNumerator = (maxx - origin);

    double tmin{ 0 }, tmax{ 0 };

    if (std::abs(direction) >= epsilon)
    {
        tmin = tminNumerator / direction;
        tmax = tmaxNumerator / direction;
    }
    else
    {
        tmin = tminNumerator * 9999999;	// C++ builder gives invalid floating point operations if using INFINITY \_(^-^)_/¯
        tmax = tmaxNumerator * 9999999; //

    }

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    return { tmin, tmax };
}


bool BoundingBox::Intersects(Ray& rt)
{
    auto [xtmin, xtmax] = CheckAxis(rt.Origin.x, rt.Direction.x, Minimum.x, Maximum.x);
    auto [ytmin, ytmax] = CheckAxis(rt.Origin.y, rt.Direction.y, Minimum.y, Maximum.y);
    auto [ztmin, ztmax] = CheckAxis(rt.Origin.z, rt.Direction.z, Minimum.z, Maximum.z);

    auto tmin = std::max(std::max(xtmin, ytmin), ztmin);
    auto tmax = std::min(std::min(xtmax, ytmax), ztmax);

    return tmax >= tmin;
}