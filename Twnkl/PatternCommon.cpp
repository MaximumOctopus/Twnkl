

#include "PatternCommon.h"


std::pair<double, double> PatternCommon::CylindricalMap(Quaternion& p)
{
	// compute the azimuthal angle, same as sphericalmap()
	double theta = atan2(p.x, p.z);
	double raw_u = theta / (2.0 * 3.1415926535);
	double u = 1.0 - (raw_u + 0.5);

	// let v go from 0 to 1 between whole units of y
	double v = fmod(p.y, 1.0);

	return { u, v };
}


std::pair<double, double> PatternCommon::SphericalMap(Quaternion& p)
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